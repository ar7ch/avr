/*************************************************************************
	Title:    Some code to output data passed via UART to 4x7seg display 
	Software: AVR-GCC 5.4.0
	Hardware: AVR8 MCUs
	License:  GNU Lesser General Public License v3
*************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "segmented.h"
#include "shiftreg.h"

#define DIGIT_PORT PORTB
#define DIGIT_DDR DDRB
#define D1_PIN 2
#define D2_PIN 3
#define D3_PIN 4
#define D4_PIN 5

// UART config: 9600/8-N-1
#define BAUD_RATE 9600L
#define UBRR_VALUE ((F_CPU / (16 * BAUD_RATE)) - 1)
#define UART_BUFFER_LEN SSD_DIGITS_COUNT // received bytes array will have a length equal to number of 7seg display digits

typedef enum
{
	ASCII_NUL = 0x00,
	ASCII_STX = 0x02,
	ASCII_ETX = 0x03,
	ASCII_ACK = 0x06,
	ASCII_BS = 0x08
}ascii_control_chars;

typedef enum
{
	CLEAR_DISPLAY = ASCII_BS,
	DIRECT_MODE_START = ASCII_STX,
	DIRECT_MODE_STOP = ASCII_ETX
}custom_control_chars;

typedef struct  
{
	uint8_t direct_mode:1;
	uint8_t reserved2:1;
	uint8_t reserved3:1;
	uint8_t reserved4:1;
	uint8_t reserved5:1;
	uint8_t reserved6:1;
	uint8_t reserved7:1;
	uint8_t reserved8:1;
}flag_register;

flag_register flag_reg = {.direct_mode = 0};
/*
normal (driver) mode: pass a character via UART, this character will be converted into corresponding bitmap
direct mode: bytes passed via UART will be written directly in SSD without any modifications

normal mode is used by default; to use direct mode, send DIRECT_MODE_START byte; every further byte will be treated as a bitmap until DIRECT_MODE_STOP received 
*/

static volatile uint16_t counter = 0;

// every digit of number to be displayed on SSD will be sent in dedicated bit (using ASCII encoding)
// it's redundant, but needed to be able to use control characters

// bytes sent by UART are stored in 4-byte-sized buffer
// once the buffer is full, its contents will be displayed on display 
static volatile char uart_recv_bytes[UART_BUFFER_LEN];
static volatile uint8_t uart_bytes_count = 0;
static volatile char uart_buffer;

void uart_init()
{
	UBRRL = UBRR_VALUE; UBRRH = (UBRR_VALUE >> 8);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);
	UCSRB = (1 << RXEN) | (1 << RXCIE);
}

ISR(USART_RXC_vect)
{
	uart_buffer = UDR;
	switch(uart_buffer)
	{
		case CLEAR_DISPLAY:
			counter = 0;
			uart_bytes_count = 4;
			for(volatile uint8_t i = 0; i < UART_BUFFER_LEN; i++) {uart_recv_bytes[i] = '0';}
			break;
		case ASCII_STX:
			flag_reg.direct_mode = 1;
			uart_bytes_count = 0;
		break;
		case ASCII_ETX:
			flag_reg.direct_mode = 0;
		break;
		default:
			if(uart_bytes_count < 4)
			{
				uart_recv_bytes[uart_bytes_count++] = uart_buffer;
			}
		break;
	}	
}
void ascii_arr_to_bitmap()
{
	volatile uint8_t i;
	for(i = 0; i < uart_bytes_count; ++i)
	{
		if(!flag_reg.direct_mode)
		{
			if( (uart_recv_bytes[i] <= '9') && (uart_recv_bytes[i] >= '0') ) // check if the character is an ASCII digit
			{
				// seg_digits_buf[0] stores the lowest number position and uart_recv_bytes[0] is the highest number position
				// this (here and further) makes an assignment to equal number positions
				seg_digits_buf[(SSD_DIGITS_COUNT - 1) - i] = bitmaps_7seg[(uart_recv_bytes[i] - '0')];
			}	
			else if (uart_recv_bytes[i] == ' ')
			{
				seg_digits_buf[(SSD_DIGITS_COUNT - 1) - i] = bitmaps_7seg[SEG_EMPTY]; // empty bitmap to avoid leading zeros
			}
		}
		else
		{
			seg_digits_buf[(SSD_DIGITS_COUNT - 1) - i] = (BITMAP_TYPE == COMMON_CATHODE ? uart_recv_bytes[i] : ~(uart_recv_bytes[i]));
		}
	}
}
uint16_t ascii_arr_to_number()
{
	volatile uint8_t i;
	volatile uint16_t num = 0;
	for(i = 0; i < uart_bytes_count; ++i)
	{
		num += (uart_recv_bytes[i] - '0');
		if(i != uart_bytes_count - 1) num *= 10;
	}
	return num;
}
//ISR(USART_TXC_vect)

inline void seg_multiplex_output()
{
	uint8_t i;
	for(i = 0; i < SSD_DIGITS_COUNT; ++i)
	{
		shiftreg_output_byte(seg_digits_buf[i]);
		shiftreg_toggle_latch();
		DIGIT_PORT |= (1 << (D1_PIN + i));
		_delay_ms(5);
		DIGIT_PORT &= ~(1 << (D1_PIN + i));
	}
}


int main(void)
{
	cli();
	uart_init();
	shiftreg_init();
	DIGIT_DDR = (1 << D1_PIN) | (1 << D2_PIN) | (1 << D3_PIN) | (1 << D4_PIN);
	DIGIT_PORT = 0x00;
	seg_number_to_bitmap(counter);
	sei();
    while(1) 
    {
		cli();
		if(uart_bytes_count == 4)
		{
			//counter = ascii_arr_to_number();
			ascii_arr_to_bitmap();
			uart_bytes_count = 0;
		} 
		//seg_number_to_bitmap(counter);
		//set_dot(seg_digits_buf[2]);
		sei();
		seg_multiplex_output();
    }
}

