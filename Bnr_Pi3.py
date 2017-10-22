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
    timeout=0.005
)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
print ('Serial Connection Ready!')
time.sleep(0.2)
count = 0
data_in = []
state = 0 
while True:
    data_out = "GET_OBS \n"
    sio.write(data_out)
    sio.flush()
    data_in = []
    while (not data_in):
        data_in=sio.readline()

    if (state == 0):
        count = count + 10
    else:
        count = count - 10

    if state == 0 and count > 100:
        state = 1
        count = 100
    if state == 1 and count < 0:
        state = 0
        count = 0
    print (str(data_in))
    
    data_out = "CMD_VEL " + str(-count)  + " " + str(count) + "\n"
    sio.write(data_out)
    sio.flush()
    time.sleep(0.05)
