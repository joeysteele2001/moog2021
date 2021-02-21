#ifndef ARPEGGIATOR_H
#define ARPEGGIATOR_H

#include "Arduino.h"

class Arpeggiator {
    public:
        /// Create a new arpeggiator that outputs to the given PWM or DAC pin.
        Arpeggiator(int arp_pin);

        /// Set the arpeggiator's tempo. All notes are quarter notes.
        void setTempo(float bpm);

        /// Set the notes that the arpeggiator plays.
        /// These are just the numbers that are output to the pin.
        void setNotes(uint8_t notes[], int notesLen);

        /// Activate the arpeggiator.
        void start();

        /// Stop the arpeggiator.
        void stop();

        /// Set notes to play forward.
        void setForward();

        /// Set notes to play backward.
        void setReverse();

        /// Set whether the arpeggiator should stop when it reaches the end of the chord.
        void stopAtEnd(bool shouldStop);

        /// Set which index of the arpeggiator's notes to play.
        void playNote(int index);

        /// Manually advance to the next note.
        /// Return the new note value.
        uint8_t advance();

        /// Update the arpeggiator and change notes if applicable.
        /// Run this function as often as possible!
        /// Returns the note that was changed to, or -1 if nothing changed.
        int update();

        /// Return whether the arpeggiator is currently active.
        bool isActive();

    private:
        bool _active = false;
        bool _stopAtEnd = false;
        bool _hasStarted = false;
        int _millisInterval;
        unsigned long _targetMillis;
        int _pin;
        uint8_t *_notes;
        int _notesLen;
        int _currentNote = 0;
        char _direction = 1;

        static constexpr char forward = 1;
        static constexpr char reverse = -1;

        /// Advance to the next note unconditionally.
        /// Returns the next note value.
        uint8_t _nextNote();

        /// Increment the _currentNote index, wrapping back to zero when necessary.
        int _incNote();

        /// Return whether the arpeggiator's _currentNote index is at the end.
        bool _isAtEnd();
};

namespace ScaleDegree {
    constexpr uint8_t tonic = 0;
    constexpr uint8_t min2 = 5;
    constexpr uint8_t maj2 = 10;
    constexpr uint8_t min3 = 15;
    constexpr uint8_t maj3 = 20;
    constexpr uint8_t p4 = 25;
    constexpr uint8_t aug4 = 30;
    constexpr uint8_t tritone = 30;
    constexpr uint8_t dim5 = 30;
    constexpr uint8_t p5 = 35;
    constexpr uint8_t min6 = 40;
    constexpr uint8_t maj6 = 45;
    constexpr uint8_t min7 = 50;
    constexpr uint8_t maj7 = 55;
    constexpr uint8_t octave = 60;
};

namespace NoteName {
    using namespace ScaleDegree;
    constexpr uint8_t C = tonic;
    constexpr uint8_t Csharp = min2;
    constexpr uint8_t Dflat = min2;
    constexpr uint8_t D = maj2;
    constexpr uint8_t Dsharp = min3;
    constexpr uint8_t Eflat = min3;
    constexpr uint8_t E = maj3;
    constexpr uint8_t F = p4;
    constexpr uint8_t Fsharp = tritone;
    constexpr uint8_t Gflat = tritone;
    constexpr uint8_t G = p5;
    constexpr uint8_t Gsharp = min6;
    constexpr uint8_t Aflat = min6;
    constexpr uint8_t A = maj6;
    constexpr uint8_t Asharp = min7;
    constexpr uint8_t Bflat = min7;
    constexpr uint8_t B = maj7;
    constexpr uint8_t Coct = octave;
}

#endif // ARPEGGIATOR_H