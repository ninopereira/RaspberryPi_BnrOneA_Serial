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
    //setup routines -> runs only once when program starts
    Serial.begin(57600);     // set baud rate to 57600bps for printing values at serial monitor.
    Serial.setTimeout(5);
    delay(200);
    Serial.println("Serial connection OK");
    // set the data rate for the SoftwareSerial port
}

void loop()
{
    // Actuate
    if (Serial.available()) {
      String received_msg  = Serial.readString();
      if (received_msg.startsWith("CMD_VEL",0))
      {
        int left_vel;
        int right_vel;
        sscanf (received_msg.c_str(),"%*s %d %d\n",&left_vel, &right_vel);        
        // sscanf to stop at a comma use  %[^,]
        sprintf(msg,"CMD_VEL= %d, %d\n", left_vel, right_vel);
        //Serial.write(msg);
        //Serial.flush();
        one.move(left_vel,right_vel);
      }
      if (received_msg.startsWith("GET_OBS",0))
      {
        // Sense
        obstacles=one.obstacleSensors(); 
        switch(obstacles)
        {
            case 0:   // no obstacles detected
                //one.lcd2("  No Obstacles");
                //msg = "No OBS";
                sprintf(msg, "OBS %d %d\n",0 ,0);
                Serial.write(msg);
                Serial.flush();
                break;
            case 1:   // obstacle detected on Left sensor
                //one.lcd2("   Left Sensor");
                Serial.write("   Left Sensor\n");
                Serial.flush();
                break;
            case 2:   // obstacle detected on Right sensor
                //one.lcd2("  Right Sensor");
                Serial.write("   Right Sensor\n");
                Serial.flush();
                break;
            case 3:   // obstacle detected on both sensors
                //one.lcd2("  Both Sensors");
                Serial.write("   Both Sensors\n");
                Serial.flush();
                break;
        }
      }
    }
}
