# RaspberryPi_BnrOneA_Serial

## Serial interface with Raspberry Pi and Bot'n Roll One A

Instructions:

Raspberry Pi files:
- For Python 3:
python3 Bnr_Pi3.py

Arduino files:
ObstacleAvoidance

## Why not use SPI?

Bot'n Roll ONE A has an ATMEGA 328 which acts as a master device using SPI communication with PIC18F45.
Hence SPI bus as well as the I2C communication cannot be used as a slave.
Connecting the Raspberry Pi as a slave device to an ATMEGA328 is not an easy task as there are no officially supported drivers for Raspberry Pi (Raspbian OS) to act as a server using SPI or I2C protocols.

## Software Serial library

The main Serial communication port is used in Bot'n Roll ONE to program the robot using a serial cable.
Using the same port to establish a communication interface with the Raspberry Pi can be used but we would have to disconnect the cables everytime we wish to program the ATMEGA using the Arduino interface.
A more practical way is to connect the Arduino directly to the Raspberry Pi using a Software Serial port which can be done using the officially supported Software Serial library from Arduino website. In this way we can define any other pair of pins to act as RX/TX and keep using the default ones to program the Arduino.
Also, as Raspberry Pi can run the Arduino IDE, it can also be used to program the Bot'n Roll ONE directly.
On top of this if you establish a remote desktop connection from your laptop to the Raspberry Pi then you'd be able to program your Raspberry Pi and Bot'n Roll wirelessly!

