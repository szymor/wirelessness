#include <stdbool.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <timer.h>

#define NULL ((void*)0)

#define OVERFLOW_VALUE	65536
// in microseconds
#define MIN_TICK	1000
#define MAX_TICK	10000
#define REAL_TICK(x)	(OVERFLOW_VALUE * 1000 * x / (F_CPU / 1000))
#define CHECK_CONDITION(x)	(REAL_TICK(x) > MIN_TICK && REAL_TICK(x) < MAX_TICK)

volatile bool auto_state = false;

static uint32_t tick, time_elapsed = 0;

ISR(TIMER1_OVF_vect)
{
	time_elapsed += tick;
	if (time_elapsed > 100000)
	{
		auto_state = !auto_state;
		time_elapsed = 0;
	}
}

void timer_init(void)
{
#if CHECK_CONDITION(1024)
#define SYSCLK_PRESCALER 5
	tick = (uint32_t)(REAL_TICK(1024));
#elif CHECK_CONDITION(256)
#define SYSCLK_PRESCALER 4
	tick = (uint32_t)(REAL_TICK(256));
#elif CHECK_CONDITION(64)
#define SYSCLK_PRESCALER 3
	tick = (uint32_t)(REAL_TICK(64));
#elif CHECK_CONDITION(8)
#define SYSCLK_PRESCALER 2
	tick = (uint32_t)(REAL_TICK(8));
#elif CHECK_CONDITION(1)
#define SYSCLK_PRESCALER 1
	tick = (uint32_t)(REAL_TICK(1));
#else
#error Cannot compute valid Clock Select prescaler bits!
#endif
	// normal port operation, normal timer operation
	TCCR1A = 0;
	TCCR1B = SYSCLK_PRESCALER;
	TIMSK = _BV(TOIE1);
}
