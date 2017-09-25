#include <inttypes.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <misc.h>
#include <gpio.h>

/* test value */
static uint8_t shift_data = 0x55;
static void shift_init(void);

int main(int argc, char *argv[])
{
	shift_init();
	sei();
	
	gpio_cfg_inp(B_ACTION);
	gpio_cfg_inp(B_NEXT);
	
	while (1)
	{
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
	MCUCR = _BV(ISC01) | _BV(ISC00);
	GICR = _BV(INT0);
	
	/* SPI - slave, mode 2, interrupt enabled, MSB first */
	gpio_cfg_out(DATA);
	SPCR = _BV(SPE) | _BV(CPOL) | _BV(SPIE);
}
