#include <Arduino.h>
#include "MHZ19_uart.h"
 
MHZ19_uart mhz19;
 
void setup()
{
  int status;
 
  Serial.begin(9600);
 
  mhz19.begin(5, 4);
  mhz19.setAutoCalibration(false);
  
  status = mhz19.getStatus();
  Serial.println(status);
  delay(2000);
  
  status = mhz19.getStatus();
  Serial.println(status);
  delay(2000);
}
 
void loop()
{
  Serial.println(mhz19.getPPM());
  delay(1000);
}
