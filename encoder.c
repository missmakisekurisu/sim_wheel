#include "encoder.h"

int currentRad = 0;

void encoder_gpio_init(void){
    //enable clock
    ENCODER_PORT_APBxClock_FUN(ENCODER_PORT_CLK_SRC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure = {
        .GPIO_Pin = ENCODER_PIN_A |ENCODER_PIN_B| ENCODER_PIN_Z,
        .GPIO_Speed = GPIO_Speed_50MHz,
        .GPIO_Mode = GPIO_Mode_IN_FLOATING,
    };
	GPIO_Init(ENCODER_PORT, &GPIO_InitStructure);
}
 

    
uint8_t encoder_read_position(void){
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
   
