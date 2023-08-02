#include "solenoid_ctrl.h"
#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>

const int32_t pca_address[OCTAVES] = {0x45, 0x44, 0x46, 0x41, 0x42, 0x43, 0x40}; // order of PCA boards across piano
const int32_t index_mat[12] = {0, 7, 1, 8, 2, 3, 9, 4, 10, 5, 11, 6}; // order of notes across pwm signals of each PCA card
Adafruit_PWMServoDriver pwm_arr[OCTAVES];

void from_pitch_to_index(uint8_t pitch, int* octave, int* index) 
{
  int normalized_pitch =  pitch - FIRST_NOTE_PITCH;
  
  if ( normalized_pitch >=3 && normalized_pitch <= 86 ) { 
    // full octaves
    *octave = (normalized_pitch - 3) / 12;
    *index = index_mat[(normalized_pitch - 3) % 12];
  } 
  else if (normalized_pitch == 87) 
  {
    // last note
    *octave = 6;
    *index = 12;
  }
  else
  {
    //placeholder incase we get wrong values
    *octave = 0;
    *index = 0;
  }
}

void activate_note(byte pitch, byte velocity, bool on)
{
  int index, octave;
  from_pitch_to_index(pitch, &octave, &index);
  
  if ( on ) 
  {
    pwm_arr[octave].setPWM(index, 0, SOLENOID_ON);
    digitalWrite(LED_PIN, HIGH);
  } 
  else 
  {
    pwm_arr[octave].setPWM(index, 0, 0);
    // Turn off the LED
    digitalWrite(LED_PIN, LOW);
  }  
}

void initialize_sol()
{
  for (int i = 0; i < OCTAVES; i++) {
    // Allocate memory for the object and call the constructor with the desired argument
    pwm_arr[i] = Adafruit_PWMServoDriver(pca_address[i]);
    pwm_arr[i].begin();
    pwm_arr[i].setPWMFreq(50); 

    // reseting power for solenoids
    for (int j = 0; j < 12; j++) { 
       pwm_arr[i].setPWM(j, 0, 0);
    }
  }
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

