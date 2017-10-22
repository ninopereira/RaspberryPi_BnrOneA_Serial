#!/usr/bin/env python
# code for python 3
import time
import serial
import io

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate = 57600,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0.01
)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
print ('Serial Connection Ready!')

count = 0
while True:
    data_in=sio.readline()
    if data_in:
        print (str(data_in))
        data_out = "CMD_VEL " + str(-count)  + " " + str(count) + "\n"
        sio.write(data_out)
        sio.flush()
        count += 10
        count = count % 100
