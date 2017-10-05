#include <avr/io.h>
#include <serial.h>

static int sendc(char c, FILE *f);
static int recvc(FILE *f);
static FILE defstream = FDEV_SETUP_STREAM(sendc, recvc, _FDEV_SETUP_RW);

void serial_init(void)
{
#define BAUD_TOL 2
#define BAUD 57600
#include <util/setbaud.h>
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	UCSRB = _BV(TXEN) | _BV(RXEN);
#if USE_2X
	UCSRA |= _BV(U2X);
#else
	UCSRA &= ~_BV(U2X);
#endif
#undef BAUD
#undef BAUD_TOL
	
	stdout = stdin = &defstream;
}

static int sendc(char c, FILE *f)
{
	// wait for empty transmit buffer
	while ( !( UCSRA & _BV(UDRE) ) );
	UDR = c;
	return 0;
}

static int recvc(FILE *f)
{
	int c;
	// wait for data to be received
	while ( !( UCSRA & _BV(RXC) ) );
	c = UDR;
	if ('\r' == c)
		c = '\n';
	return c;
}
