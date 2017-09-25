#include <inttypes.h>
#include <stdbool.h>

#include <avr/io.h>
#include <avr/interrupt.h>

#include <misc.h>
#include <gpio.h>

/* IMPORTANT - needed for proper arithmetic right shift */
static int16_t shift_data = 0xffff;
static int16_t shift_temp;
static void shift_init(void);

int main(int argc, char *argv[])
{
	shift_init();
	
	gpio_cfg_inp(B_LEFT);
	gpio_cfg_inp(B_RIGHT);
	gpio_cfg_inp(B_UP);
	gpio_cfg_inp(B_DOWN);
	gpio_cfg_inp(B_SELECT);
	gpio_cfg_inp(B_START);
	gpio_cfg_inp(B_A);
	gpio_cfg_inp(B_B);
	gpio_cfg_inp(B_TURBO_A);
	gpio_cfg_inp(B_TURBO_B);
	
	gpio_cfg_inp(IRQ);
	gpio_cfg_out_low(CE);
	gpio_cfg_out(CSN);
	
	while (1)
	{
	}
	
	return 0;
}

// LATCH
ISR(INT0_vect)
{
	if (gpio_get(LATCH))
	{
		shift_temp = shift_data;
		if (shift_temp & 1)
		{
			gpio_set(DATA);
		}
		else
		{
			gpio_clr(DATA);
		}
		shift_temp >>= 1;
	}
	else
	{
		// nothing
	}
}

// CLK
ISR(INT1_vect)
{
	if (gpio_get(CLK))
	{
		if (shift_temp & 1)
		{
			gpio_set(DATA);
		}
		else
		{
			gpio_clr(DATA);
		}
		shift_temp >>= 1;
	}
	else
	{
		// nothing
	}
}

static void shift_init(void)
{
	gpio_cfg_inz(LATCH);
	gpio_cfg_out(DATA);
	gpio_cfg_inz(CLK);
}
