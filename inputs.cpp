#include "inputs.h"
#include "pindefs.h"

constexpr int SWITCH_THRESHOLD = 1000;

// TODO define readSlideTop()
float readSlideTop();

// TODO define readSlideBottom()
float readSlideBottom();

// TODO define readFsrNeck()
float readFsrNeck();

// TODO define readFsrBody()
float readFsrBody();

bool readSwitch() {
    int rawVal = analogRead(PinDefs::PIN_SWITCH);
    return rawVal > SWITCH_THRESHOLD;
}

// TODO define readDial()
bool readDial();
