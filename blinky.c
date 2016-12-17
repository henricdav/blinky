#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

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

int pwmLight(int duty_cycle)
{
	int time_period = 100; //us
	int on_time = time_period * duty_cycle / 100;
	int off_time = time_period - on_time;
	
	PORTB = 0b00010000;
	delay_us(on_time);

	PORTB = 0b00000000;
	delay_us(off_time);

    return 0;
}


int main(void)
{
	DDRB = 0xFF; // PORTB is output, all pins
	PORTB = 0x00; // Make pins low to start

	for (;;) 
	{
		int duty_cycle = 10 + rand() % 30;
		int cycle_length = 200 + rand() % 500;
		for (int i = 0; i < cycle_length; ++i)
		{
			pwmLight(duty_cycle);
		}	
		
		//for (int percentage = 0; percentage < 100; percentage++)
		//{
		//	for (int i = 0; i < 10; ++i)
		//	{
		//		pwmLight(percentage);
		//	}
		//}
	}
	return 0;
}
