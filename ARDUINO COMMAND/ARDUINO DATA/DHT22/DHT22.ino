#include "DHT.h"

#define DHTPIN A0 // Переменная
#define DHTTYPE DHT22 // Переменная

DHT dht(DHTPIN, DHTTYPE); //Обозначить порт и название самого датчика и дать название

void setup() {
Serial.begin(9600); //Назначитьь сервер

dht.begin(); // Запустить затчик
}

void loop() {

int h = dht.readHumidity(); // Назначить влажность
int t = dht.readTemperature(); //Назначить температуру

Serial.println("Влажность: ");
Serial.println(h);
Serial.println("Температура: ");
Serial.println(t);

delay(1000); // Назначить задержку для цикла
}
