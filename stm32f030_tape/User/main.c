#include "ALL_Includes.h"//包含所需的头文件

void ALL_Config(void);

extern int gpio_bit_val;



int main(void)
{	
	int code_val , i,adc_val_tmp;
	int new_code,ag = 0;
	int ret_val,Qr_code=0;
	ALL_Config();
	
	init_code_input();
	
	for(i = 0 ; i < 64; i++){
		code_val = binToGray(i);
		printf("+++i = %d \t",i);
		printf_bit(code_val);
		code_val = grayToBin(code_val);
		printf("---i = %d \t",code_val);
		printf_bit(code_val);
	}

	board_ADC_init();

	code_val = 0;

	int cnt = 0;

	unsigned int step_val_old = -1, step_val_new;
	
	while(1){

		gpio_bit_val = get_code_input();
		
		if( code_val != gpio_bit_val ){
		
			code_val = gpio_bit_val;	
			
			step_val_new = get_10_val(gpio_bit_val);
			
			while( is_ADC_end() != 1){
				printf("---->\n");
			}

			adc_val_tmp = get_vol_val();
			
			if(step_val_new < step_val_old){
		
				if((step_val_old - step_val_new > 50) ){
					step_val_old = step_val_new;
					//printf("restart.....\n");
				}else{
					//printf("continue ... step %d %d %d\n",cnt,step_val_new,adc_val_tmp);
					step_val_old = step_val_new;
					continue;
				}
			}

			step_val_old = step_val_new;
			
			//printf("%d %d %d\n",cnt,step_val_new,adc_val_tmp);
			
			cnt++;
			
			ret_val = Qr_code_check(adc_val_tmp,1);
			if(ret_val == CONTINUE ){
				//printf("continue...\n");
			}else if(ret_val == START){
				
				printf("start...0x%08x\n",Qr_code);
				Qr_code = 0;
				cnt = 0;
			}else if(ret_val == GET_ERROR){
				//printf("GET_ERROR...\n");
			}else{
				Qr_code = ret_val|(Qr_code<<1);
				//printf("get val %d...\n",ret_val);
			}
			
			
		 
		}

	}
	
	#if 0
	while(1){
		LED_ON();
		//delay_ms(10);
		
		new_code = get_code_input();
		if(new_code != code_val){
			code_val = new_code;
			LED_OFF();
			//printf("---> 0x%x\n",code_val);
			printf_bit(code_val);
			set_infrared_en(0);
			printf("infrared = ");
			ag = get_Infrared_input();
			printf("%d \n",ag);
			set_infrared_en(1);
			//i = gray_to_binary((uint16_t)code_val);
			//printf("bin = %d |\t",i);
			//i = grayToBin(code_val);
			#if 0
			if(gray2index[code_val] == 0){
				ag++;
				ag = ag % 6;
			}
			
			printf("%d %d\n",gray2index[code_val],(gray2index[code_val] + ag*64)*15 / 16);
			#endif
		}
		//delay_ms(10);
	}
	#endif
}

/************************
函数功能：总初始化
输入参数：无
输出参数：无
备    注：无
************************/
void ALL_Config(void)
{
    Delay_Init(8);
	LED_Init();
	USART1_Init(115200);
}







