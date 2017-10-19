#!/usr/bin/env python
# code for python 3
import time
import serial
import io

ser = serial.Serial(
    port='/dev/ttyS0',
    baudrate = 19200,
    parity=serial.PARITY_NONE,
    stopbits=serial.STOPBITS_ONE,
    bytesize=serial.EIGHTBITS,
    timeout=0.1
)
sio = io.TextIOWrapper(io.BufferedRWPair(ser, ser))
print ('Serial Connection Ready!')

count = 0
while True:
    data_in=sio.readline()
    if data_in:
        print (str(data_in))
        #data_out = input('Enter msg eg: CMD_VEL 10 10 \n')
        data_out = "CMD_VEL 10 " + str(count) + "\n"
        
        time.sleep(0.10)
        sio.write(data_out)
        #ser.write(bytes(data_out+"\n","UTF-8"))
        sio.flush()
        
        count += 1
