/*
	This is a configuration header for libshiftreg. Please edit #defines according to your project 
*/

#ifndef SHIFTREGCONF_H_
#define SHIFTREGCONF_H_

#include <avr/io.h>

#define SHIFTREG_PORT 				// port pins below belong to
#define SHIFTREG_PORT_DDR			// DDR register of this port
#define SHIFTREG_OE_PIN				// OE pin, INVERTED INPUT!
#define SHIFTREG_MR_PIN				// MR pin, INVERTED INPUT!
#define SHIFTREG_LATCH_PIN			// STCP, or RCLK, or latch pin
#define SHIFTREG_DS_PIN				// DS or SER pin
#define SHIFTREG_CLOCK_PIN			// SHCP or SRCLK pin, clock impulse input


#endif /* SHIFTREG_H_ */