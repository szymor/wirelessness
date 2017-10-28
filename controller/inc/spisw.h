#ifndef _SPISW_H
#define _SPISW_H

#include <inttypes.h>

void spi_init(void);
uint8_t spi_rw(uint8_t data);

#endif
