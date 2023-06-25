#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define NUM_OF_SOLENOIDS 5
#define PCA9685_ADDRESS 0x40
#define SOLENOID_ON 3000  // Maximum PWM value for full activation

const int buttons[NUM_OF_SOLENOIDS] = { 8, 7, 4, 2, 12 };   // Pins connected to the buttons
const int solenoids[NUM_OF_SOLENOIDS] = { 0, 1, 2, 3, 4 };  // Corresponding solenoid channels on PCA9685

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);

#define NOTE_C 0
#define NOTE_D 1
#define NOTE_E 2
#define NOTE_F 3
#define NOTE_G 4

void press_note(int sol, int ms) {
  pwm.setPWM(sol, 0, SOLENOID_ON);
  delay(ms);
  pwm.setPWM(sol, 0, 0);
  delay(300);
}

void setup() {
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);  // Set the PWM frequency to 20 Hz
}

void loop() {
  press_note(NOTE_G, 500);
  press_note(NOTE_E, 1000);
  press_note(NOTE_E, 1000);

  press_note(NOTE_F, 500);
  press_note(NOTE_D, 1000);
  press_note(NOTE_D, 1000);

  press_note(NOTE_C, 500);
  press_note(NOTE_D, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_F, 500);
  press_note(NOTE_G, 1000);
  press_note(NOTE_G, 1000);
  press_note(NOTE_G, 1000);

  press_note(NOTE_G, 500);
  press_note(NOTE_E, 1000);
  press_note(NOTE_E, 1000);

  press_note(NOTE_F, 500);
  press_note(NOTE_D, 1000);
  press_note(NOTE_D, 1000);

  press_note(NOTE_C, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_G, 500);
  press_note(NOTE_G, 500);
  press_note(NOTE_C, 500);

  press_note(NOTE_D, 500);
  press_note(NOTE_D, 500);
  press_note(NOTE_D, 500);
  press_note(NOTE_D, 500);
  press_note(NOTE_D, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_F, 500);

  press_note(NOTE_E, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_F, 500);
  press_note(NOTE_G, 500);

  press_note(NOTE_G, 500);
  press_note(NOTE_E, 1000);
  press_note(NOTE_E, 1000);

  press_note(NOTE_F, 500);
  press_note(NOTE_D, 1000);
  press_note(NOTE_D, 1000);

  press_note(NOTE_C, 500);
  press_note(NOTE_E, 500);
  press_note(NOTE_G, 500);
  press_note(NOTE_G, 500);
  press_note(NOTE_C, 500);
}