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

//main interior lights
#define MAIN_RED 11
#define MAIN_GREEN 10
#define MAIN_BLUE 9

//PWM read back from the laser activation
#define LASER_INTENSITY A0

int powerLevel = -1;

#define UNKNOWN -1
#define OPEN HIGH
#define CLOSED LOW
int hood = UNKNOWN;
int hoodSwitch = UNKNOWN;

void setup() {

  pinMode(HOOD_SWITCH_PIN, INPUT_PULLUP);

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(E1, OUTPUT);
  pinMode(E2, OUTPUT);

  pinMode(MAIN_RED, OUTPUT);
  pinMode(MAIN_GREEN, OUTPUT);
  pinMode(MAIN_BLUE, OUTPUT);

  pinMode(LASER_INTENSITY, INPUT);

  strip.begin();
  //doesn't appear that enough power is available
  strip.setBrightness(192);
  strip.show();
}

void loop() {
  //tight loop since we are doing neopixels, not bothering with interrupts

  //motor control here, switch on -- open the hood, switch off -- close it
  //counting on the limit switch stops in the linear motors for the hood
  int hoodSwitch = digitalRead(HOOD_SWITCH_PIN);

  //an open hood switch, let's see if we should fire up opening the hood.
  if (hoodSwitch == OPEN) {
    //only on a state change
    if (hood != hoodSwitch) {
      //close em!
      digitalWrite(M1, HIGH);
      digitalWrite(M2, HIGH);
      digitalWrite(E1, HIGH);
      digitalWrite(E2, HIGH);
      //white lights indicate the hood is open and the system is safe
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        strip.setPixelColor(i, 255, 255, 255);
      }
      digitalWrite(MAIN_RED, 0);
      digitalWrite(MAIN_GREEN, 0);
      digitalWrite(MAIN_BLUE, 0);
      hood = OPEN;
      strip.show();
    }
  } else {
    //only on a state change
    if (hood != hoodSwitch) {
      //open em!
      digitalWrite(M1, LOW);
      digitalWrite(M2, LOW);
      digitalWrite(E1, HIGH);
      digitalWrite(E2, HIGH);
      hood = CLOSED;
      powerLevel = UNKNOWN;
    }
  }
  //closed hood switch, need to monitor power levels
  if (hood == CLOSED) {
    int level = floor(readPWM(LASER_INTENSITY) * strip.numPixels());
    if (powerLevel != level) {
      powerLevel = level;
      //red light indicate the hood is closed and lasing can happen
      //laser strength indicator the neopixels like a graphical equalizer, dialing
      //up the red to full intensity based on laser strength
      for(uint16_t i=0; i<strip.numPixels(); i++) {
        if (i < level && level) {
          strip.setPixelColor(i, 255, 0, 0);
        } else {
          strip.setPixelColor(i, 32, 0, 0);
        }
      }
      strip.show();
      digitalWrite(MAIN_RED, 0);
      digitalWrite(MAIN_GREEN, 1);
      digitalWrite(MAIN_BLUE, 1);
    }
  }
}
//Takes in reading pins and outputs pwm frequency and duty cycle.
double readPWM(int readPin){
  int highTime = 0;
  int lowTime = 0;

  int highpulse = pulseIn(readPin,HIGH);
  int lowpulse = pulseIn(readPin,LOW);
  if (highpulse == 0 && lowpulse == 0) {
    //little noise check
    if (analogRead(readPin) && analogRead(readPin) && analogRead(readPin)) {
      return 1.0;
    } else {
      return 0.0;
    }
  }
  return (highpulse/(double (lowpulse+highpulse)));
}
