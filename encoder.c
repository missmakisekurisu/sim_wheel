#include "encoder.h"

uint8_t currentRad = 0;

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
    static uint8_t flag = 0;
   if(currentRad > 18){
       currentRad = 0;
   }   
   switch(flag){
       case 0:{
           if((!ENCODER_READ_A) && (!ENCODER_READ_B)){
               flag = 1U;
               currentRad ++;
           }
           break;
       }
       case 1:{
           if((ENCODER_READ_A) && (ENCODER_READ_B)){
               flag = 0U;
           }
           break;
       }
   }       
   return currentRad;
}
   
