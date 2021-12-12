int prevVal = LOW;
long th, tl, h, l, ppm;
// Функция
int MHZ_19B_Stages(int action, int pin) {
  if(action == 1) {
    pinMode(pin, INPUT);
  } else if(action == 2) {
    long tt = millis();
    int myVal = digitalRead(pin);
    //
    if (myVal == HIGH) {
      if (myVal != prevVal) {
        h = tt;
        tl = h - l;
        prevVal = myVal;
      }
    }  else {
      if (myVal != prevVal) {
        l = tt;
        th = l - h;
        prevVal = myVal;
        ppm = 5000 * (th - 2) / (th + tl - 4);
        return ppm;
      }
    }
  }
}
