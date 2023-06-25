#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SOLENOID_ON 4000  // Maximum PWM value for full activation
#define PCA9685_ADDRESS 0x40


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(PCA9685_ADDRESS);

const int numButtons = 5;  // Number of buttons
const int buttonPins[numButtons] = {2, 4, 7, 8, 12};  // Button pins
const int solenoids[numButtons] = {0, 1, 2, 3, 4};  // Button pins

void press_note(int sol, int ms) {
  pwm.setPWM(sol, 0, SOLENOID_ON);
  delay(ms);
}

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }
  Wire.begin();
  pwm.begin();
  pwm.setPWMFreq(50);  // Set the PWM frequency to 20 Hz
}

void loop() {
  Serial.println(" pressed");
  for (int i = 0; i < numButtons; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      // Button is pressed
      // Perform the same action for each pressed button
      handleButtonPress(i);
    } else {
        pwm.setPWM(solenoids[i], 0, 0);
    }
  }

  // Other code logic
}

void handleButtonPress(int buttonIndex) {
  // Perform action for the pressed button
  // You can customize this function to define the desired action
  Serial.print("Button ");
  Serial.print(buttonIndex + 1);
  Serial.println(" pressed");

  press_note(solenoids[buttonIndex], 50);
}