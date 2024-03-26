#include "7seg.h"
#include "stm32f407xx.h"

void delay_without_interrupt(int msec){
	int loop_cnt = 500*msec;
	while(loop_cnt){
		loop_cnt--;
	}
	return;
}

void set_gpio(GPIO_TypeDef* gpio,int pin){
	gpio->BSRR |= (1 << pin);
}

void reset_gpio(GPIO_TypeDef* gpio,int pin){
	gpio->BSRR |= (1 << (pin + 16));
}

int init_button(GPIO_TypeDef* BUTTON_gpio,int BUTTON_pin){
	if(BUTTON_gpio == GPIOA){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
	else{
		return -1;
	}
	BUTTON_gpio->MODER &= ~(0b11 << (2*BUTTON_pin));
	BUTTON_gpio->MODER &= ~(0b00 << (2*BUTTON_pin));
	return 0;
}

int read_gpio(GPIO_TypeDef* gpio,int pin){
	return (gpio-> IDR >> pin) & 1;       
}

int init_7seg(GPIO_TypeDef* gpio,int DIN,int CS,int CLK){
	if(gpio==GPIOA){
		RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	}
	else{
		return -1;
	}
	//output mode
	gpio->MODER &= ~(0b11 << (2*DIN));
	gpio->MODER |= (0b01 << (2*DIN));
	gpio->MODER &= ~(0b11 << (2*CS));
	gpio->MODER |= (0b01 << (2*CS));
	gpio->MODER &= ~(0b11 << (2*CLK));
	gpio->MODER |= (0b01 << (2*CLK));
	delay_without_interrupt(1000);
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_DISPLAY_TEST,0x01); //DISPLAY TEST OPEN
	delay_without_interrupt(1000);
	send_7seg(gpio,DIN,CS,CLK,SEG_ADDRESS_DISPLAY_TEST,0x00); //DISPLAY TEST CLOSE
	for(uint8_t i = 1;i <= 8;i++){
			GotoXY(0,i);
		}
	return 0;
}

void send_7seg(GPIO_TypeDef* gpio,int DIN,int CS,int CLK,int address,uint8_t data){
	int payload = ((address & 0xFF)<<8)|(data&0xFF); //command (D8~D15),data (D0~D7)
	int total_cylces = 16+1;
	for(int i = 1;i <= total_cylces;i++){
		reset_gpio(gpio,CLK);
		
		if(((payload>>(total_cylces-1-i))&0x1) && i!=total_cylces){
			set_gpio(gpio,DIN);
		}
		else{
			reset_gpio(gpio,DIN);
		}
		
		if(i == total_cylces){
			set_gpio(gpio,CS);
		}
		else{
			reset_gpio(gpio,CS);
		}
		
		set_gpio(gpio,CLK);
	}
	return;
}
//203
void GotoXY(uint8_t x,uint8_t y){
	uint8_t map_x = 1;
	if(x < 1){
		map_x = 0;
	}
	else{
		for(x;x > 1;x--){
			map_x = map_x << 1; 
		}
	}
	send_7seg(GPIOA,5,6,7,y,map_x);
}

void SnakeXY(uint8_t (*s)[9],uint8_t Fx,uint8_t Fy){
	for(uint8_t y = 1;y <= 8;y++){
			uint8_t temp = 0;
		for(uint8_t x = 8;x >= 1;x--){
			temp = temp << 1;
			if(Fx == x && Fy == y){
				temp |= 1;
			}
			temp |= (s[x][y] & 1);
		}
		send_7seg(GPIOA,5,6,7,y,temp);
	}
}