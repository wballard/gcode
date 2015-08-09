
//read the hood open/close on pin 2, this is a switch to ground
#define HOOD_SWITCH_PIN 2

//motors are on 4,5,6,7 which is from the motor shield, PWM mode
//  http://www.dfrobot.com/wiki/index.php?title=Arduino_Motor_Shield_(L298N)_(SKU:DRI0009)
#define E1 5
#define M1 4
#define E2 6
#define M2 7

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
      digitalWrite(MAIN_RED, 0);
      digitalWrite(MAIN_GREEN, 0);
      digitalWrite(MAIN_BLUE, 0);
      hood = OPEN;
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
    int level = readPWM(LASER_INTENSITY) / 10;
    if (powerLevel != level) {
      powerLevel = level;
      //red light indicate the hood is closed and lasing is going
      //green light indicate the hood is closed and no lasing
      if (level) {
        analogWrite(MAIN_RED, 255 - (level * 25));
        analogWrite(MAIN_GREEN, 255);
        analogWrite(MAIN_BLUE, 255);
      } else {
        analogWrite(MAIN_RED, 255);
        analogWrite(MAIN_GREEN, 32);
        analogWrite(MAIN_BLUE, 255);
      }

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
