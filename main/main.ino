#include <MIDI.h>
#include <Wire.h>
#include "notes.h"
#include "midi.h"
#include "solenoid_ctrl.h"
MIDI_CREATE_DEFAULT_INSTANCE();

NotePlayer player;
NoteInfo note_info_array[NUM_NOTES];

void setup() {
  Wire.begin();

  // Start the MIDI interface
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Serial.begin(9600);
  // Set the callback functions for Note On and Note Off messages
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

  Serial.begin(115200);

  initialize_sol();
  for (int i = 0; i < NUM_NOTES; i++) {
    note_info_array[i].last_time_on = -50;
    note_info_array[i].last_time_off = -50;
  }

}

void loop() {
  player.playNotes();
  // Call the MIDI library update method in the loop
  MIDI.read();
}


