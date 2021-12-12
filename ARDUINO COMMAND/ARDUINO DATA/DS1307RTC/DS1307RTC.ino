#include <TimeLib.h> // Подключить Time библиотеку
#include <Wire.h> // Подключить стандартную библиотеку
#include <DS1307RTC.h>  // Подкоючить базоваую библиотеку DS1307 которую уже скачал

void setup()  {
  Serial.begin(9600); // Подключить сервер
  
  setSyncProvider(RTC.get);   // Функция подключения времени из RTC    
}

void loop(){
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
  Serial.println(year()); // Это год
  delay(1000); // Задержка
}
