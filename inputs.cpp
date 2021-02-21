#include "inputs.h"
#include "pindefs.h"

constexpr int SLIDE_TOP_HIGH_VALUE = 550;
constexpr int SLIDE_TOP_LOW_VALUE = 315;
constexpr int SLIDE_TOP_PRESS_THRESHOLD = 100;

constexpr int SLIDE_BOTTOM_HIGH_VALUE = 350;
constexpr int SLIDE_BOTTOM_LOW_VALUE = 250;
constexpr int SLIDE_BOTTOM_PRESS_THRESHOLD = 100;

constexpr int FSR_NECK_HIGH_VALUE = 1023;
constexpr int FSR_NECK_PRESS_THRESHOLD = 1000;

constexpr int FSR_BODY_HIGH_VALUE = 220;
constexpr int FSR_BODY_PRESS_THRESHOLD = 50;

constexpr int SWITCH_THRESHOLD = 1020;

constexpr int DIAL_LOW_VALUE = 0;
constexpr int DIAL_HIGH_VALUE = 1023;

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

static bool fsrNeckIsPressed(int rawVal) {
    return rawVal > FSR_NECK_PRESS_THRESHOLD;
}

bool fsrNeckIsPressed() {
    int rawVal = analogRead(PinDefs::PIN_FSR_NECK);
    return fsrNeckIsPressed(rawVal);
}

float readFsrNeck() {
    int rawVal = analogRead(PinDefs::PIN_FSR_NECK);
    if (!fsrNeckIsPressed(rawVal)) {
        return 0.0;
    } else {
        float mapped = floatMapLin(rawVal, FSR_NECK_PRESS_THRESHOLD, FSR_NECK_HIGH_VALUE);
        return _constrain(mapped);
    }
}

static bool fsrBodyIsPressed(int rawVal) {
    return rawVal > FSR_BODY_PRESS_THRESHOLD;
}

bool fsrBodyIsPressed() {
    int rawVal = analogRead(PinDefs::PIN_FSR_BODY);
    return fsrBodyIsPressed(rawVal);
}

float readFsrBody() {
    int rawVal = analogRead(PinDefs::PIN_FSR_BODY);
    if (!fsrBodyIsPressed(rawVal)) {
        return 0.0;
    } else {
        float mapped = floatMapLin(rawVal, FSR_BODY_PRESS_THRESHOLD, FSR_BODY_HIGH_VALUE);
        return _constrain(mapped);
    }
}

bool readSwitch() {
    int rawVal = analogRead(PinDefs::PIN_SWITCH);
    return rawVal > SWITCH_THRESHOLD;
}

float readDial() {
    int rawVal = analogRead(PinDefs::PIN_DIAL);
    float mapped = floatMapLin(rawVal, DIAL_LOW_VALUE, DIAL_HIGH_VALUE);
    return _constrain(mapped);
}
