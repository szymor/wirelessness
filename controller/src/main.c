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
	
	uint8_t addressTX[5] = { 'w', 'n', 'l', 'd', '0' };
	nrf_setAddressTX(addressTX);
	_delay_ms(10);
	
	printf("Status: %x\r\n", nrf_getStatus());
	
	printf("Hello world!\r\n");
	
	uint8_t payload[4] = { 't', 'e', 's', 't' };
	
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
		/* process received data if needed
		 * currently unused, should never happen
		*/
	}
}

static void irq_init(void)
{
	/* INT1 - falling edge */
	MCUCR |= _BV(ISC11);
	GICR |= _BV(INT1);
}
