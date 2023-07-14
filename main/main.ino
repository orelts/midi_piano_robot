#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define NUM_OF_SOLENOIDS 35
#define SOLENOID_ON 4000  // Maximum PWM value for full activation

Adafruit_PWMServoDriver* pwm_arr;

#define NOTE_C 0
#define NOTE_C_MAJOR 1
#define NOTE_D 2
#define NOTE_D_MAJOR 3
#define NOTE_E 4
#define NOTE_F 5
#define NOTE_F_MAJOR 6
#define NOTE_G 7
#define NOTE_G_MAJOR 8
#define NOTE_A 9
#define NOTE_A_MAJOR 10
#define NOTE_B 11

void press_note(int note, int octave, int force, int note_time_in_ms, Adafruit_PWMServoDriver* pwm_arr) {

  pwm_arr[octave].setPWM(note, 0, SOLENOID_ON);
  delay(10);
  pwm_arr[octave].setPWM(note, 0, force);
  
  delay(note_time_in_ms);

  pwm_arr[octave].setPWM(note, 0, 0);
  
}

void setup() {
  Wire.begin();
  int nof_pca9685 = ((NUM_OF_SOLENOID + 11) / 12); // num of pca_9685 rounded up.


  for (int i = 0; i < nof_pca9685; i++) {
        // Calculate constructor argument based on the index
    int i2caddress = 0x40 + i;

    // Allocate memory for the object and call the constructor with the desired argument
    pwm_arr[i] = new Adafruit_PWMServoDriver(i2caddress);
    pwm_arr[i].begin();
    pwm_arr[i].setPWMFreq(50); 

    // reseting power for solenoids
    for (int j = 0; j < 12; j++) { 
       pwm_arr[i].setPWM(j, 0, 10);
    }
  }
}

void loop() {
  int octave = 0;
  int force = 4000;
  int note_time = note_time;

  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_E, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_F, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_D, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_C, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_F, octave, force, note_time, pwm_arr);
  press_note(NOTE_G, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_G, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_G, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_E, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_F, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_D, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_C, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_C, octave, force, note_time, pwm_arr);

  press_note(NOTE_D, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_F, octave, force, note_time, pwm_arr);

  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_F, octave, force, note_time, pwm_arr);
  press_note(NOTE_G, octave, force, note_time, pwm_arr);

  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_E, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_F, octave, force, note_time, pwm_arr);
  press_note(NOTE_D, octave, force, 2 * note_time, pwm_arr);
  press_note(NOTE_D, octave, force, 2 * note_time, pwm_arr);

  press_note(NOTE_C, octave, force, note_time, pwm_arr);
  press_note(NOTE_E, octave, force, note_time, pwm_arr);
  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_G, octave, force, note_time, pwm_arr);
  press_note(NOTE_C, octave, force, note_time, pwm_arr);
}