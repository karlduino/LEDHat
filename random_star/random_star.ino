// one LED changes to a random color
// then update following a star pattern: 0,2,4,1,3

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 1
#define N_LED 5

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LED, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  strip.show();

  randomSeed(analogRead(A0));
}

void loop() {  
  uint32_t color = Wheel(random(256)); // random color
  int start = random(N_LED); // random LED to start things off
  int delay_amount = 100 + random(900);

  for(int i=0; i<N_LED; i++) {
    strip.setPixelColor((start + i*2) % N_LED , color); // 0, 2, 4, 1, 3
    strip.show();
    delay(delay_amount);
  }
  delay(250+random(1250)); // add a delay in-between
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(85 - WheelPos, 0, WheelPos);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos, 85 - WheelPos);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos, 85 - WheelPos, 0);
}
