#*************************************************************************
#	Title:    A small script to send current date via UART
#	Software: Python3
#	Hardware: A serial port or USB-TTL converter
#	License:  GNU Lesser General Public License v3
#*************************************************************************

# Infinite loop will eat up some resources,
# so the most appropriate way is making this script one-shot
# and launching it every minute at 00 seconds with systemd timer or cron

import serial
import time

uart = serial.Serial('COM3')
while True:
    hours = time.localtime().tm_hour
    # output time in full format, for example 08:04 instead of 8:4
    if hours < 10:
        hours = '0' + str(hours)
    mins = time.localtime().tm_min
    if mins < 10:
        mins = '0' + str(mins)
    time_data = str(hours) + str(mins)
    for uart_char in time_data:
        uart.write(uart_char.encode())
    print(time_data, end='\n')
uart.close()

