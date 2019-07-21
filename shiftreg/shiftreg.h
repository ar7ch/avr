/*************************************************************************
	Title:    shiftreg - a library for 74hc595 shift register
	Software: AVR-GCC 5.4.0
	Hardware: AVR MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#ifndef SHIFTREG_H_
#define SHIFTREG_H_

#include <avr/io.h>
#include <inttypes.h>
#include "shiftregconf.h"

#ifndef SHIFTREG_PORT 
#error "shiftreg: Please specify SHIFTREG_PORT in shiftregconf.h" 
#endif
#ifndef SHIFTREG_PORT_DDR 
#error "shiftreg: Please specify SHIFTREG_PORT_DDR in shiftregconf.h" 
#endif
#ifndef SHIFTREG_OE_PIN 
#error "shiftreg: Please specify SHIFTREG_OE_PIN in shiftregconf.h" 
#endif
#ifndef SHIFTREG_MR_PIN 
#error "shiftreg: Please specify SHIFTREG_MR_PIN in shiftregconf.h" 
#endif
#ifndef SHIFTREG_LATCH_PIN 
#error "shiftreg: Please specify SHIFTREG_LATCH_PIN in shiftregconf.h"
#endif
#ifndef SHIFTREG_DS_PIN 
#error "shiftreg: Please specify SHIFTREG_DS_PIN in shiftregconf.h" 
#endif	
#ifndef SHIFTREG_CLOCK_PIN 
#error "shiftreg: Please specify SHIFTREG_CLOCK_PIN in shiftregconf.h"
#endif

void shiftreg_init();
void clock_impulse();
void toggle_latch();
void output_byte(uint8_t out_byte);

#endif /* SHIFTREG_H_ */