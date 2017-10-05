#include <inttypes.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <misc.h>
#include <gpio.h>

/*
 * shift order:
 * A B Select Start Up Down Left Right
 */
static uint8_t shift_data = 0xff;
static void shift_init(void);

int main(int argc, char *argv[])
{
	shift_init();
	sei();
	
	gpio_cfg_inp(B_ACTION);
	gpio_cfg_inp(B_NEXT);
	
	uint8_t shift_bit = 7;
	while (1)
	{
		if (0 == gpio_get(B_ACTION))
		{
			shift_data = ~_BV(shift_bit);
			_delay_ms(200);
		}
		else
		{
			shift_data = 0xff;
		}
		
		if (0 == gpio_get(B_NEXT))
		{
			shift_bit = shift_bit != 0 ? shift_bit - 1 : 7;
			_delay_ms(200);
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
