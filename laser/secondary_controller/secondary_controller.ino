#include <Adafruit_NeoPixel.h>

//read the hood open/close on pin 2, this is a switch to ground
#define HOOD_SWITCH_PIN 2

//motors are on 4,5,6,7 which is from the motor shield, PWM mode
//  http://www.dfrobot.com/wiki/index.php?title=Arduino_Motor_Shield_(L298N)_(SKU:DRI0009)
#define E1 5
#define M1 4
#define E2 6
#define M2 7

//neopixel status indicator connect the neopixel to pin 3
#define NEOPIXEL_PIN 3
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

//PWM read back from the laser activation
#define LASER_INTENSITY 0

int loopCount = 0;

void setup() {

  pinMode(HOOD_SWITCH_PIN, INPUT_PULLUP);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  strip.begin();
  strip.show();
}

void loop() {
  //tight loop since we are doing neopixels, not bothering with interrupts

  int level = analogRead(LASER_INTENSITY) / (1024 / 8);

  //motor control here, switch on -- open the hood, switch off -- close it
  //counting on the limit switch stops in the linear motors for the hood
  int hoodSwitch = digitalRead(HOOD_SWITCH_PIN);
  //high switch is open
  if (hoodSwitch == HIGH) {
    //close em!
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    digitalWrite(E1, HIGH);
    digitalWrite(E2, HIGH);
    //white lights indicate the hood is open and the system is safe
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, 254, 254, 254);
    }
  } else {
    //open em!
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    digitalWrite(E1, HIGH);
    digitalWrite(E2, HIGH);
    //red light indicate the hood is closed and lasing can happen
    //laser strength indicator the neopixels like a graphical equalizer, dialing
    //up the red to full intensity based on laser strength
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, (i <= level && level) ? 255 : 127, 0, 0);
    }
  }
  if (loopCount++ % 1000 == 0) {
    loopCount = 0;
    strip.show();
  }

}
