#include "arpeggiator.h"

Arpeggiator::Arpeggiator(int arp_pin) {
    pinMode(arp_pin, OUTPUT);
    _pin = arp_pin;
}

void Arpeggiator::setTempo(float bpm) {
    int newMillisInterval = round(60000 / bpm); // milliseconds per beat
    int millisIntervalDiff = newMillisInterval - _millisInterval;
    _targetMillis += millisIntervalDiff; // update the target millis according to the new tempo
    _millisInterval = newMillisInterval;
}

void Arpeggiator::setNotes(uint8_t notes[], int notesLen) {
    _notes = notes;
    _notesLen = notesLen;
    _currentNote = 0;
}

void Arpeggiator::start() {
    _active = true;
    _currentNote = 0;
    _targetMillis = millis();
}

void Arpeggiator::stop() {
    _active = false;
}

int Arpeggiator::update() {
    if (!_active || millis() < _targetMillis) {
        return -1;
    }

    uint8_t nextNote = _notes[_currentNote];
    analogWrite(_pin, nextNote);

    _currentNote++;
    _currentNote %= _notesLen;

    _targetMillis += _millisInterval;

    return nextNote;
}
