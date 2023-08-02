#ifndef MIDI_SOL_H
#define MIDI_SOL_H

#include <Arduino.h>

#define MID_INTERVAL_IN_MS 1
// Callback function for Note On messages
void handleNoteOn(byte channel, byte pitch, byte velocity);

// Callback function for Note Off messages
void handleNoteOff(byte channel, byte pitch, byte velocity);


#endif