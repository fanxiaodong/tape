#include <stdio.h>
#include "USART1.h"

#define USRT_TX_PIN GPIO_Pin_9
#define USRT_RX_PIN GPIO_Pin_10
#define USRT_TX_PIN_SRC GPIO_PinSource9
#define USRT_RX_PIN_SRC GPIO_PinSource10

//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
}; 
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{  
  while(!((USART1->ISR)&(1<<7))){}
  USART1->TDR=ch;
  return (ch);
}
#endif 

GPIO_InitTypeDef GPIO_InitStructure = {
 .GPIO_Pin = USRT_TX_PIN | USRT_RX_PIN,
 .GPIO_Mode = GPIO_Mode_AF,
 .GPIO_Speed = GPIO_Speed_50MHz,
 .GPIO_OType = GPIO_OType_PP,
 .GPIO_PuPd = GPIO_PuPd_UP,
 };
 
USART_InitTypeDef USART_InitStructure = {
 .USART_BaudRate = 115200,
 .USART_WordLength = USART_WordLength_8b,
 .USART_StopBits = USART_StopBits_1,
 .USART_Parity = USART_Parity_No,
 .USART_HardwareFlowControl = USART_HardwareFlowControl_None,
 .USART_Mode = USART_Mode_Rx | USART_Mode_Tx,
};

NVIC_InitTypeDef NVIC_InitStruct = {
 .NVIC_IRQChannel = USART1_IRQn,
 .NVIC_IRQChannelPriority = 0x02,
 .NVIC_IRQChannelCmd = ENABLE,
};

/* USART初始化 */
void USART1_Init(uint32_t baud)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);  //使能GPIOA的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);//使能USART的时钟
	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOA, USRT_TX_PIN_SRC, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, USRT_RX_PIN_SRC, GPIO_AF_1);
	
	USART_InitStructure.USART_BaudRate = baud;
	USART_Init(USART1, &USART_InitStructure);		
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);          
	USART_Cmd(USART1, ENABLE);
	NVIC_Init(&NVIC_InitStruct);
}

//=============================================================================
//文件名称：
//功能概要：USART1中断函数
//参数说明：无
//函数返回：无
//=============================================================================
static uint8_t rec_buff[32];
static uint8_t rec_cnt = 0;

void USART1_IRQHandler(void)
{ 
	uint16_t ret;
//	uint32_t cmd;
  if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
  {
  	
  	 ret = USART_ReceiveData(USART1);

	if(ret == 0x0a){
		rec_buff[rec_cnt] = (ret & 0xff);
		rec_cnt = 0;
		
		debug("\n ret ----> %s \n",rec_buff);  	 	
		#if 0	
		cmd = uart_str2cmd((char *)rec_buff);
		
		cmd = uart_cmd_proc(cmd);
		
		if(cmd){
			printf("\ncmd error\n");
		}else{
			printf("\ncmd OK\n");
		}
		#endif
		memset(rec_buff, 0, sizeof(rec_buff));
	}else{
	
		USART_SendData(USART1,ret);
		rec_buff[rec_cnt] = ret;
		rec_cnt++;
	}
  	
    /* USART_SendData(USART1,);
	 while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
	*/
  }
}

