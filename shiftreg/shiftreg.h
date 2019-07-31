/*************************************************************************
	Title:    shiftreg - a library for 74hc595 shift register
	Software: AVR-GCC 5.4.0
	Hardware: AVR8 MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#ifndef SHIFTREG_H_
#define SHIFTREG_H_

#include <avr/io.h>

/* =========================== PROJECT-SPECIFIC PORTS AND PINS DEFINITIONS ========================== */

#define SHIFTREG_PORT PORTC				// port pins below belong to
#define SHIFTREG_PORT_DDR DDRC			// DDR register of this port
#define SHIFTREG_OE_PIN 0				// OE pin, INVERTED INPUT!
#define SHIFTREG_MR_PIN	1				// MR pin, INVERTED INPUT!
#define SHIFTREG_LATCH_PIN 2			// STCP, or RCLK, or latch pin
#define SHIFTREG_DS_PIN	3				// DS or SER pin
#define SHIFTREG_CLOCK_PIN 4			// SHCP or SRCLK pin, clock impulse input

/* ================================================================================================== */

void shiftreg_init();
void shiftreg_clock_impulse();
void shiftreg_toggle_latch();
void shiftreg_output_byte(uint8_t out_byte);

#endif /* SHIFTREG_H_ */