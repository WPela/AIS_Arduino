//AIS - Initial version

#include "RTClib.h"
#include <Wire.h>

RTC_DS3231 RTC;

int relayPin = 8;    // Relay Pin
int sensor_pin = A0; // Soil Sensor input at Analog PIN A0
int output_value ;

void setup()        
{ 
  Serial.begin(9600);                 
  Wire.begin();
  RTC.begin();
  pinMode(relayPin, OUTPUT);
  pinMode(sensor_pin, INPUT);
  Serial.println("Reading From the Sensor ...");
  delay(2000);
}

void loop()
{
 DateTime now = RTC.now();  //RTC will be used to set night break

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

 output_value= analogRead(sensor_pin);
 output_value = map(output_value,550,10,0,100);
 Serial.print("Mositure : ");
 Serial.print(output_value);
 Serial.println("%");    //Read and print of the soil moisture level in Serial monitor

 if(output_value>45){                //condition set to turn on water pump when sensor output is lower then 45%  
  digitalWrite(relayPin, LOW);
 }
 else
 {
  digitalWrite(relayPin, HIGH);      //when the condition met, pump will work 2 sec and wait 30 sec then the condition is checked once again.
  Serial.print("Powering water pump");
  delay(2000);
  digitalWrite(relayPin, LOW);
  delay(30000);         
 }
 delay(1000);
}
