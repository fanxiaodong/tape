#include "ALL_Includes.h"//包含所需的头文件

void ALL_Config(void);

extern int gpio_bit_val;



#if 0
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
	/*
	for(i = 0 ; i < arry_size(bar_code); i++){
		printf_bit(bar_code[i]);
	}
	*/
	board_ADC_init();

	code_val = 0;

	int cnt = 0;

	unsigned int step_val_old = -1, step_val_new;
	int dir_tmp = 1;
	
	float val_inch = 0.00;

	#define INCH_CM 2.54

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
		
				if((step_val_old - step_val_new > 50)){
					val_inch = 0.0176 * (step_val_new + 64 - step_val_old) + val_inch;
					dir_tmp = 1;
					cnt++;
				}else{

					dir_tmp = 0;
					cnt--;
				}
			}else{
			
				dir_tmp = 1;
				cnt++;
			}
			
			val_inch = 0.0176 * (step_val_new - step_val_old) + val_inch;
			
			step_val_old = step_val_new;
			
			printf("%02d %02d %4d %f %f\n",cnt,step_val_new,adc_val_tmp,val_inch,val_inch*INCH_CM);
			
			ret_val = Qr_code_check(adc_val_tmp,dir_tmp);
			if(ret_val == CONTINUE ){
				//printf("continue...\n");
			}else if(ret_val == START){
				
				printf("%d 0x%08x\n",cnt,Qr_code);
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
	
}

#else
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
	/*
	for(i = 0 ; i < arry_size(bar_code); i++){
		printf_bit(bar_code[i]);
	}
	*/
	board_ADC_init();

	code_val = 0;

	int cnt = 0;

	unsigned int step_val_old = -1, step_val_new;
	int dir_tmp = 1;
	
	float val_inch = 0.00;

	#define INCH_CM 2.54

	while(1){

		gpio_bit_val = get_code_input();
		
		if( code_val != gpio_bit_val ){
		
			code_val = gpio_bit_val;	
			
			step_val_new = get_10_val(gpio_bit_val);
			
			while( is_ADC_end() != 1){
				printf("---->\n");
			}
			adc_val_tmp = get_vol_val();			
		 	
			bar_code_proc(step_val_new,adc_val_tmp);
			inch_proc(step_val_new);
		}

	}
	
}
#endif
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







