// Библиотеки
  // Экран
    #include <SoftwareSerial.h>
  // Датчик температуры и влажности
    #include "DHT.h"
// Порты
  // Экран
    #define ScreenTXpin 13
    #define ScreenRXpin 12
  // Датчик температуры и влажности
    #define DHTPIN A0
    #define DHTTYPE DHT22
  // Датчик уровня
    #define PinBotton A1
  // Реле
    #define RELEpin 11
// Настройка
  // Экран
    SoftwareSerial mySerial(13, 12);
    int data;
  // Датчик температуры и влажности
    DHT dht(DHTPIN, DHTTYPE);
void setup() {
  Serial.begin(9600); 
  // Запуск
    // Экран
      mySerial.begin(9600);
    // Датчик температуры и влажности
      dht.begin();
    // Датчик уровня
      pinMode(PinBotton, INPUT_PULLUP);
    // Реле
      pinMode(RELEpin, OUTPUT);
      digitalWrite(RELEpin, HIGH);  
}

void loop() {
  // Вывод
    // Датчик температуры и влажности
      mySerial.print((String)"n0.val="+((int)dht.readTemperature())+char(255)+char(255)+char(255));
      mySerial.print((String)"n1.val="+((int)dht.readHumidity())+char(255)+char(255)+char(255));
   // Датчк уровня
    int levelSensor = digitalRead(PinBotton);
    if(levelSensor == 1) {
      mySerial.print((String)"t4.txt=""\"Get down\""+char(255)+char(255)+char(255));
      mySerial.print((String)"t4.bco=20093"+char(255)+char(255)+char(255));
    } else if(levelSensor == 0) {
      mySerial.print((String)"t4.txt=""\"Rise up\""+char(255)+char(255)+char(255)); 
      mySerial.print((String)"t4.bco=63748"+char(255)+char(255)+char(255));
    }
  delay(1000);
}
void yield() {
  data = mySerial.read();
  if(data > 0) {
    Serial.println(data);
    if(data == 1) {
      digitalWrite(RELEpin, LOW);
    } else if(data == 2) {
      digitalWrite(RELEpin, HIGH); 
    }
 }
}
