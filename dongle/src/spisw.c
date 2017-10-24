#include <spisw.h>
#include <misc.h>
#include <gpio.h>

uint8_t spi_rw(uint8_t data)
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
		
		//_delay_ms(1);
		gpio_set(SCK);
		//_delay_ms(1);
		
		data_out <<= 1;
		data_out |= gpio_get(MISO);
		
		gpio_clr(SCK);
		//_delay_ms(1);
	}
	
	return data_out;
}

void spi_init(void)
{
	gpio_cfg_out(MOSI);
	gpio_cfg_inz(MISO);
	gpio_cfg_out_low(SCK);
}
