#include "inputs.h"
#include "pindefs.h"

constexpr int SLIDE_TOP_HIGH_VALUE = 520;
constexpr int SLIDE_TOP_LOW_VALUE = 335;

constexpr int SLIDE_TOP_PRESS_THRESHOLD = 100;
constexpr int SWITCH_THRESHOLD = 1000;

// Map a float from between fromLow and fromHigh to between 0 and 1.
static float floatMapLin(float value, float fromLow, float fromHigh) {
    return (value - fromLow) / (fromHigh - fromLow);
}

static bool slideTopIsPressed(int rawVal) {
    return rawVal > SLIDE_TOP_PRESS_THRESHOLD;
}

float readSlideTop() {
    int rawVal = analogRead(PinDefs::PIN_SLIDE_TOP);
    if (!slideTopIsPressed(rawVal)) {
        return 0.0;
    } else {
        return floatMapLin(rawVal, SLIDE_TOP_LOW_VALUE, SLIDE_TOP_HIGH_VALUE);
    }
}

bool slideTopIsPressed() {
    int rawVal = analogRead(PinDefs::PIN_SLIDE_TOP);
    return slideTopIsPressed(rawVal);
}

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
