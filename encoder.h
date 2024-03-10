#ifndef _ENCODER_H
#define _ENCODER_H
#include "stm32f10x.h"

#define ENCODER_PORT                 GPIOB     
#define ENCODER_PIN_A                GPIO_Pin_8 
#define ENCODER_PIN_B                GPIO_Pin_9 
#define ENCODER_PIN_Z                GPIO_Pin_5 
#define ENCODER_PORT_CLK_SRC         RCC_APB2Periph_GPIOB
#define ENCODER_PORT_APBxClock_FUN   RCC_APB2PeriphClockCmd

#define ENCODER_READ_A  GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN_A)
#define ENCODER_READ_B  GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN_B)
#define ENCODER_READ_Z  GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN_Z )

void encoder_gpio_init(void);
uint8_t encoder_read_position(void);

#endif
