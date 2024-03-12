#include "encoder.h"

int currentRad = 0;

static void Key1_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    NVIC_InitStructure.NVIC_IRQChannel = KEY1_INT_EXTI_IRQ;
    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;

    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;

    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);
}

static void EXTI_Key1_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /*开启按键GPIO口的时钟*/
    RCC_APB2PeriphClockCmd(KEY1_INT_GPIO_CLK,ENABLE);

    /* 配置 NVIC 中断*/
    Key1_NVIC_Configuration();

    /*--------------------------KEY1配置---------------------*/
    /* 选择按键用到的GPIO */
    GPIO_InitStructure.GPIO_Pin = KEY1_INT_GPIO_PIN;
    /* 配置为浮空输入 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(KEY1_INT_GPIO_PORT, &GPIO_InitStructure);

    /* 选择EXTI的信号源 */
    GPIO_EXTILineConfig(KEY1_INT_EXTI_PORTSOURCE, \
                        KEY1_INT_EXTI_PINSOURCE);
    EXTI_InitStructure.EXTI_Line = KEY1_INT_EXTI_LINE;

    /* EXTI为中断模式 */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    /* 上升沿中断 */
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    /* 使能中断 */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

void KEY1_IRQHandler(void)
{
    //确保是否产生了EXTI Line中断
    if (EXTI_GetITStatus(KEY1_INT_EXTI_LINE) != RESET) {
        // 
        currentRad = 0U;
        //清除中断标志位
        EXTI_ClearITPendingBit(KEY1_INT_EXTI_LINE);
    }
}

void encoder_gpio_init(void){
    EXTI_Key1_Config();
    ENCODER_PORT_APBxClock_FUN(ENCODER_PORT_CLK_SRC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {
        .GPIO_Pin = ENCODER_PIN_A |ENCODER_PIN_B,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_IN_FLOATING,
    };
	GPIO_Init(ENCODER_PORT, &GPIO_InitStructure);
}
 

    
uint8_t encoder_read_position(void){
    //if(!ENCODER_READ_Z){currentRad = 0;}
    static uint8_t state = 0;
    static uint8_t lastState = 0;
//    if(currentRad > ENCODER_RESOLUTION || currentRad <(-ENCODER_RESOLUTION)){
//        currentRad = 0;
//    }  
    
    //A->B: 00-10-01-00
    //B->A: 00-01-10-00    
    switch(state){
        case 0:{
            if(ENCODER_READ_A && ENCODER_READ_B && lastState != 0){
                currentRad = currentRad + (lastState == 1?(-1):(1));
                lastState = 0;
            }
            if(!ENCODER_READ_A){state = 1U;}
            if(!ENCODER_READ_B){state = 2U;}
            break;
        }
        case 1:{
            if(ENCODER_READ_A && ENCODER_READ_B){state = 0;}
            if(ENCODER_READ_A && (!ENCODER_READ_B)){
                lastState = state; 
                state = 2U;
            }
            break;
        }
        case 2:{
            if(ENCODER_READ_A && ENCODER_READ_B){state = 0;}
            if((!ENCODER_READ_A) && ENCODER_READ_B){
                lastState = state; 
                state = 1U;
            }
            break;
        }
        default: state = 0;
    }                
    return 0;
}
   
