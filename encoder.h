#ifndef _ENCODER_H
#define _ENCODER_H
#include "stm32f10x.h"
#include "stm32f10x_exti.h"

//编码器中间按钮用中断
#define KEY1_INT_GPIO_PORT         GPIOB
#define KEY1_INT_GPIO_CLK          (RCC_APB2Periph_GPIOB\
                                    |RCC_APB2Periph_AFIO)
#define KEY1_INT_GPIO_PIN          GPIO_Pin_9
#define KEY1_INT_EXTI_PORTSOURCE   GPIO_PortSourceGPIOB
#define KEY1_INT_EXTI_PINSOURCE    GPIO_PinSource9
#define KEY1_INT_EXTI_LINE         EXTI_Line9
#define KEY1_INT_EXTI_IRQ          EXTI9_5_IRQn

#define KEY1_IRQHandler            EXTI9_5_IRQHandler


//编码器AB相用轮询
#define ENCODER_PORT                 GPIOB     
#define ENCODER_PIN_A                GPIO_Pin_7 
#define ENCODER_PIN_B                GPIO_Pin_8 
#define ENCODER_PORT_CLK_SRC         RCC_APB2Periph_GPIOB
#define ENCODER_PORT_APBxClock_FUN   RCC_APB2PeriphClockCmd

#define ENCODER_READ_A  GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN_A)
#define ENCODER_READ_B  GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN_B)
//#define ENCODER_READ_Z  GPIO_ReadInputDataBit(ENCODER_PORT, ENCODER_PIN_Z )

#define ENCODER_RESOLUTION  (19)

void encoder_gpio_init(void);
uint8_t encoder_read_position(void);

#endif
