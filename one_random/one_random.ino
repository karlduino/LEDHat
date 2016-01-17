// one random LED changes to pink and back
// others all blue

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 1
#define N_LED 5
const int brightness = 50;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LED, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
  for(int i=0; i<N_LED; i++) {
    strip.setPixelColor(i, strip.Color(0, brightness, brightness));
  }
  strip.show();

  randomSeed(analogRead(A0));
}

int last_selected = random(N_LED); // last one selected

void loop() {  
  int selected = random(N_LED);
  while(selected == last_selected) {
    selected = random(N_LED);
  }
    
  for(int i=1; i<=brightness; i++) {
    strip.setPixelColor(selected, strip.Color(i, brightness-i, brightness));
    strip.setPixelColor(last_selected, strip.Color(brightness-i, i, brightness));
    strip.show();
    delay(1000/brightness);
  }

  delay(1000);

  last_selected = selected;
}

