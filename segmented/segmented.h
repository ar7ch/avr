/*************************************************************************
	Title:    segmented - a library for seven segment displays
	Software: AVR-GCC 5.4.0
	Hardware: AVR MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#ifndef SEGMENTED_H_
#define SEGMENTED_H_
#include <avr/io.h>
#include <inttypes.h>
#include "segconf.h"

#define set_dot(val) ( (BITMAP_TYPE == COMMON_CATHODE) ? (val |= (1 << 7)) : (val &= ~(1 << 7)) )
#define clear_dot(val) ( (BITMAP_TYPE == COMMON_ANODE) ? (val &= ~(1 << 7)) : (val |= (1 << 7)) )

#ifndef SSD_DIGITS_COUNT
	#error "segmented: Please define SSD_DIGITS_COUNT"
#else
	uint8_t digits[SSD_DIGITS_COUNT]; 
#endif



/* the syntax is:
0b00000000
  hgfedcba
  76543210

common anode: 0 - segment turned on
common cathode: 1 - segment turned on
*/

extern uint8_t bitmaps_7seg[];

void number_to_bitmap(uint16_t number);
#endif /* SEGMENTED_H_ */