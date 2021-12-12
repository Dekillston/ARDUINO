#include <SoftwareSerial.h> // Библиотека

SoftwareSerial mySerial(13, 12); // Порты 1 - TX. 2 - RX     

int data; // Переменная для данных

void setup() {
  Serial.begin(9600); 
  mySerial.begin(9600); // Включить передачу с экранаЫ
}

void loop() {
  data = mySerial.read(); // Задаю значение, когда нечего не нажато то даёт 0 или -1
  if(data > 0) {Serial.println(data);}
  delay(100);
}                                                                
