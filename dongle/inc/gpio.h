#ifndef _H_GPIO
#define _H_GPIO

#include <avr/io.h>

#define GPIO_CFG_OUT(port, pin) \
	PORT##port |= (1 << pin); \
	DDR##port |= (1 << pin)
#define GPIO_CFG_OUT_LOW(port, pin) \
	PORT##port &= ~(1 << pin); \
	DDR##port |= (1 << pin)
#define GPIO_CFG_INZ(port, pin) \
	PORT##port &= ~(1 << pin); \
	DDR##port &= ~(1 << pin);
#define GPIO_CFG_INP(port, pin) \
	PORT##port |= (1 << pin); \
	DDR##port &= ~(1 << pin);
#define GPIO_GET(port, pin)				((PIN##port >> pin) & 0x01)
#define GPIO_TOGGLE(port, pin)			(PIN##port = (1 << pin))
#define GPIO_SET(port, pin)				(PORT##port |= (1 << pin))
#define GPIO_CLR(port, pin)				(PORT##port &= ~(1 << pin))

#define GPIO_CFG_OUT_EX(port, pin)		GPIO_CFG_OUT(port, pin)
#define GPIO_CFG_OUT_LOW_EX(port, pin)	GPIO_CFG_OUT_LOW(port, pin)
#define GPIO_CFG_INZ_EX(port, pin)		GPIO_CFG_INZ(port, pin)
#define GPIO_CFG_INP_EX(port, pin)		GPIO_CFG_INP(port, pin)
#define GPIO_GET_EX(port, pin)			GPIO_GET(port, pin)
#define GPIO_TOGGLE_EX(port, pin)		GPIO_TOGGLE(port, pin)
#define GPIO_SET_EX(port, pin)			GPIO_SET(port, pin)
#define GPIO_CLR_EX(port, pin)			GPIO_CLR(port, pin)

#define gpio_cfg_out(name)				GPIO_CFG_OUT_EX(PORT_##name, PIN_##name)
#define gpio_cfg_out_low(name)			GPIO_CFG_OUT_LOW_EX(PORT_##name, PIN_##name)
#define gpio_cfg_inz(name)				GPIO_CFG_INZ_EX(PORT_##name, PIN_##name)
#define gpio_cfg_inp(name)				GPIO_CFG_INP_EX(PORT_##name, PIN_##name)
#define gpio_get(name)					GPIO_GET_EX(PORT_##name, PIN_##name)
#define gpio_toggle(name)				GPIO_TOGGLE_EX(PORT_##name, PIN_##name)
#define gpio_set(name)					GPIO_SET_EX(PORT_##name, PIN_##name)
#define gpio_clr(name)					GPIO_CLR_EX(PORT_##name, PIN_##name)

#endif
