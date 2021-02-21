#ifndef INPUTS_H
#define INPUTS_H

#include "Arduino.h"

/// Read the top sliding pot with appropriate scaling.
/// Returns 0 if not pressed.
/// For sanity, returns a value between 0 and 1.
float readSlideTop();

/// Return whether the top sliding pot is being pressed.
bool slideTopIsPressed();

/// Read the bottom sliding pot with appropriate scaling.
/// For sanity, returns a value between 0 and 1.
float readSlideBottom();

/// Read the neck force-sensitive resistor with appropriate scaling.
/// For sanity, returns a value between 0 and 1.
float readFsrNeck();

/// Read the body force-sensitive resistor with appropriate scaling.
/// For sanity, returns a value between 0 and 1.
float readFsrBody();

/// Read the body's switch, either on or off.
bool readSwitch();

/// Read the body's dial with appropriate scaling.
/// For sanity, returns a value between 0 and 1.
bool readDial();

#endif // INPUTS_H
