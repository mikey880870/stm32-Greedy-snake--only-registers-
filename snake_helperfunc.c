#include "snake_helperFunc.h"

void food_source(void){
	timer_enable(TIM2);
	timer_init(TIM2,16000,1000);    // Counter =  (PSC+1) * (1/Fclk)  (psc->16bit)
	timer_start(TIM2);
	delay_ms(10);
}

uint8_t foodXY(void){
	uint8_t  pos = (TIM2 -> CNT) % MAPSIZE;
	return pos;
}

void bornSanke(void){
	//create first food	
	food_s.x = foodXY();
	food_s.y = foodXY();
	// init snake in middle
	snake_s.xy[MAPSIZE/2][MAPSIZE/2] = 1;
	snake_s.body[0] = (MAPSIZE/2)*10+(MAPSIZE/2);
	// init snake config
	snake_s.len = 4;
	snake_s.speed = 5000;

	for(uint8_t i = 1;i < snake_s.len;i++){
		uint8_t x = snakeBody_xpos(snake_s.body[i-1]) + 1;
		uint8_t y = snakeBody_ypos(snake_s.body[0]);
		snake_s.xy[x][y] = 1;
		snake_s.body[i] = x*10+y;
	}
	SnakeXY(snake_s.xy,food_s.x,food_s.y);
}

uint8_t snakeBody_xpos(int pos){
	return pos/10;
}

uint8_t snakeBody_ypos(int pos){
	return pos%10;
}

void change_dir(void){
	printf("x = %d\n",Rxdata[0]);	
	printf("y = %d\n",Rxdata[1]);
	if(Rxdata[0] < 500 && Rxdata[1] > 2000){
		dir = 4;
	}
	if(Rxdata[0] > 3300 && Rxdata[1] > 2000){
		dir = 6;
	}
	if(Rxdata[1] < 500 && Rxdata[0] > 2000){
		dir = 8;
	}
	if(Rxdata[1] > 3300 && Rxdata[1] > 2000){
		dir = 2;
	}
}


void checkDir(void){
	short int pre_dir = dir;
	change_dir();
	// clear snake tail
	if(eatFlag == 0){
			uint8_t x = snakeBody_xpos(snake_s.body[snake_s.len - 1]);
			uint8_t y = snakeBody_ypos(snake_s.body[snake_s.len - 1]);
			snake_s.xy[x][y] = 0;
		}
		//forward/*
		for(uint8_t i = snake_s.len - 1;i > 0;i--){
			// original clear
			uint8_t x = snakeBody_xpos(snake_s.body[i]);
			uint8_t y = snakeBody_ypos(snake_s.body[i]);
			//snake_s.xy[x][y] = 0;
			// forward
			x = snakeBody_xpos(snake_s.body[i - 1]);
			y = snakeBody_ypos(snake_s.body[i - 1]);
			snake_s.xy[x][y] = 1;
			snake_s.body[i] = x*10+y;
		}
		SnakeXY(snake_s.xy,food_s.x,food_s.y);

		
		if(pre_dir == 8 && dir == 2){
			dir = pre_dir;
		}
		else if(pre_dir == 2 && dir == 8){
			dir = pre_dir;
		}
		else if(pre_dir == 4 && dir == 6){
			dir = pre_dir;
		}
		else if(pre_dir == 6 && dir == 4){
			dir = pre_dir;
		}
		//head pos
		uint8_t x = snakeBody_xpos(snake_s.body[0]);
		uint8_t y = snakeBody_ypos(snake_s.body[0]);
		snake_s.xy[x][y] = 0;
		
		switch(dir){
			case 8:
				// original clear
				y--;
				snake_s.xy[x][y] = 1;
				snake_s.body[0] = x*10+y;
				break;
			case 2:
				y++;
				snake_s.xy[x][y] = 1;
				snake_s.body[0] = x*10+y;
				break;
			case 4:
				x++;
				snake_s.xy[x][y] = 1;
				snake_s.body[0] = x*10+y;
				break;
			case 6:
				x--;
				snake_s.xy[x][y] = 1;
				snake_s.body[0] = x*10+y;
				break;
		}
		//SnakeXY(snake_s.xy,food_s.x,food_s.y);
		eatFlag = 0;
}

void createFood(void){
	//head pos 
	uint8_t headX = snakeBody_xpos(snake_s.body[0]);
	uint8_t headY = snakeBody_ypos(snake_s.body[0]);
	if(headX == food_s.x && headY == food_s.y){
			while(1){
				short int flag = 0;
				food_s.x = foodXY();
				food_s.y = foodXY();
				for(uint8_t i = 0;i < snake_s.len;i++){
						uint8_t x = snakeBody_xpos(snake_s.body[i]);
						uint8_t y = snakeBody_ypos(snake_s.body[i]);
					if(x == food_s.x && y == food_s.y){
							break;
						}
					flag = 1;
					}
				if(flag != 0){
					break;
				}
			}
			SnakeXY(snake_s.xy,food_s.x,food_s.y);
			snake_s.len++;
			eatFlag = 1;
		}
}
	
short int snakeAlive(void){
		// 1 alive 0 died
		uint8_t headX = snakeBody_xpos(snake_s.body[0]);
		uint8_t headY = snakeBody_ypos(snake_s.body[0]);
		if(headX == 0 || headX == MAPSIZE){
			return 0;
		}
		if(headY == 0 || headY == MAPSIZE){
			return 0;
		}
		for(int i = 1;i < snake_s.len;i++){
			uint8_t x = snakeBody_xpos(snake_s.body[i]);
			uint8_t y = snakeBody_ypos(snake_s.body[i]);
			if(x == headX && y == headY){
				return 0;
			}
		}
		return 1;
}

