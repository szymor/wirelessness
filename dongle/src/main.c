#include <inttypes.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <misc.h>
#include <gpio.h>
#include <NRF24L01.h>

/*
 * shift order:
 * A B Select Start Up Down Left Right
 */
static uint8_t shift_data = 0xff;
static void shift_init(void);

static void irq_init(void);

int main(int argc, char *argv[])
{
	spi_init();
	shift_init();
	
	nrf_init();
	_delay_ms(100);
	nrf_configure();
	irq_init();
	
	gpio_cfg_out(LED);
	gpio_cfg_inp(B_ACTION);
	gpio_cfg_inp(B_NEXT);
	
	sei();
	
	uint8_t addressRX[5] = { 'w', 'n', 'l', 'd', '0' };
	nrf_setAddressRX(addressRX);
	nrf_powerUpRX();
	_delay_ms(10);
	
	while (1)
	{
		// to do - sleep
		
		if (0 == gpio_get(B_ACTION))
		{
			shift_data = (uint8_t) ~_BV(BTN_A);
			_delay_ms(200);
			shift_data = 0xff;
		}

		if (0 == gpio_get(B_NEXT))
		{
			shift_data = (uint8_t) ~_BV(BTN_START);
			_delay_ms(200);
			shift_data = 0xff;
		}
	}
	
	return 0;
}

ISR(INT0_vect)
{
	/*
	 * load data and enable data shifting by pulling down SS
	 * pull it up first in case of previous transfer ended prematurely
	 */
	gpio_set(FORCE_SS);
	SPDR = shift_data;
	gpio_clr(FORCE_SS);
}

ISR(INT1_vect)
{
	static uint8_t status;
	static uint8_t buff[NRF_PAYLOAD_SIZE];
	
	status = nrf_getStatus();
	
	if (status & _BV(RX_DR))
	{
		nrf_getData(buff, NRF_PAYLOAD_SIZE);
		shift_data = buff[0];
	}
}

ISR(SPI_STC_vect)
{
	/* restore SS to high */
	gpio_set(FORCE_SS);
}

static void shift_init(void)
{
	gpio_cfg_inz(LATCH);
	gpio_cfg_out(FORCE_SS);
	
	/* INT0 - rising edge */
	MCUCR |= _BV(ISC01) | _BV(ISC00);
	GICR |= _BV(INT0);
	
	/* SPI - slave, mode 2, interrupt enabled, MSB first */
	gpio_cfg_out(DATA);
	SPCR |= _BV(SPE) | _BV(CPOL) | _BV(SPIE);
}

static void irq_init(void)
{
	/* INT1 - low level */
	MCUCR |= 0;
	GICR |= _BV(INT1);
}
