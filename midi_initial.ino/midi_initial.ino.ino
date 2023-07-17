#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();

// MIDI channel to listen to
const int midiChannel = 1;

// LED pin
const int ledPin = 13;

void setup() {
  // Start the MIDI interface
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Serial.begin(9600);
  // Set the callback functions for Note On and Note Off messages
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

  // Set the LED pin as an output
  pinMode(ledPin, OUTPUT);
  // Turn off the LED
  digitalWrite(ledPin, LOW);
}

void loop() {
  // Call the MIDI library update method in the loop
  MIDI.read();
}

// Callback function for Note On messages
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Handle Note On message for channel 1
  if (channel == midiChannel) {
    // Process the MIDI message
    // Print a message to Serial Monitor
    Serial.print("Note On: Pitch = ");
    Serial.print(pitch);
    Serial.print(", Velocity = ");
    Serial.println(velocity);

    // Turn on the LED
    digitalWrite(ledPin, HIGH);
  }
}

// Callback function for Note Off messages
void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Handle Note Off message for channel 1
  if (channel == midiChannel) {
    // Process the MIDI message
    // Print a message to Serial Monitor
    Serial.print("Note Off: Pitch = ");
    Serial.print(pitch);
    Serial.print(", Velocity = ");
    Serial.println(velocity);

    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }
}
