/*************************************************************************
	Title:    segmented - a library for seven segment displays
	Software: AVR-GCC 5.4.0
	Hardware: AVR8 MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#include "segmented.h"

/* the syntax is:
0b00000000
  hgfedcba
  76543210

common anode: 0 - segment turned on
common cathode: 1 - segment turned on
*/
#if BITMAP_TYPE == COMMON_ANODE
	#pragma message("segmented: Compiling with common anode bitmap")
	uint8_t bitmaps_7seg[] = { // common anode bitmap
			0b11000000, //0
			0b11111001, //1
			0b10100100, //2
			0b10110000, //3
			0b10011001, //4
			0b10010010, //5
			0b10000010, //6
			0b11111000, //7
			0b10000000, //8
			0b10010000, //9 
			0b11111111  //empty character
	};
#elif BITMAP_TYPE == COMMON_CATHODE
	#pragma message ("segmented: Compiling with common cathode bitmap")
	uint8_t bitmaps_7seg[] = { // common cathode bitmap
			0b00111111, //0
			0b00000110, //1
			0b01011011, //2
			0b01001111, //3
			0b01100110, //4
			0b01101101, //5
			0b01111101, //6
			0b00000111, //7
			0b01111111, //8
			0b01101111, //9
			0b00000000, //empty character
	};
#else
	#error "segmented: Invalid BITMAP_TYPE value"
#endif


void seg_number_to_bitmap(uint16_t number)
{
	volatile uint8_t i;
	volatile uint8_t temp;
	for(i = 0; i < SSD_DIGITS_COUNT; ++i)
	{
		temp = number % 10;
		seg_digits_buf[i] = bitmaps_7seg[temp];
		number /= 10;
	}
}