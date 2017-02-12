/*
  RFSnifferMQTT

  Usage: ./RFSnifferMQTT
*/

#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <sstream>
     
     
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
        
	    std::ostringstream oss;
		oss << "mosquitto_pub -t 433mhz/" << value << " -m CLOSED";
		std::string mqttCommand = oss.str();
	    
	    system(mqttCommand.c_str());
        printf("Received value: %i\n", value);
    
        mySwitch.resetAvailable();
    
      }
      
  
  }

  exit(0);


}

