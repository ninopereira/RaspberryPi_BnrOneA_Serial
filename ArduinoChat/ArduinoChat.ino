/*
 Software serial interface with other devices (e.g.Raspberry Pi)

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 8 (connect to TX of other device)
 * TX is digital pin 9 (connect to RX of other device)
 Created on October 14, 2017
 by Nino Pereira
 based on Tom Igoe and Mikal Hart's examples

 This example code is in the public domain.

 */
#include <SoftwareSerial.h>

SoftwareSerial mySerial(8,9); // RX, TX

void setup() 
{
  //setup routines -> runs only once when program starts
  Serial.begin(9600);     // set baud rate to 57600bps for printing values at serial monitor.
  delay(200);
  Serial.println("PC Serial OK");
  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  mySerial.println("Hello, world!");
}


void loop() { // run over and over
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
  if (mySerial.available()) {
    String received_msg  = mySerial.readString();
    Serial.println(received_msg);
    if (received_msg.startsWith("CMD_VEL",0))
    {
      int left_vel;
      int right_vel;
      float left_veloc;
      float right_veloc;
      sscanf (received_msg.c_str(),"%*s %d %d",&left_vel, &right_vel);
      // sscanf to stop at a comma use  %[^,]
      //left_veloc = atof(left_vel.c_str());
      //right_veloc = atof(right_vel.c_str());
      Serial.println("This command sends velocity commands to the wheels");
      Serial.println(left_vel);
      Serial.println(right_vel);
      //Serial.println("%f,%f",left_vel,right_vel);
    }
  }
}
