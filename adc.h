#ifndef _ADC_H_
#define _ADC_H_
#include "stm32f407xx.h"
#include "delay.h"
#define hw504_adc ADC3

void adc_init(ADC_TypeDef* adc);
void start_adc(ADC_TypeDef* adc);
void adc_psc(ADC_Common_TypeDef* adc);

#endif
