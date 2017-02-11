/*
  RFSnifferMQTT

  Usage: ./RFSnifferMQTT
*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
     
     
RCSwitch mySwitch;
 


int main(int argc, char *argv[]) {
  
     // This pin is not the first pin on the RPi GPIO header!
     // Consult https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     // for more information.
     int PIN = 29;
     
     if(wiringPiSetup() == -1) {
       printf("wiringPiSetup failed, exiting...");
       return 0;
     }

     mySwitch = RCSwitch();
     mySwitch.enableReceive(PIN);  // Receiver on interrupt 0 => that is pin #2
     
    
     while(1) {
  
      if (mySwitch.available()) {
    
        int value = mySwitch.getReceivedValue();
        
		char mqttCommand[50]; // enough to hold all numbers up to 64-bits
		sprintf(mqttCommand, "mosquitto_pub -t 433mhz/%d -m CLOSED", value);
		
	    system(mqttCommand);
        printf(mqttCommand);
    
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}

