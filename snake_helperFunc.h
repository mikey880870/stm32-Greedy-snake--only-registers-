#ifndef _SNAKE_HELPERFUNC_H_
#define _SNAKE_HELPERFUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include "7seg.h"
#include "food_timer.h"
#include "usart.h"
#include "delay.h"

#define SNAKE_SIZE 63
#define MAPSIZE 9

struct _food{
	uint8_t x;
	uint8_t y;
};

struct _snake{
	int speed;
	int len;
	int body[SNAKE_SIZE];
	uint8_t xy[MAPSIZE][MAPSIZE];
};

extern struct _food food_s;
extern struct _snake snake_s;
extern short int dir;
extern short int eatFlag;
extern volatile uint16_t Rxdata[2];

void bornSanke(void);
void checkDir(void);
void createFood(void);
void food_source(void);
void change_dir(void);


uint8_t foodXY(void);

short int snakeAlive(void);
uint8_t snakeBody_xpos(int pos);
uint8_t snakeBody_ypos(int pos);

#endif
