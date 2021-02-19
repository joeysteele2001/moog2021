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

        /// Update the arpeggiator and change notes if applicable.
        /// Run this function as often as possible!
        /// Returns the note that was changed to, or -1 if nothing changed.
        int update();

    private:
        bool _active = false;
        int _millisInterval;
        unsigned long _targetMillis;
        int _pin;
        uint8_t *_notes;
        int _notesLen;
        int _currentNote = 0;
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

#endif // ARPEGGIATOR_H