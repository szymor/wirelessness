#ifndef _H_MISC
#define _H_MISC

/** A compile time assertion check.
 *
 *  Validate at compile time that the predicate is true without
 *  generating code. This can be used at any point in a source file
 *  where typedef is legal.
 *
 *  On success, compilation proceeds normally.
 *
 *  On failure, attempts to typedef an array type of negative size. The
 *  offending line will look like
 *      typedef assertion_failed_file_h_42[-1]
 *  where file is the content of the second parameter which should
 *  typically be related in some obvious way to the containing file
 *  name, 42 is the line number in the file on which the assertion
 *  appears, and -1 is the result of a calculation based on the
 *  predicate failing.
 *
 *  \param predicate The predicate to test. It must evaluate to
 *  something that can be coerced to a normal C boolean.
 *
 *  \param file A sequence of legal identifier characters that should
 *  uniquely identify the source file in which this condition appears.
 */

#define CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)

#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) \
    typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];

#define BTN_A		7
#define BTN_B		6
#define BTN_SELECT	5
#define BTN_START	4
#define BTN_UP		3
#define BTN_DOWN	2
#define BTN_LEFT	1
#define BTN_RIGHT	0

#define PORT_LED			D
#define PIN_LED				0

/* Button pins */
#define PORT_B_ACTION		D
#define PIN_B_ACTION		6
#define PORT_B_NEXT			D
#define PIN_B_NEXT			7

/* Shift output pins
 * LATCH - INT0
 */
#define PORT_LATCH			D
#define PIN_LATCH			2
#define PORT_DATA			B
#define PIN_DATA			4
/*
#define PORT_CLK			B
#define PIN_CLK				5
*/
#define PORT_FORCE_SS		B
#define PIN_FORCE_SS		1

/* NRF24L01 pins
 * IRQ - INT1
 */
#define PORT_IRQ			D
#define PIN_IRQ				3
#define PORT_CE				C
#define PIN_CE				5
#define PORT_CSN			C
#define PIN_CSN				4
#define PORT_MOSI			C
#define PIN_MOSI			1
#define PORT_MISO			C
#define PIN_MISO			0
#define PORT_SCK			C
#define PIN_SCK				2

#endif
