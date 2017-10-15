#!/usr/bin/env python
# code for python 3
import time
import serial
import io

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate = 9600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0.1
)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
print ('Chat Room Ready!')
counter = 0

while True:
    data_in=sio.readline()
    if data_in:
        print (str(data_in))
    data_out = input('Enter msg eg: CMD_VEL 10 10 \n')
    ser.write(bytes(data_out+"\n","UTF-8"))
    counter +=1
