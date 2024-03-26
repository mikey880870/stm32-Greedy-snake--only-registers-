#include "7seg.h"
#include "snake_helperFunc.h"
#include "delay.h"
#include "usart.h"
#include "adc.h"
#include "dma.h"
#include "IWDG.h"

#define pc_mcu_uart USART2

#define BUTTON_gpio GPIOA
#define BUTTON_pin 0
#define SEG_gpio GPIOA
#define DIN_pin 5
#define CS_pin 6
#define CLK_pin 7

struct _food food_s;
struct _snake snake_s;

short int dir = 6;  // up 8 down 2 left 4 right 6
short int eatFlag = 0;

volatile uint16_t Rxdata[2] = {0};

int fputc(int ch, FILE* stream){
	USART_sendByte(USART2,ch);
	return ch;
}
	
int main(void){
	food_source();
	init_uart(pc_mcu_uart);	
	init_dma(adc_dma);
	adc_psc(ADC123_COMMON);
	adc_init(hw504_adc);
	start_adc(hw504_adc);
	start_dma((uint32_t)&ADC3->DR,(uint32_t)Rxdata);
	delay_ms(100);
	// T = 1/32 * 32 * 5000 = 5s
	IWDG_init(0x03, 5000);

	if(init_7seg(SEG_gpio,DIN_pin,CS_pin,CLK_pin) != 0){
		return -1;
	}
	
	if(init_button(BUTTON_gpio,BUTTON_pin) != 0){
		return -1;
	}

	bornSanke();		
	while(1){		
		checkDir();
		if(snakeAlive() != 1){
			break;
		}
		createFood();
		delay_ms(snake_s.speed);
	}
	return 0;
}
