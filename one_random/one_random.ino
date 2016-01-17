// one random LED changes to pink and back
// others all blue

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

int brightness = 60;

void loop() {
  int selected = random(N_LED);

  for(int i=0; i<N_LED; i++) {
    strip.setPixelColor(i, strip.Color(0, brightness, brightness));
  }
  strip.show();

  for(int i=1; i<=brightness; i++) {
    strip.setPixelColor(selected, strip.Color(i, brightness-i, brightness));
    strip.show();
    delay(2000/brightness);
  }

  delay(2000);

  for(int i=brightness-1; i>=0; i--) {
    strip.setPixelColor(selected, strip.Color(i, brightness-i, brightness));
    strip.show();
    delay(2000/brightness);
  }

}

