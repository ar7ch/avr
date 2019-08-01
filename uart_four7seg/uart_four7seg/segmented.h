/*************************************************************************
	Title:    segmented - a library for seven segment displays
	Software: AVR-GCC 5.4.0
	Hardware: AVR8 MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#ifndef SEGMENTED_H_
#define SEGMENTED_H_

#include <avr/io.h>

#define COMMON_ANODE 1
#define COMMON_CATHODE 2

/* =========================== PROJECT-SPECIFIC PORTS AND PINS DEFINITIONS ========================== */ 

#define SSD_DIGITS_COUNT 4			// number of digits in your Seven Segment Display (SSD)
#define BITMAP_TYPE COMMON_ANODE	// whether common anode or cathode

/* ================================================================================================== */ 


uint8_t seg_digits_buf[SSD_DIGITS_COUNT]; // a buffer with bitmap for every digit; seg_digits_buf[0] is D1 and so on
extern uint8_t bitmaps_7seg[];
typedef enum
{
	SEG_EMPTY = 10

}bitmaps_symbols_index;

// set or remove dot segment on required digit
#define set_dot(val) ( (BITMAP_TYPE == COMMON_CATHODE) ? (val |= (1 << 7)) : (val &= ~(1 << 7)) ) 
#define clear_dot(val) ( (BITMAP_TYPE == COMMON_ANODE) ? (val &= ~(1 << 7)) : (val |= (1 << 7)) )

void seg_number_to_bitmap(uint16_t number);

#endif /* SEGMENTED_H_ */