/*
 Obstacle avoidance using Raspberry Pi as behaviour computing device
 
 The circuit:
 * RX is digital pin 6 (connect to TX of other device)
 * TX is digital pin 7 (connect to RX of other device)
 Created on October 14, 2017
 by Nino Pereira

 This example code is in the public domain.

*/

#include <BnrOneA.h>   // Bot'n Roll ONE A library
#include <EEPROM.h>    // EEPROM reading and writing
#include <SPI.h>       // SPI communication library required by BnrOne.cpp
BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A

//constants definition
#define SSPIN  2      // Slave Select (SS) pin for SPI communication

#include <SoftwareSerial.h>
SoftwareSerial mySerial(6,7); // RX, TX

char msg[50];
byte obstacles=0;
void setup() 
{ 
    //setup routines -> runs only once when program starts
    one.spiConnect(SSPIN);   // start the SPI communication module
    one.stop();              // stop motors
    one.obstacleEmitters(ON);// activate obstacles detection
    //setup routines -> runs only once when program starts
    Serial.begin(19200);     // set baud rate to 57600bps for printing values at serial monitor.
    delay(200);
    Serial.println("Serial connection OK");
    // set the data rate for the SoftwareSerial port
    mySerial.begin(19200);
    mySerial.println("Hello pi!");
}

void loop()
{
    // Sense
    obstacles=one.obstacleSensors(); 
    switch(obstacles)
    {
        case 0:   // no obstacles detected
            //one.lcd2("  No Obstacles");
            //msg = "No OBS";
            sprintf(msg, "OBS %d %d\n",0 ,0);
            mySerial.write(msg);
            mySerial.flush();
            break;
        case 1:   // obstacle detected on Left sensor
            //one.lcd2("   Left Sensor");
            mySerial.write("   Left Sensor\n");
            mySerial.flush();
            break;
        case 2:   // obstacle detected on Right sensor
            //one.lcd2("  Right Sensor");
            mySerial.write("   Right Sensor\n");
            mySerial.flush();
            break;
        case 3:   // obstacle detected on both sensors
            //one.lcd2("  Both Sensors");
            mySerial.write("   Both Sensors\n");
            mySerial.flush();
            break;
    }
    delay(250);
    // Actuate
    if (mySerial.available()) {
      String received_msg  = mySerial.readString();
      if (received_msg.startsWith("CMD_VEL",0))
      {
        int left_vel;
        int right_vel;
        sscanf (received_msg.c_str(),"%*s %d %d",&left_vel, &right_vel);        
        // sscanf to stop at a comma use  %[^,]
        sprintf(msg,"CMD_VEL= %d, %d\n", left_vel, right_vel);
        Serial.write(msg);
        Serial.flush();
        one.move(left_vel,right_vel);
      }
    }
}
