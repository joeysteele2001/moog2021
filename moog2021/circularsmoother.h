#include "Arduino.h"

template <int LEN=32>
class CircularSmoother {
    public:
        CircularSmoother() {}

        void addData(float angle);
        float averageAngle();
        float averageCosine();
        float averageSine();
        float cosineSum();
        float sineSum();

    private:
        float _sines[LEN] = { 0.0 };
        float _sineSum = 0.0;
        float _cosines[LEN] = { 1.0 };
        float _cosineSum = 0.0;
        int _smoothIndex = 0;
};

////// TEMPLATE IMPLEMENTATIONS //////

template <int LEN>
void CircularSmoother<LEN>::addData(float angle) {
    float sine = sin(angle);
    float cosine = cos(angle);
    
    // update the sine sum
    _sineSum -= _sines[_smoothIndex];
    _sineSum += sine;

    // update the sine buffer
    _sines[_smoothIndex] = sine;

    // update the cosine sum
    _cosineSum -= _cosines[_smoothIndex];
    _cosineSum += cosine;

    // update the cosine buffer
    _cosines[_smoothIndex] = cos(angle);

    // increment and wrap the current data index
    _smoothIndex++;
    _smoothIndex %= LEN;
}

template <int LEN>
float CircularSmoother<LEN>::averageAngle() {
    return atan2(_sineSum, _cosineSum);
}

template <int LEN>
float CircularSmoother<LEN>::averageSine() {
    return _sineSum / LEN;
}

template <int LEN>
float CircularSmoother<LEN>::averageCosine() {
    return _cosineSum / LEN;
}

template <int LEN>
float CircularSmoother<LEN>::cosineSum() {
    return _cosineSum;
}

template <int LEN>
float CircularSmoother<LEN>::sineSum() {
    return _sineSum;
}
