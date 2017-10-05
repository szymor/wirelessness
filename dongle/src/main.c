#include <inttypes.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <misc.h>
#include <gpio.h>

static uint8_t spi_rw(uint8_t data);
#include <NRF24L01.h>
#include "NRF24L01.c"
static void spi_init(void);

#define FRAME_SIZE	2

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
	
	uint8_t addressTX[5] = { 'c', 't', 'l', 'r', '1' };
	uint8_t addressRX[5] = { 'd', 'n', 'g', 'l', '1' };
	nrf_setAddressRX(addressRX);
	nrf_setAddressTX(addressTX);
	_delay_ms(10);
	
	while (1)
	{
		// to do - sleep
		
		if (0 == gpio_get(B_ACTION))
		{
			// button A
			shift_data = 0b01111111;
			_delay_ms(200);
			shift_data = 0xff;
		}

		if (0 == gpio_get(B_NEXT))
		{
			// start
			shift_data = 0b11101111;
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
	static uint8_t buff[FRAME_SIZE];
	status = nrf_getStatus();
	
	if (status & _BV(RX_DR))
	{
		nrf_getData(buff, FRAME_SIZE);
		shift_data = buff[0];
		gpio_toggle(LED);
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

static uint8_t spi_rw(uint8_t data)
{
	uint8_t data_out = 0xff;
	
	for (uint8_t i = 0; i < 8; ++i)
	{
		if (data & 0x80)
		{
			gpio_set(MOSI);
		}
		else
		{
			gpio_clr(MOSI);
		}
		data <<= 1;
		
		_delay_ms(1);
		gpio_set(SCK);
		_delay_ms(1);
		
		data_out <<= 1;
		data_out |= gpio_get(MISO);
		
		gpio_clr(SCK);
		_delay_ms(1);
	}
	
	return data_out;
}

static void spi_init(void)
{
	gpio_cfg_out(MOSI);
	gpio_cfg_inp(MISO);
	gpio_cfg_out_low(SCK);
}

static void irq_init(void)
{
	/* INT1 - falling edge */
	MCUCR |= _BV(ISC11);
	GICR |= _BV(INT1);
}
