#include <Adafruit_NeoPixel.h>


#define LED_PIN 13
#define ON_PIN 15
#define INTENSITY_PIN 16
#define FIRE_PIN 3
#define STATUS_PIN 4
#define FIRE_INTENSITY_PIN 5
#define BLINK 50
#define PIXELS 8

int fire = 0;
int intensity = 0;
unsigned long last = 0;
int blinkCycle = 1;
Adafruit_NeoPixel status = Adafruit_NeoPixel(PIXELS, STATUS_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  pinMode(ON_PIN, INPUT);
  pinMode(INTENSITY_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(FIRE_PIN, OUTPUT);
  pinMode(FIRE_INTENSITY_PIN, OUTPUT);
  status.begin();
  status.setPixelColor(0, 255, 0, 255);
  status.show();
  Serial.begin(9600);
}

void loop()
{
  fire = digitalRead(ON_PIN);
  digitalWrite(LED_PIN, fire);
  digitalWrite(FIRE_PIN, fire);
  intensity = analogRead(INTENSITY_PIN) / 3;
  analogWrite(FIRE_INTENSITY_PIN, intensity);
  Serial.println(intensity);
  Serial.println(' ');
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
