#ifndef _7seg_H_
#define _7seg_H_

#include "stm32f407xx.h"
#include "usart.h"

int init_7seg(GPIO_TypeDef* gpio,int DIN,int CS,int CLK);
void send_7seg(GPIO_TypeDef* gpio,int DIN,int CS,int CLK,int address,uint8_t data);
void set_gpio(GPIO_TypeDef* gpio,int pin);
void reset_gpio(GPIO_TypeDef* gpio,int pin);
void delay_without_interrupt(int msec);
int init_button(GPIO_TypeDef* BUTTON_gpio,int BUTTON_pin);
int read_gpio(GPIO_TypeDef* gpio,int pin);
void GotoXY(uint8_t x,uint8_t y);
void SnakeXY(uint8_t (*s)[9],uint8_t Fx,uint8_t Fy);

// define Non-decode Mode constants
#define SEG_DATA_NON_DECODE_0 0b1111110
#define SEG_DATA_NON_DECODE_1 0b0110000
#define SEG_DATA_NON_DECODE_2 0b1101101
#define SEG_DATA_NON_DECODE_3 0b1111001
#define SEG_DATA_NON_DECODE_4 0b0110011
#define SEG_DATA_NON_DECODE_5 0b1011011
#define SEG_DATA_NON_DECODE_6 0b1011111 
#define SEG_DATA_NON_DECODE_7 0b1110000
#define SEG_DATA_NON_DECODE_8 0b1111111
#define SEG_DATA_NON_DECODE_9 0b1111011
#define SEG_DATA_NON_DECODE_A 0b1110111
#define SEG_DATA_NON_DECODE_B 0b0011111
#define SEG_DATA_NON_DECODE_C 0b1001110
#define SEG_DATA_NON_DECODE_D 0b0111101
#define SEG_DATA_NON_DECODE_E 0b1001111
#define SEG_DATA_NON_DECODE_F 0b1000111
#define SEG_DATA_NON_DECODE_DASH 0b0000001
#define SEG_DATA_NON_DECODE_BLANK 0b0000000

// define address constants 
#define SEG_ADDRESS_NOP 0
#define SEG_ADDRESS_DIGIT_0 1
#define SEG_ADDRESS_DIGIT_1 2
#define SEG_ADDRESS_DIGIT_2 3
#define SEG_ADDRESS_DIGIT_3 4
#define SEG_ADDRESS_DIGIT_4 5
#define SEG_ADDRESS_DIGIT_5 6
#define SEG_ADDRESS_DIGIT_6 7
#define SEG_ADDRESS_DIGIT_7 8
#define SEG_ADDRESS_DECODE_MODE 9
#define SEG_ADDRESS_INTENSITY 10
#define SEG_ADDRESS_SCAN_LIMIT 11
#define SEG_ADDRESS_SHUTDOWN 12
#define SEG_ADDRESS_DISPLAY_TEST 15


#endif