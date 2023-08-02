#ifndef NOTES_H
#define NOTES_H

#include <Arduino.h>

class Note {
public:
  uint8_t pitch;
  unsigned long time_to_play;
  uint8_t velocity;

  Note(byte n, unsigned long t, byte v) : pitch(n), time_to_play(t), velocity(v) {}

  // Custom comparator for the priority queue
  bool operator>(const Note& other) const {
      return time_to_play < other.time_to_play;
  }
};

// Remember last time note was played. One instance of each note in the NoteInfo vector
struct NoteInfo {
  unsigned long last_time_on;
  unsigned long last_time_off;
};

class NotePlayer {
public:
  void addNote(byte pitch, unsigned long timeOffset, byte velocity);

  void playNotes();

private:
  struct Node {
      Note data;
      Node* next;

      Node(const Note& note, Node* nextNode) : data(note), next(nextNode) {}
  };

  Node* head = nullptr;

  void insertSorted(Note note);
};

#endif