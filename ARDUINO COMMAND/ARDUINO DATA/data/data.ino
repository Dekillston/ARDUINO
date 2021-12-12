// Перевести строку
int another_line = 0;
//Include используемы ебиблиотеки
#include "DHT.h"
#include <TimeLib.h>
#include <Wire.h>
#include <DS1307RTC.h>
#include <Arduino.h>
#include "MHZ19_uart.h"
#include <SoftwareSerial.h>
// Вывести на экран 

SoftwareSerial mySerial(8, 9);

// Датчик уровня
#define Level_sensor 12
int Num_LS;
int OldNum_LS = 0;
// Датчик измерения температуры и влажности
#define DHTPIN 13 
#define DHTTYPE DHT22 
DHT dht(DHTPIN, DHTTYPE);
int NumDHT_humidity;
int OldNumDHT_humidity = 0;
int NumDHT_temperature;
int OldNumDHT_temperature = 0;
// Датчик углекислого газа
MHZ19_uart mhz19;
void setup() {
  Serial.begin(9600);
  // Включить экран

   mySerial.begin(9600);
  
  // Датчик уровня
  pinMode(Level_sensor, INPUT_PULLUP);
  // Датчик измерения температуры и влажности
  dht.begin();
  //Время
  setSyncProvider(RTC.get);
  //Датчик углекислого газа
  mhz19.begin(2, 4);
  mhz19.setAutoCalibration(false);
  int status = mhz19.getStatus();
  Serial.println(status);
  delay(2000);
  status = mhz19.getStatus();
  Serial.println(status);
  delay(2000);
}

void loop() {
  // Датчик уровня
  int Num_LS = digitalRead(Level_sensor);
  if(!(Num_LS == OldNum_LS)) {
    OldNum_LS = Num_LS;
    another_line = 1;
  }  
  // Датчик измерения температуры и влажности
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  NumDHT_humidity = h;
  if(!(NumDHT_humidity == OldNumDHT_humidity)) {
    OldNumDHT_humidity = NumDHT_humidity;
    //Serial.print("Влажность: ");
    //Serial.print(h);
    //Serial.print(" ");
    another_line = 1;
  }
  NumDHT_temperature = t;
  if(!(NumDHT_temperature == OldNumDHT_temperature)) {
    OldNumDHT_temperature = NumDHT_temperature;
    //Serial.print("Температура: ");
    //Serial.print(t);
    another_line = 1;
  }
  // Время
  

  // Перевод строки
  if(another_line == 1){
    // Датчик температуры и влажности
    Serial.print("Температура: ");
    Serial.print(t);
    Serial.print(" ");
    Serial.print("Влажность: ");
    Serial.print(h);
    Serial.print("   ");
    // Датчик уровня воды
    if(Num_LS == 0) {
      Serial.print("Вода поднялась!   ");  
      mySerial.print((String)"t3.bco="+63651+char(255)+char(255)+char(255));
      mySerial.print((String)"t3.txt=""\"Get down\""+char(255)+char(255)+char(255)); 
    } else if(Num_LS == 1) {
      Serial.print("Вода опустилась!   ");  
      mySerial.print((String)"t3.bco="+20093+char(255)+char(255)+char(255));
      mySerial.print((String)"t3.txt=""\"Rise up\""+char(255)+char(255)+char(255)); 
    }
    //Время
    Serial.print("Время: ");
    Serial.print(hour()); // Это часы
    Serial.print(":");
    Serial.print(minute()); //Это минуты
    Serial.print(":");
    Serial.print(second()); // Это секунды
    Serial.print("  ");
    Serial.print(day()); // Это дни
    Serial.print(".");
    Serial.print(month()); // Это месяц
    Serial.print(".");
    Serial.print(year()); // Это год
    Serial.print("   ");
    // Датчик углекислого газа
    Serial.print("Углекислый газ: ");
    Serial.print(mhz19.getPPM());
    Serial.println("");
    another_line = 0;
  }
  // Вывести на экран
    // Температура
    mySerial.print((String)"n0.val="+t+char(255)+char(255)+char(255));
    // Влажность
    mySerial.print((String)"n1.val="+h+char(255)+char(255)+char(255));
    // Углекислый газ
    mySerial.print((String)"n2.val="+mhz19.getPPM()+char(255)+char(255)+char(255));
    // Время
    String TimeLeft = ((String)hour() + ":" + minute() + ":" + second());
    TimeLeft = "\""+TimeLeft+"\"";
    mySerial.print((String)"t4.txt="+TimeLeft+char(255)+char(255)+char(255));

    String TimeRight = ((String)day()+"."+month()+"."+year());
    TimeRight = "\""+TimeRight+"\"";
    mySerial.print((String)"t5.txt="+TimeRight+char(255)+char(255)+char(255));
    delay(1000);
}
