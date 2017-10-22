/*
 Obstacle avoidance using Raspberry Pi as behaviour computing device
 
 The circuit:
 * RX is digital pin 0 (connect to TX of other device)
 * TX is digital pin 1 (connect to RX of other device)
 Created on October 14, 2017
 by Nino Pereira

 This example code is in the public domain.

*/

#include <BnrOneA.h>   // Bot'n Roll ONE A library
#include <EEPROM.h>    // EEPROM reading and writing
#include <SPI.h>       // SPI communication library required by BnrOne.cpp
BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A
#include <SoftwareSerial.h>
SoftwareSerial mySerial(6, 7); // RX, TX
//constants definition
#define SSPIN  2      // Slave Select (SS) pin for SPI communication

int velocity = 0;

char msg[50];
byte obstacles=0;
void setup() 
{ 
    //setup routines -> runs only once when program starts
    one.spiConnect(SSPIN);   // start the SPI communication module
    one.stop();              // stop motors
    one.obstacleEmitters(ON);// activate obstacles detection
    mySerial.begin(19200);
    mySerial.setTimeout(5);
    delay(100);
}

void loop()
{
    // Actuate
    if (mySerial.available()) {
      String received_msg  = mySerial.readString();
      if (received_msg.startsWith("CMD_VEL",0))
      {
        int left_vel;
        int right_vel;
        sscanf (received_msg.c_str(),"%*s %d %d\n",&left_vel, &right_vel);        
        sprintf(msg,"CMD_VEL= %d, %d\n", left_vel, right_vel);
        one.move(left_vel,right_vel);
      }
      if (received_msg.startsWith("GET_OBS",0))
      {
        // Sense
        obstacles=one.obstacleSensors(); 
        switch(obstacles)
        {
            case 0:   // no obstacles detected
                sprintf(msg, "OBS %d %d\n",0 ,0);
                mySerial.write(msg);
                mySerial.flush();
                break;
            case 1:   // obstacle detected on Left sensor
                mySerial.write("   Left Sensor\n");
                mySerial.flush();
                break;
            case 2:   // obstacle detected on Right sensor
                mySerial.write("   Right Sensor\n");
                mySerial.flush();
                break;
            case 3:   // obstacle detected on both sensors
                mySerial.write("   Both Sensors\n");
                mySerial.flush();
                break;
        }
      }
    }
}
