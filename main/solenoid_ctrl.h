#ifndef SOL_H
#define SOL_H

#include <Arduino.h>

#define FIRST_NOTE_PITCH 21
#define OCTAVES 7
#define NUM_NOTES 88
#define SOLENOID_ON 4000  // Maximum PWM value for full activation
#define LED_PIN 13

void from_pitch_to_index(uint8_t pitch, int* octave, int* index);
void activate_note(byte pitch, byte velocity, bool on);
void initialize_sol();

#endif