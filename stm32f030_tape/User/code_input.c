#include "ALL_Includes.h"
typedef enum _CODE_PIN
{
	DATA_0,
	DATA_1,
	DATA_2,
	DATA_3,
	DATA_4,
	DATA_5,
	DATA_6,
	DATA_7,
	DATA_NM,       
}CODE_PIN;

typedef struct
{
	gpio_t data_pin[DATA_NM];  // RESETn_A PA1  µÕµÁ∆Ω∏¥Œª
}code_pin_t;

code_pin_t data_pin_ctl =
{
	.data_pin[DATA_0]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin	= GPIO_Pin_0,
		.GPIO_Mode	= GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd	= GPIO_PuPd_UP,
		},
		.status = 0,
	},

	.data_pin[DATA_1]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin	= GPIO_Pin_1,
		.GPIO_Mode	= GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd	= GPIO_PuPd_UP,
		},
		.status = 0,
	},
	
	.data_pin[DATA_2]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin	= GPIO_Pin_2,
		.GPIO_Mode	= GPIO_Mode_IN,
		.GPIO_Speed 	= GPIO_Speed_50MHz,
		.GPIO_OType 	= GPIO_OType_PP,
		.GPIO_PuPd	= GPIO_PuPd_UP,
		},
		.status = 0,
	},
	.data_pin[DATA_3]={
		.gpio_clk = RCC_AHBPeriph_GPIOC,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin	= GPIO_Pin_3,
		.GPIO_Mode	= GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd	= GPIO_PuPd_UP,
		},
		.status = 0,
	},
	.data_pin[DATA_4]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin 	= GPIO_Pin_4,
		.GPIO_Mode 	= GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd 	= GPIO_PuPd_UP,
		},
		.status = 0,	
	},
	.data_pin[DATA_5]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin 	= GPIO_Pin_5,
		.GPIO_Mode 	= GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd 	= GPIO_PuPd_UP,
		},
		.status = 0,
	},
	.data_pin[DATA_6]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin 	= GPIO_Pin_6,
		.GPIO_Mode 	= GPIO_Mode_IN,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd 	= GPIO_PuPd_NOPULL,
		},
		.status = 0xffff,
	},
	.data_pin[DATA_7]={
		.gpio_clk = RCC_AHBPeriph_GPIOA,
		.gpio_port = GPIOA,
		.init_val = {
		.GPIO_Pin 	= GPIO_Pin_7,
		.GPIO_Mode 	= GPIO_Mode_OUT,
		.GPIO_Speed = GPIO_Speed_50MHz,
		.GPIO_OType = GPIO_OType_PP,
		.GPIO_PuPd 	= GPIO_PuPd_UP,
		},
		.status = 0,
	}
};
//=============for gpio interrupt==================
gpio_interrupt_t gpio_intr = {
	.pgpio_info = &data_pin_ctl.data_pin[DATA_0],
	.exti_init_val = {
		.EXTI_Line = 0,
		.EXTI_Mode = EXTI_Mode_Interrupt,
		.EXTI_Trigger = EXTI_Trigger_Rising_Falling,
		.EXTI_LineCmd = ENABLE,
	},
	.nvic_init_val = {
		.NVIC_IRQChannel = EXTI0_1_IRQn,
		.NVIC_IRQChannelPriority = 0x00,
		.NVIC_IRQChannelCmd = ENABLE,
	},
};

void init_code_input(void)
{
	int i;	
	for(i = 0 ;i < DATA_NM; i++){
		init_gpio(&data_pin_ctl.data_pin[i]);
	}

	gpio_intr.exti_init_val.EXTI_Line = gpio_intr.pgpio_info->init_val.GPIO_Pin;
	
	gpio_interrupt_Config(&gpio_intr);
	
}

int get_code_input(void)
{
	int val = get_gpio_group_val(&data_pin_ctl.data_pin[0],0x3f);
	//printf("val = %x\n",val);
	return val;
}
int get_Infrared_input(void)
{
	return get_gpio_pin_val(&data_pin_ctl.data_pin[DATA_6]);
}

void set_infrared_en(int enable)
{
	set_gpio_pin_val(&data_pin_ctl.data_pin[DATA_7],enable);
}
