#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define PCA9685_ADDRESS 0x40
#define SOLENOID_ON 4000  // Maximum PWM value for full activation

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);

void press_note(int sol, int force, int ms) {
  pwm.setPWM(sol, 0, SOLENOID_ON);
  delay(5);
  pwm.setPWM(sol, 0, force);

  delay(ms);

  pwm.setPWM(sol, 0, 0);
}

void setup() {
  pwm.begin();
  pwm.setPWMFreq(100);  // Set the PWM frequency to 20 Hz
}

void loop() {
    press_note(0, 3900, 1600);
    delay(1600);
}