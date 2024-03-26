#ifndef _IWDG_H_
#define _IWDG_H_
#include "stm32f407xx.h"

void IWDG_init(uint8_t psc,uint16_t reload);
void feed_dog(void);

#endif