#!/usr/bin/env python
# code for python 2
import time
import serial

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0.1
)
print ('Chat Room Ready!')
counter = 0

while True:

    data_in=ser.readline()

    if data_in:
        print (str(data_in))
    data_out = raw_input('Enter msg: ')
    ser.write(data_out+'\n')
    counter +=1
