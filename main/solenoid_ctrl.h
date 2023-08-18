#ifndef SOL_H
#define SOL_H

#include <Arduino.h>

#define FIRST_NOTE_PITCH 21
#define OCTAVES 7
#define NUM_NOTES 88
#define SOLENOID_MAX 4095  // Maximum PWM value for full activation
#define SOLENOID_MIN 3500  // Maximum PWM value for min activation
#define V_MAX 127 

#define LED_PIN 13

void from_pitch_to_index(uint8_t pitch, int* octave, int* index);
void activate_note(byte pitch, byte velocity, bool on);
void initialize_sol();

#endif