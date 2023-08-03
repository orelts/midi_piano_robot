#include "midi.h"
#include "notes.h"
#include <Arduino.h>
#include "solenoid_ctrl.h"

#define RECOIL 45
const int midiChannel = 1;

extern NotePlayer player;
extern NoteInfo note_info_array[NUM_NOTES];

// Callback function for Note On messages
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Handle Note On message for channel 1
  if (channel == midiChannel) {
    unsigned long time_to_play = note_info_array[pitch-FIRST_NOTE_PITCH].last_time_off + RECOIL;
    player.addNote(pitch, time_to_play, velocity);
  }
}

// Callback function for Note Off messages
void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Handle Note Off message for channel 1
  if (channel == midiChannel) {
    activate_note(pitch, velocity, false);
    unsigned long current_time = millis();
    note_info_array[pitch-FIRST_NOTE_PITCH].last_time_off = current_time;
  }
}