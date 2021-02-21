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
    _targetMillis = millis();
}

void Arpeggiator::stop() {
    _active = false;
}

void Arpeggiator::setForward() {
    if (_direction != forward) {
        _direction = forward;
        _incNote();
        _incNote();
    }
}

void Arpeggiator::setReverse() {
    if (_direction != reverse) {
        _direction = reverse;
        _incNote();
        _incNote();
    }
}

void Arpeggiator::stopAtEnd(bool shouldStop) {
    _stopAtEnd = shouldStop;
}

void Arpeggiator::playNote(int index) {
    if (index >= _notesLen) {
        // Invalid index; do nothing
        return;
    }

    _currentNote = index;
    advance();
}

uint8_t Arpeggiator::advance() {
    return _nextNote();
}

int Arpeggiator::update() {
    if (!_active || millis() < _targetMillis) {
        return -1;
    }

    _targetMillis += _millisInterval;
    return advance();
}

uint8_t Arpeggiator::_nextNote() {
    uint8_t nextNote = _notes[_currentNote];
    analogWrite(_pin, nextNote);

    int nextInd = _incNote();
    
    /// Disable arpeggiator if stopAtEnd mode is enabled.
    if (_stopAtEnd && nextInd == 0) {
        _active = false;
    }

    return nextNote;
}

int Arpeggiator::_incNote() {
    _currentNote += _direction;
    _currentNote %= _notesLen;

    if (_currentNote < 0) {
        _currentNote += _notesLen;
    }

    return _currentNote;
}
