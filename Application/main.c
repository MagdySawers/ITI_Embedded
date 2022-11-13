/*
 * ITI_Embedded.c
 *
 * Created: 11/12/2022 8:57:23 PM
 * Author : dell
 */ 
#define F_CPU 16000000UL
#include <util/delay.h>

#include "BIT_MATH.h"
#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_Interface.h"
#include "ADC_Interface.h"
#include <avr/interrupt.h>
void ADC_NotFunc (void);

u16 APP_u16ADCReading;


int main(void)
{  
	 
	PORT_voidInit();
	ADC_voidInit();
    sei();
    while (1) 
    {
		
		ADC_u8GetChannelReading_A_Synch(1,&APP_u16ADCReading,&ADC_NotFunc);
		
	
    }
}

void ADC_NotFunc (void)
{
	
	DIO_SetPortValue(DIO_u8PORTC,APP_u16ADCReading);
	
}