#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <MIDI.h>


MIDI_CREATE_DEFAULT_INSTANCE();

#define SOLENOID_ON 4000  // Maximum PWM value for full activation
#define FIRST_NOTE_PITCH 21
#define OCTAVES 7

const int32_t pca_address[OCTAVES] = {0x45, 0x44, 0x46, 0x41, 0x42, 0x43, 0x40}; // order of PCA boards across piano
const int32_t index_mat[12] = {0, 7, 1, 8, 2, 3, 9, 4, 10, 5, 11, 6}; // order of notes across pwm signals of each PCA card
const int midiChannel = 1;
const int ledPin = 13;

Adafruit_PWMServoDriver pwm_arr[OCTAVES];

void from_pitch_to_index(uint8_t pitch, int* pca, int* index) 
{

  int normalized_pitch =  pitch - FIRST_NOTE_PITCH;
  
  if ( normalized_pitch >=3 && normalized_pitch <= 86 ) { 
    // full octaves
    *pca = (normalized_pitch - 3) / 12;
    *index = index_mat[(normalized_pitch - 3) % 12];
  } 
  else if (normalized_pitch == 87) 
  {
    // last note
    *pca = 6;
    *index = 12;
  }
  else
  {
    //placeholder incase we get wrong values
    *pca = 0;
    *index = 0;
  }

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
  Serial.begin(115200);
}

void loop() {
  // Call the MIDI library update method in the loop
  MIDI.read();
}

void activate_note(byte pitch, byte velocity, bool on)
{
  int index, octave;
  from_pitch_to_index(pitch, &octave, &index);
  
  if ( on ) 
  {
    pwm_arr[octave].setPWM(index, 0, SOLENOID_ON);
    digitalWrite(ledPin, HIGH);
  } 
  else 
  {
    pwm_arr[octave].setPWM(index, 0, 0);
    delay(40);
    // Turn off the LED
    digitalWrite(ledPin, LOW);
  }  
}

// Callback function for Note On messages
void handleNoteOn(byte channel, byte pitch, byte velocity) {
  // Handle Note On message for channel 1
  if (channel == midiChannel) {
    activate_note(pitch, velocity, true);
  }
}

// Callback function for Note Off messages
void handleNoteOff(byte channel, byte pitch, byte velocity) {
  // Handle Note On message for channel 1
  if (channel == midiChannel) {
    activate_note(pitch, velocity, false);
  }
}
