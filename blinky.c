#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define CHANNELS 3

void delay_ms(uint16_t count) {
	while(count--) {
		_delay_ms(1);
	}
}

void delay_us(uint16_t count) {
	while(count--) {
		_delay_us(1);
	}
}

int pwmLight(int duty_cycle[])
{
	int time_period = 100; //us
	int on_time[CHANNELS];
	for (int i = 0; i < CHANNELS; ++i)
	{
		on_time[i] = time_period * duty_cycle[i] / 100;
	}
	
	PORTB = 0b00111111;
	for (int i = 0; i < time_period; ++i)
	{
		if (i == on_time[0])
			PORTB -= 10000;
		if (i == on_time[1])
			PORTB -= 1000;
		if (i == on_time[2])
			PORTB -= 100;
		_delay_us(1);
	}

    return 0;
}


int main(void)
{
	DDRB = 0xFF; // PORTB is output, all pins
	PORTB = 0x00; // Make pins low to start
	
	int duty_cycle[CHANNELS];
	int cycle_length[CHANNELS];
	int counter[CHANNELS];
	
	for (int i = 0; i < CHANNELS; ++i)
	{
		duty_cycle[i] = 20;
		cycle_length[i] = 300;
		counter[i] = 0;
	}
		
	for (;;) 
	{
		for (int i = 0; i < CHANNELS; ++i)
		{
			if (counter[i] == cycle_length[i])
			{
				duty_cycle[i] = rand() % 100;
				cycle_length[i] = 50 + rand() % 400;
				counter[i] = 0;
			} 
		}
		pwmLight(duty_cycle);
		//PORTB = 0b00111111;
		//_delay_ms(1000);
		//PORTB -= 10000;
		//_delay_ms(1000);
		//PORTB -= 1000;
		//_delay_ms(1000);
		//PORTB -= 100;
		//_delay_ms(1000);
		

		for (int i = 0; i < CHANNELS; ++i)
		{
			++counter[i];
		}
	}
	return 0;
}
