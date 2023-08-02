#include "notes.h"
#include "solenoid_ctrl.h"
#include <Arduino.h>

extern NoteInfo note_info_array[NUM_NOTES];

void NotePlayer::addNote(byte pitch, unsigned long time_to_play, byte velocity) {
    Note newNote(pitch, time_to_play, velocity);
    insertSorted(newNote);
}

void NotePlayer::insertSorted(Note note) {
    Node* newNode = new Node(note, nullptr);
    newNode->data = note;
    newNode->next = nullptr;

    if (head == nullptr || note.time_to_play < head->data.time_to_play) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr && current->next->data.time_to_play <= note.time_to_play) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void NotePlayer::playNotes() {
  unsigned long current_time = millis();

  while (head != nullptr && head->data.time_to_play <= current_time) {
    // Remove and obtain the note from the queue
    Note nextNoteToPlay = head->data;
    // Remove the note from the queue
    Node* temp = head;
    head = head->next;
    delete temp;

    uint8_t pitch = nextNoteToPlay.pitch;
    uint8_t velocity = nextNoteToPlay.velocity;

    activate_note(pitch, velocity, true);       
    note_info_array[pitch-FIRST_NOTE_PITCH].last_time_on = current_time; 
  }
}