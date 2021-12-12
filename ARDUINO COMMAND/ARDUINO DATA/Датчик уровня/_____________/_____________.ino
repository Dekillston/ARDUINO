int PIN_BUTTON = A1; // Создать переменную с пином

void setup() {
  Serial.begin(9600); // Подключить сервер
  pinMode(PIN_BUTTON, INPUT_PULLUP); // Настроить пин как вход и подключить подтягивающий резистер
}

void loop() {
  Serial.println(digitalRead(PIN_BUTTON)); // Вывести специальной командой
  delay(100); // Задержка
}
