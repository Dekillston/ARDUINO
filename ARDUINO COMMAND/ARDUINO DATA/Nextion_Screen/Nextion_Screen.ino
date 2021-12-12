#include <SoftwareSerial.h> // Библеотека

String _TEXT_ = "\"Woow\""; // Переменная для текста
int _NUM_ = 666; // Переменная для числа

SoftwareSerial mySerial(8, 9); // Порты 1 - Tx 2 - Rx

void setup() {
  mySerial.begin(9600); // Подключить сервер экрана
}

void loop() {
  mySerial.print((String)"t0.txt="+_TEXT_+char(255)+char(255)+char(255));  // Для текста
  //mySerial.print((String)"n0.val="+_NUM_+char(255)+char(255)+char(255)); // Для числа
  delay(500);
}
