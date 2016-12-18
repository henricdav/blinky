#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>

#define CHANNELS 3

volatile uint8_t* Port[] = {&OCR0A, &OCR0B, &OCR1B};
int Pin[] = {0, 1, 4};

int main(void)
{
	
	DDRB = 0xFF;
	// Configure counter/timer0 for fast PWM on PB0 and PB1
	TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
	TCCR0B = 0<<WGM02 | 1<<CS00 || 0<<CS01 | 1<<CS02; // Optional; already set
	// Configure counter/timer1 for fast PWM on PB4
	TCCR1 = 1<<CTC1 | 1<<PWM1A | 3<<COM1A0 | 1<<CS12 | 0<<CS11 | 1<<CS10;
	GTCCR = 1<<PWM1B | 3<<COM1B0;
	// Interrupts on OC1A match and overflow
	TIMSK = TIMSK | 1<<OCIE1A | 1<<TOIE1;
	
	int intensity[CHANNELS];
	int _intensity[CHANNELS];
	int cycle_length[CHANNELS];
	int counter[CHANNELS];
	
	for (int i = 0; i < CHANNELS; ++i)
	{
		_intensity[i] = 20;
		intensity[i] = 20;
		cycle_length[i] = 300;
		counter[i] = 0;
		*Port[i] = 255;
	}
	_delay_ms(1000);
	for (int i = 0; i < CHANNELS; ++i)
	{
		*Port[i] = 0;
		_delay_ms(500);
	}
		
	for (;;) 
	{
		for (int i = 0; i < CHANNELS; ++i)
		{
			if (counter[i] == cycle_length[i])
			{
				intensity[i] = 10 + rand() % 40;
				cycle_length[i] = 1 + rand() % 200;
				counter[i] = 0;
				*Port[i] = 255 - (3*intensity[i] + 7*_intensity[i])/10;
				_intensity[i] = (3*intensity[i] + 7*_intensity[i])/10;
			} 
		}
		_delay_ms(1);
		
		for (int i = 0; i < CHANNELS; ++i)
		{
			++counter[i];
		}
	}
	return 0;
}
