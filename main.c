#include "stm32f10x.h"
#include "encoder.h"


int main(void){
    encoder_gpio_init();
    for(;;){
        encoder_read_position();
    }
    return 0;
}
