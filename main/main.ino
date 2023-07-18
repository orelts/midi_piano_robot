#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();

#define SOLENOID_ON 4000  // Maximum PWM value for full activation
#define FIRST_NOTE_PITCH 21
#define OCTAVES 7

const int32_t pca_address[OCTAVES] = {0x45, 0x44, 0x46, 0x41, 0x42, 0x43, 0x40};
const int midiChannel = 1;
const int ledPin = 13;

Adafruit_PWMServoDriver pwm_arr[OCTAVES];

void from_pitch_to_index(byte pitch, int* pca, int* index) {

  int normalized_pitch =  static_cast<int>(pitch); - FIRST_NOTE_PITCH;
  
  if ( ( normalized_pitch) && (normalized_pitch  <= 14) ) {
    // first octave 
    *pca = 0;
    *index = normalized_pitch;
  } 
  else if (normalized_pitch == 87) 
  {
      // last note
    *pca = 6;
    *index = 12;
  }
  else
  {
    *pca = (normalized_pitch - 3) / 12;
    *index = (normalized_pitch - 3) % 12;
  }

}
void press_note(int note, int octave, int force, int note_time_in_ms, Adafruit_PWMServoDriver* pwm_arr) {

  pwm_arr[1].setPWM(note, 0, SOLENOID_ON);
  delay(10);
  pwm_arr[1].setPWM(note, 0, force);
  
  delay(note_time_in_ms);

  pwm_arr[1].setPWM(note, 0, 0);
  
}

void setup() {
  Wire.begin();

  // Start the MIDI interface
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // Serial.begin(9600);
  // Set the callback functions for Note On and Note Off messages
  MIDI.setHandleNoteOn(handleNoteOn);
  MIDI.setHandleNoteOff(handleNoteOff);

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
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Call the MIDI library update method in the loop
  MIDI.read();
}

// Callback function for Note On messages
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  int index, pca;
  from_pitch_to_index(pitch, &pca, &index);
  // Handle Note On message for channel 1
  if (channel == midiChannel) {
    pwm_arr[pca].setPWM(index, 0, SOLENOID_ON);
    // // Turn on the LED
    digitalWrite(ledPin, HIGH);
    // Serial.print("Note On: Pitch = ");
    // Serial.print(pitch);
    // Serial.print(", Velocity = ");
    // Serial.println(velocity);



  }
}

// Callback function for Note Off messages
void handleNoteOff(byte channel, byte pitch, byte velocity) {

  int index, pca;
  from_pitch_to_index(pitch, &pca, &index);

  // Handle Note Off message for channel 1
  if (channel == midiChannel) {
    pwm_arr[pca].setPWM(index, 0, 0);

    // Turn off the LED
    digitalWrite(ledPin, LOW);
    // Print a message to Serial Monitor
    // Serial.print("Note Off: Pitch = ");
    // Serial.print(pitch);
    // Serial.print(", Velocity = ");
    // Serial.println(velocity);
  }
}
