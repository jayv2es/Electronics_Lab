void setup() {
  pinMode(3, OUTPUT); //Blue LED
  pinMode(6, OUTPUT); //Red LED
}

void loop() {
  blinker(100000, 500000);    // Blink LEDs with periods 0.2s(blue), 1s(red)
}

// PRE: T3, T6 > 0
// POST: LEDs blink at periods 2*T3(blue), 2*T6(red)
void blinker (unsigned int T3, unsigned int T6){
  static unsigned long last_us_3 = 0;
  static unsigned long last_us_6 = 0;
  if ((micros() - last_us_3) >= T3){ 
    last_us_3 = micros(); 
    digitalWrite(3, !digitalRead(3));
  }
  if ((micros() - last_us_6) >= T6){ 
    last_us_6 = micros(); 
    digitalWrite(6, !digitalRead(6));
  }
}
