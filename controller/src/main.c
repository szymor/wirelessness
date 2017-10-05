#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <misc.h>
#include <serial.h>
#include <gpio.h>
#include <NRF24L01.h>

int main(void)
{
	serial_init();
	gpio_cfg_inp(B1);
	gpio_cfg_inp(B2);
	gpio_cfg_inp(B3);
	nrf_init();
	sei();
	
	printf("Hello world!\r\n");
	
	while (1)
	{
		if (0 == gpio_get(B1))
		{
			printf("Button 1 pressed.\r\n");
			_delay_ms(500);
		}
		if (0 == gpio_get(B2))
		{
			printf("Button 2 pressed.\r\n");
			_delay_ms(500);
		}
		if (0 == gpio_get(B3))
		{
			printf("Button 3 pressed.\r\n");
			_delay_ms(500);
		}
	}
	
	return 0;
}
