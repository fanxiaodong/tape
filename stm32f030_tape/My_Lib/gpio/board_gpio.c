#include "ALL_Includes.h"

static void set_gpio_port_clk(uint32_t port,FunctionalState NewState)
{
	RCC_AHBPeriphClockCmd(port, NewState);
}

static int get_gpio_port_nm(uint32_t  pport){
	switch(pport) {
	 case GPIOA_BASE: return 0;
	 case GPIOB_BASE: return 1;
	 case GPIOC_BASE: return 2;
	 case GPIOD_BASE: return 3;
	// case GPIOE_BASE: return 4;
	 case GPIOF_BASE: return 5;
	 default: return -1;
	 }
}

static int bit2nm(uint32_t bit){
	int i;
	for(i = 0; i < 32; i++){
		if(bit & (1<<i)){
			return i;
		}
	}
	return -1;
}

static uint32_t nm2bit(int nm){
	return (1<<nm);
}
int init_gpio(gpio_t *pgpio)
{
	gpio_t *pma = pgpio;
	int pin_nm;
	if(pma->status == 0)
	{
		set_gpio_port_clk(pma->gpio_clk, ENABLE);
		
		GPIO_Init(pma->gpio_port,&pma->init_val);
		
		pin_nm = bit2nm(pma->init_val.GPIO_Pin);

		printf(" init_gpio_pwm_pin %d: %d\n",pin_nm,pma->init_val.GPIO_Mode);

		if(pma->init_val.GPIO_Mode == GPIO_Mode_OUT){
			GPIO_WriteBit(pma->gpio_port,pma->init_val.GPIO_Pin, Bit_SET);
		}else if(pma->init_val.GPIO_Mode == GPIO_Mode_AF){
			GPIO_PinAFConfig(pma->gpio_port, pin_nm,pma->gpio_af);
		}else if(pma->init_val.GPIO_Mode == GPIO_Mode_AN){
			
		}else{
			
		}
		
		pma->status = pma->init_val.GPIO_Pin;
	}	
	
	return 0;
}

void set_gpio_pin_val(gpio_t *pgpio, uint32_t val)
{	
	gpio_t *pma = pgpio;

	if(pma->status == 0)
	{
		return;
	}	
	
	GPIO_WriteBit(pma->gpio_port,pma->init_val.GPIO_Pin, val ? Bit_SET : Bit_RESET);
	
}

int get_gpio_pin_val(gpio_t *pgpio)
{	
	gpio_t *pma = pgpio;
	if(pma->status == 0)
	{
		return -1;
	}	

	uint32_t val = GPIO_ReadInputData(pma->gpio_port);
	return (val &  pma->init_val.GPIO_Pin) ? 1:0;
}

int get_gpio_group_val(gpio_t *pgpio, uint32_t mask)
{	
	gpio_t *pma = pgpio;
	if(pma->status == 0)
	{
		return -1;
	}	

	uint32_t val = GPIO_ReadInputData(pma->gpio_port);
	return (val & mask);
}





//////////////////////////////////////////////////////////////
typedef enum _gpio_exti_e
{
	GPIO_0_1,
	GPIO_2_3,
	GPIO_4_15,
	GPID_EXTI_NM
}GPIO_EXTI_E;

static gpio_interrupt_t *pgpio_exti[GPID_EXTI_NM];
int gpio_bit_val;

//STARTUP\startup_stm32f0xx_ld.s
//DCD 	EXTI0_1_IRQHandler			   ; EXTI Line 0 and 1
//DCD 	EXTI2_3_IRQHandler			   ; EXTI Line 2 and 3
//DCD 	EXTI4_15_IRQHandler 		   ; EXTI Line 4 to 15

/*
只支持每种类型设置一个gpio管脚
*/
void gpio_interrupt_Config(gpio_interrupt_t *pgi)
{

  int gpio_port_nm = 0;
  int gpio_pin_nm = 0;

  
  /* Enable GPIOC clock */
  RCC_AHBPeriphClockCmd(pgi->pgpio_info->gpio_clk, ENABLE);

  /* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  GPIO_Init(pgi->pgpio_info->gpio_port, &pgi->pgpio_info->init_val);

  gpio_port_nm = get_gpio_port_nm((uint32_t)pgi->pgpio_info->gpio_port);
  
  gpio_pin_nm = bit2nm(pgi->pgpio_info->init_val.GPIO_Pin);
  
  if(pgi->pgpio_info->init_val.GPIO_Pin & 0x3){
  	pgpio_exti[GPIO_0_1] = pgi;
  }else if(pgi->pgpio_info->init_val.GPIO_Pin &(0x3<<2)){
  	pgpio_exti[GPIO_2_3] = pgi;
  }else if(pgi->pgpio_info->init_val.GPIO_Pin &(0xfff<<4)){
  	pgpio_exti[GPIO_4_15] = pgi;
  }
   /* Connect EXTI8 Line to PC8 pin 
     SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOC, EXTI_PinSource13);
     */ 
  SYSCFG_EXTILineConfig(gpio_port_nm, gpio_pin_nm);
 
  pgi->exti_init_val.EXTI_Line = pgi->pgpio_info->init_val.GPIO_Pin;

  EXTI_Init(&pgi->exti_init_val);
  
  EXTI_ClearITPendingBit(pgi->exti_init_val.EXTI_Line);
  
  NVIC_Init(&pgi->nvic_init_val);

}


void EXTI0_1_IRQHandler(void){
	int ret;
	gpio_interrupt_t *pgi = pgpio_exti[GPIO_0_1] ;

	if(EXTI_GetITStatus(pgi->exti_init_val.EXTI_Line) != RESET){

		gpio_bit_val = get_gpio_group_val(pgi->pgpio_info,0x3f);

		//printf("intr......%d\n",ret);
		//gpio_bit_val = ret ;
		EXTI_ClearITPendingBit(pgi->exti_init_val.EXTI_Line);
	}
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

