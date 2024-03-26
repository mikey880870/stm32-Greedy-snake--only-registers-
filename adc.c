#include "adc.h"

void adc_init(ADC_TypeDef* adc){
	// ADC3 PC0 PC1 (IN10 IN11)
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
	RCC->APB2ENR |= RCC_APB2ENR_ADC3EN;
	// analog mode
	GPIOC->MODER |= (3 << GPIO_MODER_MODE0_Pos);
	GPIOC->MODER |= (3 << GPIO_MODER_MODE1_Pos);
	// enable scan mode
	adc->CR1 = (0x1 << ADC_CR1_SCAN_Pos);
	// 12bit resolution
	adc->CR1 |= (0x0 << ADC_CR1_RES_Pos);
	//Continuous Conversion
	adc->CR2 = (0x1 << ADC_CR2_CONT_Pos);
	//EOC after each conversion
	adc->CR2 |= (0x1 << ADC_CR2_EOCS_Pos);
	// Data Alignment RIGHT
	adc->CR2 &= ~(0x1 << ADC_CR2_ALIGN_Pos);
	// Enable DMA for ADC
	adc->CR2 |= (0x1 << ADC_CR2_DMA_Pos);
	// Enable Continuous Request
	adc->CR2 |= (0x1 << ADC_CR2_DDS_Pos);
	// sampling time
	adc->SMPR1 |= ((0x3 << ADC_SMPR1_SMP10_Pos) | (0x3 << ADC_SMPR1_SMP11_Pos));
	adc->SMPR1 |= (0x3 << ADC_SMPR1_SMP10_Pos);
	//Set the Regular channel sequence length in ADC_SQR1
	adc->SQR1 |= (0x1 << ADC_SQR1_L_Pos);
	// Channel Sequence
	adc->SQR3 |= (10 << ADC_SQR3_SQ1_Pos);
	adc->SQR3 |= (11 << ADC_SQR3_SQ2_Pos);
	// enable adc
	adc->CR2 |= (1 << ADC_CR2_ADON_Pos);
	delay_ms(2000);
}
void adc_psc(ADC_Common_TypeDef* adc){
	// ADC prescaler divide two
	adc->CCR |= (0x0 << ADC_CCR_ADCPRE_Pos);
}

void start_adc(ADC_TypeDef* adc){
	adc->SR = 0;
	adc->CR2 |= (1 << ADC_CR2_SWSTART_Pos);
}
