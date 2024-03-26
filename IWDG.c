#include "IWDG.h"

void IWDG_init(uint8_t psc,uint16_t reload){
	// open LSI
    RCC->CSR |= RCC_CSR_LSION;          
	// waiting LSI stable
    while (!(RCC->CSR & RCC_CSR_LSIRDY));
	// unlock protection
    IWDG->KR = 0x5555;  
	// setting psc
    IWDG->PR = psc;
	//setign reload	
    IWDG->RLR = reload;
	// waiting update
	//while (IWDG->SR != 0);  
	// feed dog
    IWDG->KR = 0xAAAA;            
	// enable IWDG
    IWDG->KR = 0xCCCC;            
}

void feed_dog(void){
	IWDG->KR = 0xAAAA;            
}