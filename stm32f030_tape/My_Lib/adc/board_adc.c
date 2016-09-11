#include "ALL_Includes.h"

ADC_dev_t ADC_dev_1 = {
 .ADC_clk = ADC1_CLK,
 .ADC_GPIO_pin={
	 .gpio_clk = RCC_AHBPeriph_GPIOA,
	 .gpio_port = GPIOA,
	 .init_val ={
	 	.GPIO_Pin = ADC1_ch6_PIN,
		.GPIO_Mode	= GPIO_Mode_AN,
		.GPIO_PuPd	= GPIO_PuPd_NOPULL,
	 	},
	 .status = 0,
 	},
 	
 .ADC_ch = ADC_Channel_6,
 .ADC_dev = ADC1_DEV,
 .ADC_dev_param = {
	 .ADC_Resolution = ADC_Resolution_12b,
	 .ADC_ContinuousConvMode = ENABLE, 
	 .ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None,
	 .ADC_DataAlign = ADC_DataAlign_Right,
	 .ADC_ScanDirection = ADC_ScanDirection_Upward,
 	},
 #ifdef USE_ADC_ANGLE_D	
 .use_dma = 1,	
 #else
 .use_dma = 0,
 #endif
};


void board_ADC_init(void) {

  ADC_dev_t *pdev = &ADC_dev_1;
  
  /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(pdev->ADC_GPIO_pin.gpio_clk, ENABLE);
  
  /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(pdev->ADC_clk, ENABLE);
  
  GPIO_Init(pdev->ADC_GPIO_pin.gpio_port, &pdev->ADC_GPIO_pin.init_val);
  
  /* ADCs DeInit */  
  ADC_DeInit(pdev->ADC_dev);
  
  ADC_Init(pdev->ADC_dev, &pdev->ADC_dev_param); 
  
  /* Convert the ADC1 Channel 11 with 239.5 Cycles as sampling time */ 
  ADC_ChannelConfig(pdev->ADC_dev, pdev->ADC_ch, ADC_SampleTime);

  #if 0
  /* Convert the ADC1 temperature sensor  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(pdev->ADC_dev, ADC_Channel_TempSensor , ADC_SampleTime);  
  ADC_TempSensorCmd(ENABLE);
  
  /* Convert the ADC1 Vref  with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(pdev->ADC_dev, ADC_Channel_Vrefint , ADC_SampleTime); 
  ADC_VrefintCmd(ENABLE);
  
  /* Convert the ADC1 Vbat with 55.5 Cycles as sampling time */ 
  ADC_ChannelConfig(pdev->ADC_dev, ADC_Channel_Vbat , ADC_SampleTime);  
  ADC_VbatCmd(ENABLE);
  #endif
  
  /* ADC Calibration */
  ADC_GetCalibrationFactor(pdev->ADC_dev);
  
  if(pdev->use_dma){
	/* ADC DMA request in circular mode */
	ADC_DMARequestModeConfig(pdev->ADC_dev, ADC_DMAMode_Circular);

	/* Enable ADC_DMA */
	ADC_DMACmd(pdev->ADC_dev, ENABLE);  
  }
   
  /* Enable the ADC peripheral */
  ADC_Cmd(pdev->ADC_dev, ENABLE);      
  /* Wait the ADRDY flag */
  while(!ADC_GetFlagStatus(pdev->ADC_dev, ADC_FLAG_ADRDY)); 
  
  /* ADC1 regular Software Start Conv */ 
  ADC_StartOfConversion(pdev->ADC_dev);


  if(pdev->use_dma){
  //	ADC_DMA_init();
  }
  
}


void board_ADC_deinit(void) {
	ADC_dev_t *pdev = &ADC_dev_1;
	
	ADC_StopOfConversion(pdev->ADC_dev);
	ADC_Cmd(pdev->ADC_dev, DISABLE); 	
	ADC_DeInit(pdev->ADC_dev);
	
	if(pdev->use_dma){
	
	  /* Enable ADC_DMA */
	  ADC_DMACmd(pdev->ADC_dev, DISABLE);  
	}

}



int is_ADC_end(void){
	ADC_dev_t *pdev = &ADC_dev_1;

	if(ADC_GetFlagStatus(pdev->ADC_dev, ADC_FLAG_EOC)){
		return 1;
	}else{
		return 0;
	}

}

uint16_t get_ADC_val(void){
	ADC_dev_t *pdev = &ADC_dev_1;
	uint16_t val;
	
	val =  ADC_GetConversionValue(pdev->ADC_dev);
	
	if(pdev->ADC_dev_param.ADC_DataAlign == ADC_DataAlign_Right){
		val = val & (~(0xf << 12));
	}else {
		val = val >> 4;	
	}
	
	return val;
}

uint16_t get_vol_val(void){

	uint16_t val = get_ADC_val();
	uint16_t angle_val = (val * 3300)/4096;
	//printf("angle %d \n",angle_val);
	return angle_val;
}


