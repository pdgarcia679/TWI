/*
 * TWI.c
 *
 * Created: 13/05/2019 14:47:33
 * Author : Marlon Valerio
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "TWI/TWI.h"

#define RTC_slaveAddr	0b01101000
#define RTC_segAddr		0x00

uint8_t currentSeg = 0;

int main(void)
{
	cli();
    TWI_Init();
	sei();
	
	_delay_ms(10);
	
	while(TWI_startCond());
	while(TWI_sendAdrr(RTC_slaveAddr, TWI_W));
	while(TWI_write(RTC_segAddr));
	while(TWI_write(0x00));
	TWI_stopCond();
	
	_delay_ms(7000);
	
	while(TWI_startCond());
	while(TWI_sendAdrr(RTC_slaveAddr, TWI_W));
	while(TWI_write(RTC_segAddr));
	while(TWI_restrtCond());
	while(TWI_sendAdrr(RTC_slaveAddr, TWI_R));
	currentSeg = TWI_read(TWI_NACK);
	TWI_stopCond();
	
    while (1);
}

