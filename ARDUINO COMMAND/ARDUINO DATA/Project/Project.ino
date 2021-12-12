// Используваемые библиотеки
  // Вывести на экран или получить данные с экрана
  #include <SoftwareSerial.h>
  // Датчик влажности и температуры
  #include "DHT.h" 
  /*
  // Датчик углекислого газа
  #include <Arduino.h>
  #include "MHZ19_uart.h"
  */
  // Датчик уровня воды
    // Библиотек нет
  // Датчик времени
  #include <TimeLib.h>
  #include <Wire.h>
  #include <DS1307RTC.h>
// Все порты
  // Вывести на экран
  #define ScreenTx 8
  #define ScreenRx 9
  // Датчик температуры и влажности
  #define DHTpin 13
  #define DHTname DHT22
  // Датчик углекислого газа
  /*
  #define MhzTx 2
  #define MhzRx 4
  */
  // Датчик уровня воды
  #define LevelSensorPin 12
// Подключение
  // Вывести на экран
  SoftwareSerial mySerial(ScreenTx, ScreenRx);
  // Датчик температуры и влажности
  DHT dht(DHTpin, DHTname);
  //Датчик углекислого газа
  /*
  MHZ19_uart mhz19;
  */
  // Получить данные с экрана
  int data;
//
// void setup
//
void setup() {
  Serial.begin(9600);  
  // Запуск
    // Вывести на экран и получить данные
    mySerial.begin(9600);
    // Датчик температуры и влажности
    dht.begin();
    // Датчик унлекислого газа
    /*
    mhz19.begin(MhzTx, MhzRx);
    mhz19.setAutoCalibration(false);
    */
    // Датчик уровня воды
    pinMode(LevelSensorPin, INPUT_PULLUP);
    // Датчик времени 
    setSyncProvider(RTC.get);
}
//
// void loop
//
void loop() {
  // Вывести
    // Датчик температуры и влажности
    DisplayScreen((String)"n0.val="+((int)dht.readTemperature()));
    DisplayScreen((String)"n1.val="+((int)dht.readHumidity()));
    // Датчик углекислого газа
    /*
    DisplayScreen((String)"n2.val="+mhz19.getPPM());
    */
    // Датчик уровня воды
    int NumLS = digitalRead(LevelSensorPin);
    if(NumLS == 0) {
      // Поднялась
      DisplayScreen((String)"t5.txt=""\"Rise up\"");
      DisplayScreen((String)"t5.bco="+63651);
    } else {
      // Опустилась
      DisplayScreen((String)"t5.txt=""\"Get down\"");
      DisplayScreen((String)"t5.bco="+20093);
    }
    // Датчик времени
    DisplayScreen((String)"t6.txt=""\""+hour()+":"+minute()+":"+second()+"\"");
    DisplayScreen((String)"t7.txt=""\""+day()+"."+month()+"."+year()+"\""); 
    // Получить данные с экрана
    data = mySerial.read();
    if(data > 0) {Serial.println(data);}
  delay(1);
}
//
// Используемые функции
//
  // Функция для ввода данных на экран
    void DisplayScreen(String team){
      mySerial.print((String)team+char(255)+char(255)+char(255));
    }
