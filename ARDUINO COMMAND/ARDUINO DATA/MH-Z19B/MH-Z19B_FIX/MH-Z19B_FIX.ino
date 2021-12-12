#define pwmPin 5

#include <SoftwareSerial.h> // Библиотека
SoftwareSerial mySerial(13, 12); // Порты 1 - TX. 2 - RX    
int data; // Переменная для данных

#include "text.h"

void setup() { 
  Serial.begin(9600);
  MHZ_19B_Stages(1, pwmPin);
  mySerial.begin(9600); // Включить передачу с экрана
}

void loop() {
  data = mySerial.read(); 
  if(data > 0) {Serial.println(data);}
  delay(1000);
}
void yield() {
  Serial.println(MHZ_19B_Stages(2, pwmPin));
}
