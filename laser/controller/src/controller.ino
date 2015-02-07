#include <Adafruit_NeoPixel.h>

#define LED_PIN 13

#define LASER_FIRE_PIN 3
#define LASER_INTENSITY_PIN 4

#define NEOPIXEL_STATUS_PIN 16

#define TINYG_FIRE_PIN 14
#define TINYG_INTENSITY_PIN 15

#define BLINK 50
#define PIXELS 8

int fire = 0;
int intensity = 0;
unsigned long last = 0;
int blinkCycle = 1;
Adafruit_NeoPixel status = Adafruit_NeoPixel(PIXELS, NEOPIXEL_STATUS_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(TINYG_FIRE_PIN, INPUT);
  pinMode(TINYG_INTENSITY_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(LASER_FIRE_PIN, OUTPUT);
  pinMode(LASER_INTENSITY_PIN, OUTPUT);
  status.begin();
  status.setPixelColor(0, 255, 0, 255);
  status.show();
}

void loop()
{
  fire = digitalRead(TINYG_FIRE_PIN);
  digitalWrite(LED_PIN, fire);
  digitalWrite(LASER_FIRE_PIN, fire);
  //by 3 rather than four to scale up to 5V from 3.3V tinyG
  intensity = analogRead(TINYG_INTENSITY_PIN) / 3;
  analogWrite(LASER_INTENSITY_PIN, intensity);
  unsigned long current = millis();

  if (current - last > BLINK) {
    last = current;
    blinkCycle++;
    if (blinkCycle == PIXELS) {
      blinkCycle = 1;
    }

    for (int i = 0; i < PIXELS; i++) {
      status.setPixelColor(i, 0, 0, 255);
    }

    //firing marqee
    if (fire) {
      status.setPixelColor(blinkCycle, 255, 0, 0);
    }

    status.show();
  }
}
