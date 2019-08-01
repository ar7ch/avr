/*************************************************************************
	Title:    shiftreg - a library for 74hc595 shift register
	Software: AVR-GCC 5.4.0
	Hardware: AVR MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#include "shiftreg.h"

void shiftreg_init()
{
	SHIFTREG_PORT_DDR |= (1 << SHIFTREG_MR_PIN) | (1 << SHIFTREG_CLOCK_PIN) | (1 << SHIFTREG_DS_PIN) | (1 << SHIFTREG_OE_PIN) | (1 << SHIFTREG_LATCH_PIN); //set port to output
	SHIFTREG_PORT &= ~( (1 << SHIFTREG_MR_PIN) | (1 << SHIFTREG_CLOCK_PIN) | (1 << SHIFTREG_DS_PIN) | (1 << SHIFTREG_OE_PIN) | (1 << SHIFTREG_LATCH_PIN) ); //clear bits in use
	SHIFTREG_PORT |= (1 << SHIFTREG_MR_PIN); // MR input is inverted, set to 1 to deactivate
}

void shiftreg_clock_impulse()
{
	asm volatile("nop");
	SHIFTREG_PORT |= (1 << SHIFTREG_CLOCK_PIN);
	asm volatile("nop");
	SHIFTREG_PORT &= ~(1 << SHIFTREG_CLOCK_PIN);
}

void shiftreg_toggle_latch() // off-on-off to pass values from shift register to output register 
{
	asm volatile("nop");
	SHIFTREG_PORT |= (1 << SHIFTREG_LATCH_PIN);
	asm volatile("nop");
	SHIFTREG_PORT &= ~(1 << SHIFTREG_LATCH_PIN);    
}

void shiftreg_output_byte(uint8_t out_byte){
    for(uint8_t i = 0; i < 8; ++i)
	{
		if(out_byte & (1 << 7))
		{
			SHIFTREG_PORT |= (1 << SHIFTREG_DS_PIN);
		}
		else
		{
			SHIFTREG_PORT &= ~(1 << SHIFTREG_DS_PIN);
		}
		shiftreg_clock_impulse();
		out_byte <<= 1;
	}
}