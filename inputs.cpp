#include "inputs.h"
#include "pindefs.h"

constexpr int SLIDE_TOP_HIGH_VALUE = 550;
constexpr int SLIDE_TOP_LOW_VALUE = 315;
constexpr int SLIDE_TOP_PRESS_THRESHOLD = 100;

constexpr int SLIDE_BOTTOM_HIGH_VALUE = 350;
constexpr int SLIDE_BOTTOM_LOW_VALUE = 250;
constexpr int SLIDE_BOTTOM_PRESS_THRESHOLD = 100;

constexpr int SWITCH_THRESHOLD = 1000;

// Map a float from between fromLow and fromHigh to between 0 and 1.
static float floatMapLin(float value, float fromLow, float fromHigh) {
    return (value - fromLow) / (fromHigh - fromLow);
}

// Constrain a value between 0 and 1.
static inline float _constrain(float value) {
    if (value < 0.0) {
        return 0.0;
    } else if (value > 1.0) {
        return 1.0;
    } else {
        return value;
    }
}

static bool slideTopIsPressed(int rawVal) {
    return rawVal > SLIDE_TOP_PRESS_THRESHOLD;
}

float readSlideTop() {
    int rawVal = analogRead(PinDefs::PIN_SLIDE_TOP);
    if (!slideTopIsPressed(rawVal)) {
        return 0.0;
    } else {
        float mapped = floatMapLin(rawVal, SLIDE_TOP_LOW_VALUE, SLIDE_TOP_HIGH_VALUE);
        return _constrain(mapped);
    }
}

bool slideTopIsPressed() {
    int rawVal = analogRead(PinDefs::PIN_SLIDE_TOP);
    return slideTopIsPressed(rawVal);
}

static bool slideBottomIsPressed(int rawVal) {
    return rawVal > SLIDE_BOTTOM_PRESS_THRESHOLD;
}

float readSlideBottom() {
    int rawVal = analogRead(PinDefs::PIN_SLIDE_BOTTOM);
    if (!slideBottomIsPressed(rawVal)) {
        return 0.0;
    } else {
        float mapped = floatMapLin(rawVal, SLIDE_BOTTOM_LOW_VALUE, SLIDE_BOTTOM_HIGH_VALUE);
        return _constrain(mapped);
    }
}

bool slideBottomIsPressed() {
    int rawVal = analogRead(PinDefs::PIN_SLIDE_BOTTOM);
    return slideBottomIsPressed(rawVal);
}

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
