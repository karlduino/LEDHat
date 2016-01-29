// have the LEDs pulse, with each pulse a different color

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
  byte color_int = random(256); // random color

  for(float angle=-1.570796326794897; angle<4.71238898038469; angle += 0.02454369260617026) { // from -pi/2 to 3*pi/2
    uint32_t color = Wheel(color_int, calc_brightness(angle));
    for(int i=0; i<N_LED; i++)
      strip.setPixelColor(i, color);
    strip.show();
    delay(10);
  }

}

// pulse_brightness
float calc_brightness(float angle)
{
  return (exp(sin(angle)) - 0.3678794411714423)*0.4254590641196608; // exp(sin(x)) scaled to [0,1]
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos, float brightness) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
    return strip.Color(brightness*(85 - WheelPos), 0, brightness*WheelPos);
  }
  if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, brightness*WheelPos, brightness*(85 - WheelPos));
  }
  WheelPos -= 170;
  return strip.Color(brightness*WheelPos, brightness*(85 - WheelPos), 0);
}
