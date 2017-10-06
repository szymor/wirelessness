#include <avr/interrupt.h>
#include <util/delay.h>

#include <stdio.h>
#include <string.h>
#include <inttypes.h>

#include <misc.h>
#include <serial.h>
#include <gpio.h>
#include <NRF24L01.h>

static void irq_init(void);

int main(void)
{
	serial_init();
	gpio_cfg_inp(B1);
	gpio_cfg_inp(B2);
	gpio_cfg_inp(B3);
	gpio_cfg_out(LED);
	gpio_cfg_inp(IRQ);
	
	nrf_init();
	_delay_ms(100);
	nrf_configure();
	irq_init();
	
	sei();
	
	uint8_t addressRX[5] = { 'c', 't', 'l', 'r', '1' };
	uint8_t addressTX[5] = { 'd', 'n', 'g', 'l', '1' };
	nrf_setAddressRX(addressRX);
	nrf_setAddressTX(addressTX);
	_delay_ms(10);
	
	printf("Status: %x\r\n", nrf_getStatus());
	
	printf("Hello world!\r\n");
	
	uint8_t payload[] = { 't', 'e', 's', 't' };
	
	payload[0] = 0xff;
	while (1)
	{
		payload[0] = 0xff;
		
		if (0 == gpio_get(B1))
		{
			payload[0] &= ~_BV(BTN_START);
		}
		if (0 == gpio_get(B2))
		{
			payload[0] &= ~_BV(BTN_A);
		}
		if (0 == gpio_get(B3))
		{
			payload[0] &= ~_BV(BTN_RIGHT);
		}

		nrf_powerUpRX();
		nrf_powerUpTX();
		nrf_transmit( payload );
		
		_delay_ms(10);

		/* Computer keyboard control stub:
		switch (fgetc(stdin))
		{
			case 'a': payload[0] &= ~_BV(1); break;
			case 'd': payload[0] &= ~_BV(0); break;
			case 'w': payload[0] &= ~_BV(3); break;
			case 's': payload[0] &= ~_BV(2); break;
			case '\n': payload[0] &= ~_BV(4); break;
			case 'p': payload[0] &= ~_BV(5); break;
			case 'n': payload[0] &= ~_BV(7); break;
			case 'm': payload[0] &= ~_BV(6); break;
			case ' ': payload[0] = 0xff; break;
		}

		nrf_powerUpRX();
		nrf_powerUpTX();
		nrf_transmit( payload );
		*/
	}
	
	return 0;
}

ISR(INT1_vect)
{
	static uint8_t status;
	static uint8_t buff[NRF_PAYLOAD_SIZE];
	status = nrf_getStatus();
	
	if (status & _BV(RX_DR))
	{
		nrf_getData(buff, NRF_PAYLOAD_SIZE);
	}
}

static void irq_init(void)
{
	/* INT1 - falling edge */
	MCUCR |= _BV(ISC11);
	GICR |= _BV(INT1);
}
