#include "AiThinkerAx.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
AiThinkerAx    moduleA7(mySerial);

void setup() {
  Serial.begin(9600);
  
  Serial.print("Init module... ");
	if(moduleA7.begin(9600)){
    Serial.println("OK");
	}else{
    Serial.println("FAIL");
	}

  Serial.print("Send SMS... ");
  if(moduleA7.sendSMS("+3xxxxxxxxxxx", "text message")){
    Serial.println("OK");
  }else{
    Serial.println("FAIL");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}