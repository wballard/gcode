#include <Adafruit_NeoPixel.h>


#define LED_PIN 13
#define ON_PIN 15
#define FIRE_PIN 3
#define STATUS_PIN 4
#define BLINK 50
#define PIXELS 8

int fire = 0;
unsigned long last = 0;
int blinkCycle = 1;
Adafruit_NeoPixel status = Adafruit_NeoPixel(PIXELS, STATUS_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(ON_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FIRE_PIN, OUTPUT);
  status.begin();
  status.setPixelColor(0, 255, 0, 255);
  status.show();
}

void loop()
{
  fire = digitalRead(ON_PIN);
  unsigned long current = millis();
  digitalWrite(LED_PIN, fire);
  digitalWrite(FIRE_PIN, fire);
  if (current - last > BLINK) {
    last = current;
    blinkCycle++;
    if (blinkCycle == PIXELS) {
      blinkCycle = 1;
    }
    
    //fun! color rotation
    status.setPixelColor(0, 255 / blinkCycle, 0, 255);
    
    //rest of the light are a laser marquee
    for (int i = 1; i < PIXELS; i++) {
      status.setPixelColor(i, 0, 0, 0);
    }
    
    if (fire || 1) {
      status.setPixelColor(blinkCycle, 255, 0, 0);
    }
    
    status.show();
  }
}
