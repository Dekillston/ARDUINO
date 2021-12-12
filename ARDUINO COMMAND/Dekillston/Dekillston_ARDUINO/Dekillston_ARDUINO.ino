// Библиотеки
  // Экран
    #include <SoftwareSerial.h>
  // Датчик температуры и влажности
    #include "DHT.h"
  // Датчик времени
    #include <TimeLib.h>
    #include <Wire.h>
    #include <DS1307RTC.h>
  // Датчик углекислого газа
    #include "Include_MHZ19B.h"
// Все порты
  // Экран
    #define ScreenTx 13
    #define ScreenRx 12
  // Датчик температуры и влажности
    #define DHTpin A0
    #define DHTname DHT22
  // Датчик воды
    #define WaterSensor A1
    #define WaterSensorAnalog A2
  // Реле
    #define ReleN1 8
    #define ReleN2 7 
  // Датчик углекислого газа
    #define MHZ19Bpin 5  
// Настройка
  // Экран 
    SoftwareSerial mySerial(ScreenTx, ScreenRx); 
    int ScreenDATA;
    int DATA_on_off = 1;
    int DATAdelay;
    // В какое время поменяли время
      // N1
        float WhatTimeN1 = 0;
      // N2
        float WhatTimeN2 = 0;
    // Выключенно или включенно авто
      // N1
        int SaveOnOffAutoN1 = 0;
      // N2
        int SaveOnOffAutoN2 = 0;
    // Сохранение выборов авто
      // N1
        int AutoSaveN1 = 1;
      // N2
        int AutoSaveN2 = 1;
    // По часовой N1
      // Верхний
        int TopFromToN1_1 = 0;
        int TopFromToN1_2 = 0;
        int TopFromToN1_3 = 0;
      // Нижний
        int BotFromToN1_1 = 0;
        int BotFromToN1_2 = 0;
        int BotFromToN1_3 = 0;
    // Каждый день N1
      // Верхний
        int TopEveryDayN1_1 = 0;
        int TopEveryDayN1_2 = 0;
        int TopEveryDayN1_3 = 0;
      // Нижний 
        int BotEveryDayN1_1 = 0;
        int BotEveryDayN1_2 = 0;
        int BotEveryDayN1_3 = 0;
    // По часовой N2
      // Верхний
        int TopFromToN2_1 = 0;
        int TopFromToN2_2 = 0;
        int TopFromToN2_3 = 0;
      // Нижний
        int BotFromToN2_1 = 0;
        int BotFromToN2_2 = 0;
        int BotFromToN2_3 = 0;
    // Каждый день N2
      // Верхний
        int TopEveryDayN2_1 = 0;
        int TopEveryDayN2_2 = 0;
        int TopEveryDayN2_3 = 0;
      // Нижний 
        int BotEveryDayN2_1 = 0;
        int BotEveryDayN2_2 = 0;
        int BotEveryDayN2_3 = 0;
  // Датчик температуры и влажности
    DHT dht(DHTpin, DHTname);
  // Датчик воды
    int DataWater;
    int DataWaterAnalog;
  // Датчик углекислого газа
    int DataMHZ19B;
//
// setup
//
void setup() {
  Serial.begin(9600); 
  mySerial.begin(9600);
  // Запуск
    // Датчик температуры и влажности 
      dht.begin();
    // Датчик воды
      pinMode(WaterSensor, INPUT_PULLUP); 
      pinMode(WaterSensorAnalog, INPUT_PULLUP); 
    // Датчик времени
      setSyncProvider(RTC.get); 
    // Реле
      pinMode(ReleN1, OUTPUT); 
      digitalWrite(ReleN1, HIGH);
      pinMode(ReleN2, OUTPUT);  
      digitalWrite(ReleN2, HIGH);
    // Датчик углекислого газа
      MHZ_19B_Stages(1, MHZ19Bpin);
}
//
// loop
//
void loop() {
  float MillisNUM = millis()/1000;
  // Вывод
    // Выключение данных
    ScreenDATA = mySerial.read();
    if(ScreenDATA > 0) {Serial.println(ScreenDATA);}
    if(ScreenDATA == 1) {DATA_on_off = 0;} else if(ScreenDATA == 2) {DATA_on_off = 1;}
    // Выкл вкл Авто
      // Левый
        if(ScreenDATA == 10) {
          digitalWrite(ReleN1, LOW);
        } else if(ScreenDATA == 11) {
          digitalWrite(ReleN1, HIGH);
        } else if(ScreenDATA == 12) {
          digitalWrite(ReleN1, HIGH);
        }
      // Правый
        if(ScreenDATA == 20) {
          digitalWrite(ReleN2, LOW);
        } else if(ScreenDATA == 21) {
          digitalWrite(ReleN2, HIGH);
        } else if(ScreenDATA == 22) {
          digitalWrite(ReleN2, HIGH);
        }
    // По часовой N1
      // Верхние
        // Часы
          if(ScreenDATA == 74) {
            TopFromToN1_1 = ZeroingTime(1, TopFromToN1_1, 23, "n42.val=");
          } else if(ScreenDATA == 75) {
            TopFromToN1_1 = ZeroingTime(0, TopFromToN1_1, 23, "n42.val=");
          }
        // Минуты
          if(ScreenDATA == 76) {
            TopFromToN1_2 = ZeroingTime(1, TopFromToN1_2, 59, "n43.val=");   
          } else if(ScreenDATA == 77) {
            TopFromToN1_2 = ZeroingTime(0, TopFromToN1_2, 59, "n43.val=");  
          }
        // Секунды
          if(ScreenDATA == 78) {
            TopFromToN1_3 = ZeroingTime(1, TopFromToN1_3, 59, "n44.val=");
          } else if(ScreenDATA == 79) {
            TopFromToN1_3 = ZeroingTime(0, TopFromToN1_3, 59, "n44.val=");  
          }
      // Нижние
        // Часы
          if(ScreenDATA == 80) {
            BotFromToN1_1 = ZeroingTime(1, BotFromToN1_1, 23, "n45.val=");
          } else if(ScreenDATA == 81) {
            BotFromToN1_1 = ZeroingTime(0, BotFromToN1_1, 23, "n45.val=");
          }
        // Минуты
          if(ScreenDATA == 82) {
            BotFromToN1_2 = ZeroingTime(1, BotFromToN1_2, 59, "n46.val=");
          } else if(ScreenDATA == 83) {
            BotFromToN1_2 = ZeroingTime(0, BotFromToN1_2, 59, "n46.val=");
          }
        // Секунды
          if(ScreenDATA == 84) {
            BotFromToN1_3 = ZeroingTime(1, BotFromToN1_3, 59, "n47.val=");
          } else if(ScreenDATA == 85) {
            BotFromToN1_3 = ZeroingTime(0, BotFromToN1_3, 59, "n47.val=");
          }
    // Каждый день N1
      // Верхний
        // Часы
          if(ScreenDATA == 50) {
            TopEveryDayN1_1 = ZeroingTime(1, TopEveryDayN1_1, 23, "n30.val=");
            WhatTimeN1 = MillisNUM;
          } else if(ScreenDATA == 51) {
            TopEveryDayN1_1 = ZeroingTime(0, TopEveryDayN1_1, 23, "n30.val=");
            WhatTimeN1 = MillisNUM;
          }
        // Минуты
          if(ScreenDATA == 52) {
            TopEveryDayN1_2 = ZeroingTime(1, TopEveryDayN1_2, 59, "n31.val=");
            WhatTimeN1 = MillisNUM;
          } else if(ScreenDATA == 53) {
            TopEveryDayN1_2 = ZeroingTime(0, TopEveryDayN1_2, 59, "n31.val=");
            WhatTimeN1 = MillisNUM;
          }
        // Секунды
        if(ScreenDATA == 54) {
            TopEveryDayN1_3 = ZeroingTime(1, TopEveryDayN1_3, 59, "n32.val=");
            WhatTimeN1 = MillisNUM;
          } else if(ScreenDATA == 55) {
            TopEveryDayN1_3 = ZeroingTime(0, TopEveryDayN1_3, 59, "n32.val=");
            WhatTimeN1 = MillisNUM;
          }
      // Нижний
        // Часы
          if(ScreenDATA == 56) {
            BotEveryDayN1_1 = ZeroingTime(1, BotEveryDayN1_1, 23, "n33.val=");
            WhatTimeN1 = MillisNUM;
          } else if(ScreenDATA == 57) {
            BotEveryDayN1_1 = ZeroingTime(0, BotEveryDayN1_1, 23, "n33.val=");
            WhatTimeN1 = MillisNUM;
          }
        // Минуты
          if(ScreenDATA == 58) {
            BotEveryDayN1_2 = ZeroingTime(1, BotEveryDayN1_2, 59, "n34.val=");
            WhatTimeN1 = MillisNUM;
          } else if(ScreenDATA == 59) {
            BotEveryDayN1_2 = ZeroingTime(0, BotEveryDayN1_2, 59, "n34.val=");
            WhatTimeN1 = MillisNUM;
          }
        // Секунды
          if(ScreenDATA == 60) {
            BotEveryDayN1_3 = ZeroingTime(1, BotEveryDayN1_3, 59, "n35.val=");
            WhatTimeN1 = MillisNUM;
          } else if(ScreenDATA == 61) {
            BotEveryDayN1_3 = ZeroingTime(0, BotEveryDayN1_3, 59, "n35.val=");
            WhatTimeN1 = MillisNUM;
          }
    // По часовой N2 
      // Верхнее
        // Часы
          if(ScreenDATA == 86) {
            TopFromToN2_1 = ZeroingTime(1, TopFromToN2_1, 23, "n48.val=");
          } else if(ScreenDATA == 87) {
            TopFromToN2_1 = ZeroingTime(0, TopFromToN2_1, 23, "n48.val=");
          }
        // Минуты
          if(ScreenDATA == 88) {
            TopFromToN2_2 = ZeroingTime(1, TopFromToN2_2, 59, "n49.val=");
          } else if(ScreenDATA == 89) {
            TopFromToN2_2 = ZeroingTime(0, TopFromToN2_2, 59, "n49.val=");
          }
        // Секунды
          if(ScreenDATA == 90) {
            TopFromToN2_3 = ZeroingTime(1, TopFromToN2_3, 59, "n50.val=");
          } else if(ScreenDATA == 91) {
            TopFromToN2_3 = ZeroingTime(0, TopFromToN2_3, 59, "n50.val=");
          }
      // Нижнее
        // Часы
          if(ScreenDATA == 92) {
            BotFromToN2_1 = ZeroingTime(1, BotFromToN2_1, 23, "n51.val=");
          } else if(ScreenDATA == 93) {
            BotFromToN2_1 = ZeroingTime(0, BotFromToN2_1, 23, "n51.val=");
          }
        // Минуты
          if(ScreenDATA == 94) {
            BotFromToN2_2 = ZeroingTime(1, BotFromToN2_2, 59, "n52.val=");
          } else if(ScreenDATA == 95) {
            BotFromToN2_2 = ZeroingTime(0, BotFromToN2_2, 59, "n52.val=");
          }
        // Секунды
          if(ScreenDATA == 96) {
            BotFromToN2_3 = ZeroingTime(1, BotFromToN2_3, 59, "n53.val=");
          } else if(ScreenDATA == 97) {
            BotFromToN2_3 = ZeroingTime(0, BotFromToN2_3, 59, "n53.val=");
          }
    // Каждый день N2
      // Верхнее
        // Часы
          if(ScreenDATA == 62) {
            TopEveryDayN2_1 = ZeroingTime(1, TopEveryDayN2_1, 23, "n36.val=");
            WhatTimeN2 = MillisNUM;
          } else if(ScreenDATA == 63) {
            TopEveryDayN2_1 = ZeroingTime(0, TopEveryDayN2_1, 23, "n36.val=");
            WhatTimeN2 = MillisNUM;
          }
        // Минуты
          if(ScreenDATA == 64) {
            TopEveryDayN2_2 = ZeroingTime(1, TopEveryDayN2_2, 59, "n37.val=");
            WhatTimeN2 = MillisNUM;
          } else if(ScreenDATA == 65) {
            TopEveryDayN2_2 = ZeroingTime(0, TopEveryDayN2_2, 59, "n37.val=");
            WhatTimeN2 = MillisNUM;
          }
        // Секунды
          if(ScreenDATA == 66) {
            TopEveryDayN2_3 = ZeroingTime(1, TopEveryDayN2_3, 59, "n38.val=");
            WhatTimeN2 = MillisNUM;
          } else if(ScreenDATA == 67) {
            TopEveryDayN2_3 = ZeroingTime(0, TopEveryDayN2_3, 59, "n38.val=");
            WhatTimeN2 = MillisNUM;
          }
      // Нижнее
        // Часы
          // Часы
          if(ScreenDATA == 68) {
            BotEveryDayN2_1 = ZeroingTime(1, BotEveryDayN2_1, 23, "n39.val=");
            WhatTimeN2 = MillisNUM;
          } else if(ScreenDATA == 69) {
            BotEveryDayN2_1 = ZeroingTime(0, BotEveryDayN2_1, 23, "n39.val=");
            WhatTimeN2 = MillisNUM;
          }
        // Минуты
          if(ScreenDATA == 70) {
            BotEveryDayN2_2 = ZeroingTime(1, BotEveryDayN2_2, 59, "n40.val=");
            WhatTimeN2 = MillisNUM;
          } else if(ScreenDATA == 71) {
            BotEveryDayN2_2 = ZeroingTime(0, BotEveryDayN2_2, 59, "n40.val=");
            WhatTimeN2 = MillisNUM;
          }
        // Секунды
          if(ScreenDATA == 72) {
            BotEveryDayN2_3 = ZeroingTime(1, BotEveryDayN2_3, 59, "n41.val=");
            WhatTimeN2 = MillisNUM;
          } else if(ScreenDATA == 73) {
            BotEveryDayN2_3 = ZeroingTime(0, BotEveryDayN2_3, 59, "n41.val=");
            WhatTimeN2 = MillisNUM;
          }
    // Запуск по часовой или каждый день
      // N1
        if(ScreenDATA == 31) {
          AutoSaveN1 = 1;  
        } else if(ScreenDATA == 32) {
          AutoSaveN1 = 2; 
          WhatTimeN1 = MillisNUM;  
        }
      // N2
        if(ScreenDATA == 41) {
          AutoSaveN2 = 1;  
        } else if(ScreenDATA == 42) {
          AutoSaveN2 = 2;  
          WhatTimeN2 = MillisNUM;
        }
     // Запуск авто
      // N1
        if(ScreenDATA == 12) {
          SaveOnOffAutoN1 = 1;
          WhatTimeN1 = MillisNUM;
        } else if(ScreenDATA == 10 || ScreenDATA == 11) {
          SaveOnOffAutoN1 = 0; 
        }
      // N2
        if(ScreenDATA == 22) {
          SaveOnOffAutoN2 = 1;
          WhatTimeN2 = MillisNUM;
        } else if(ScreenDATA == 20 || ScreenDATA == 21) {
          SaveOnOffAutoN2 = 0;
        }
    // Запуск 
      // N1
        //String Clockwise = ((String)hour()+":"+minute()+":"+second());
        long Clockwise = (((long)hour())*60*60)+(minute()*60)+second();
        if(SaveOnOffAutoN1 == 1) {
          // По часовой
            if(AutoSaveN1 == 1) {
              long ClockwiseN1PerformTOP = ((long)TopFromToN1_1*60*60)+(TopFromToN1_2*60)+TopFromToN1_3; 
              long ClockwiseN1PerformBOT = ((long)BotFromToN1_1*60*60)+(BotFromToN1_2*60)+BotFromToN1_3;   
              if(ClockwiseN1PerformTOP <= Clockwise && Clockwise < ClockwiseN1PerformBOT) {
                digitalWrite(ReleN1, LOW);        
              } else if(Clockwise >= ClockwiseN1PerformBOT) {
                digitalWrite(ReleN1, HIGH);  
              }
            }
          // Каждый день
            if(AutoSaveN1 == 2) {
              float ClockwiseBeginN1 = WhatTimeN1+((float)TopEveryDayN1_1*60*60+TopEveryDayN1_2*60+TopEveryDayN1_3);  
              float ClockwiseBeginN1_OFF = ClockwiseBeginN1+((float)BotEveryDayN1_1*60*60+BotEveryDayN1_2*60+BotEveryDayN1_3);
              if(ClockwiseBeginN1 <= MillisNUM && MillisNUM < ClockwiseBeginN1_OFF) {
                digitalWrite(ReleN1, LOW); 
              } else if(MillisNUM >= ClockwiseBeginN1_OFF) {
                digitalWrite(ReleN1, HIGH); 
                WhatTimeN1 = MillisNUM;  
              }
            }
        } 
      // N2
        if(SaveOnOffAutoN2 == 1) {
          // По часовой
            long ClockwiseN2PerformTOP = ((long)TopFromToN2_1*60*60)+(TopFromToN2_2*60)+TopFromToN2_3; 
            long ClockwiseN2PerformBOT = ((long)BotFromToN2_1*60*60)+(BotFromToN2_2*60)+BotFromToN2_3;   
            if(ClockwiseN2PerformTOP <= Clockwise && Clockwise < ClockwiseN2PerformBOT) {
              digitalWrite(ReleN2, LOW);        
            } else if(Clockwise >= ClockwiseN2PerformBOT) {
              digitalWrite(ReleN2, HIGH);  
            }
          // Каждый день 
            if(AutoSaveN2 == 2) {
              float ClockwiseBeginN2 = WhatTimeN2+((float)TopEveryDayN2_1*60*60+TopEveryDayN2_2*60+TopEveryDayN2_3);  
              float ClockwiseBeginN2_OFF = ClockwiseBeginN2+((float)BotEveryDayN2_1*60*60+BotEveryDayN2_2*60+BotEveryDayN2_3);
              if(ClockwiseBeginN2 <= MillisNUM && MillisNUM < ClockwiseBeginN2_OFF) {
                digitalWrite(ReleN2, LOW); 
              } else if(MillisNUM >= ClockwiseBeginN2_OFF) {
                digitalWrite(ReleN2, HIGH); 
                WhatTimeN2 = MillisNUM;  
              } 
            } 
        }
    // Пропуск
    if(DATA_on_off == 0) {DATAdelay = 0; return;}
    if(DATAdelay == 0) {} else {delay(1000);}
    DATAdelay = 1;
    // Датчик температуры и влажности
      DisplayScreen((String)"n0.val="+((int)dht.readTemperature()));
      DisplayScreen((String)"n1.val="+((int)dht.readHumidity()));
    // Датчик воды
      DataWater = digitalRead(WaterSensor);
      if(DataWater == 0) {
        DisplayScreen((String)"t3.txt=""\"Rise up\"");
        DisplayScreen((String)"t3.bco="+55787);
      } else {
        DisplayScreen((String)"t3.txt=""\"Get down\"");
        DisplayScreen((String)"t3.bco="+20093);
      }
      //
      DataWaterAnalog = digitalRead(WaterSensorAnalog);
      if(DataWaterAnalog == 0) {
        DisplayScreen((String)"t6.txt=""\"Rise up\"");
        DisplayScreen((String)"t6.bco="+55787);
      } else {
        DisplayScreen((String)"t6.txt=""\"Get down\"");
        DisplayScreen((String)"t6.bco="+20093);
      }
    // Датчик времени
      DisplayScreen((String)"t4.txt=""\""+hour()+":"+minute()+":"+second()+"\"");
      DisplayScreen((String)"t5.txt=""\""+day()+"."+month()+"."+year()+"\"");
    // Датчик углекислого газа
      DisplayScreen((String)"n2.val="+DataMHZ19B);
}
//
//  yield
//
void yield() {
  int ConnectMHZ19B = MHZ_19B_Stages(2, MHZ19Bpin);
  if(ConnectMHZ19B < 1000 && ConnectMHZ19B > 200) {DataMHZ19B = ConnectMHZ19B;}
}
//
// Используемые функции
//
  // Функция для ввода данных на экран
    void DisplayScreen(String team){
      mySerial.print((String)team+char(255)+char(255)+char(255));
    }
  // функция времени
    int ZeroingTime(int Action, int num, int Limit, String Bring) {
      if(Action == 0) {
        num = num-1;
      } else if(Action == 1) {
        num = num+1;
      }
      //
      if(num > Limit) {
        num = 0;
      } else if(num < 0) {
        num = Limit;
      }
      //
      DisplayScreen((String)Bring+num);
      //
      return num;
    }
