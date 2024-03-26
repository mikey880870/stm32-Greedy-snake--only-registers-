#ifndef _DMA_H_
#define _DMA_H_

#include "stm32f407xx.h"
#define adc_dma DMA2

void init_dma(DMA_TypeDef* dma);
void start_dma(uint32_t scrAddress,uint32_t destAddress);

#endif