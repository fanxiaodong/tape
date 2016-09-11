#ifndef __board_adc__
#define __board_adc__
#include "ALL_Includes.h"


#define ADC_SampleTime ADC_SampleTime_7_5Cycles
//PB0 ADC_IN8
//#define ADC1_ch1_PIN GPIO_Pin_0
#define ADC1_ch1_PIN GPIO_Pin_4
#define ADC1_ch6_PIN GPIO_Pin_6

#define ADC1_CLK RCC_APB2Periph_ADC1
#define ADC1_DEV ADC1
typedef struct 
{
	uint32_t  ADC_clk;//adc 时钟选择
	gpio_t   ADC_GPIO_pin; //adc 外部链接管脚参数
	uint32_t ADC_ch;//adc 通道	
	ADC_TypeDef *ADC_dev;//adc 设备
	ADC_InitTypeDef ADC_dev_param; //adc 参数
	uint32_t use_dma;//使用dma
}ADC_dev_t;



void board_ADC_init(void) ;
void board_ADC_deinit(void);

int is_ADC_end(void);
uint16_t get_ADC_val(void);
uint16_t get_vol_val(void);



#endif
