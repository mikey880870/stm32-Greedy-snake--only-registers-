#include "dma.h"

void init_dma(DMA_TypeDef* dma){
	//enable dma2
	RCC->AHB1ENR |= RCC_AHB1ENR_DMA2EN;
	// ADC3 -> DMA2 stream 0 channel 2
	// Data direction
	DMA2_Stream0->CR &= ~(3 << DMA_SxCR_DIR_Pos);
	// Select Circular mode
	DMA2_Stream0->CR |= (1 << DMA_SxCR_CIRC_Pos);
	// Enable Memory Address Increment
	DMA2_Stream0->CR |= (1 << DMA_SxCR_MINC_Pos);
	// Set the size for data 16 bit 
	DMA2_Stream0->CR |= ((1 << DMA_SxCR_MSIZE_Pos) | (1 << DMA_SxCR_PSIZE_Pos));
	// channel 2
	DMA2_Stream0->CR |= (0x2 << DMA_SxCR_CHSEL_Pos);
}

void start_dma(uint32_t scrAddress,uint32_t destAddress){
	//  Set the size of the transfer
	DMA2_Stream0->NDTR = 0x2;
	// Source address is peripheral address
	DMA2_Stream0->PAR = scrAddress;
	// memory address
	DMA2_Stream0->M0AR = destAddress;
	//start
	DMA2_Stream0->CR |= (1 << DMA_SxCR_EN_Pos);
}
