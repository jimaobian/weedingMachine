#include <PlainProtocol.h>

#include "DFMobile.h"
DFMobile Robot (7,6,4,5);

PlainProtocol mytest(Serial);

int motorSpeed;
int motorDestination[2];

String displayString="";
int displayPosition[2];


void setup() {
    Robot.Direction (HIGH,LOW);// (left direction,right direction); 

  mytest.begin(115200);
  for(int i=4;i<=7;i++){
     pinMode(i, OUTPUT);  
  }

}
/*
This is the receiving demo code for plainprotocol.

You can send the following frame in Serial monitor to test whether the PlainProtocol can phrase the frame correctly:

<speed>100;
<destination>23,56;
<displayHello World!>10,35;

*/



void loop() {

  if (mytest.available()) {
    if (mytest.equals("destination")) {    //send "<destination>100;" in Serial monitor
      //the "speed" process
      motorSpeed=mytest.read();
      
      Serial.print("destination:");
      Serial.println(motorSpeed);
    }
    else if (mytest.equals("speed")){   //send "<speed>23,56;" in Serial monitor
      //the "destination" process
      motorDestination[0]=mytest.read();
      motorDestination[1]=mytest.read();

      Serial.println("speed:");
      Serial.print(" X:");
      Serial.print(motorDestination[0]);
      Serial.print(" Y:");
      Serial.println(motorDestination[1]);

      
      Robot.Speed (motorDestination[0],motorDestination[1]);

      
    }
    else if (mytest.equals("display")){    //send "<displayHello World!>10,35;" in Serial monitor
      //the "destination" process
      displayString=mytest.readString();
      displayPosition[0]=mytest.read();
      displayPosition[1]=mytest.read();

      Serial.println("display:");
      Serial.print("displayString:");
      Serial.println(displayString);
      Serial.print(" X:");
      Serial.print(displayPosition[0]);
      Serial.print(" Y:");
      Serial.println(displayPosition[1]);
    }
    else{
      //no matching command
    }
  }
}
