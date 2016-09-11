#ifndef __gpio_h__
#define __gpio_h__
#include "ALL_Includes.h"
//board_gpio.h

typedef struct _gpio_t
{
	uint32_t gpio_clk;
	GPIO_TypeDef *gpio_port;
	GPIO_InitTypeDef init_val;
	uint32_t status;
	uint8_t gpio_af;
	uint8_t res[3];
}gpio_t;

typedef struct{
	gpio_t *pgpio_info;
	EXTI_InitTypeDef exti_init_val;
	NVIC_InitTypeDef nvic_init_val;
}gpio_interrupt_t;


int init_gpio(gpio_t *pgpio);
void set_gpio_pin_val(gpio_t *pgpio, uint32_t val);
int get_gpio_pin_val(gpio_t *pgpio);
int get_gpio_group_val(gpio_t *pgpio,uint32_t mask);
void gpio_interrupt_Config(gpio_interrupt_t *pgi);



#endif
