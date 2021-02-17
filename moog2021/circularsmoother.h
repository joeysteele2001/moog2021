#ifndef CIRCULARSMOOTHER_H
#define CIRCULARSMOOTHER_H

/// Smooth circular data with random noise using an averager.
/// Circular data is any data that can be converted into an "angle" which loops back on itself.
/// Template parameter LEN is the number of past points to average.
template <int LEN=32>
class CircularSmoother {
    public:
        CircularSmoother() {}

        /// Feed a new data point to the CircularSmoother.
        /// Angle must be given in radians.
        void addData(float angle);

        /// Get the current average raw angle.
        /// Ranges from -pi to +pi.
        /// This is still sensitive to sudden jumps on the edge of -pi and +pi.
        float averageAngle();

        /// Get the average of the cosines of the angles.
        /// Ranges from -1 to +1.
        /// This method has no sudden jumps in its output, unlike averageAngle().
        float averageCosine();

        /// Get the average of the sines of the angles.
        /// Ranges from -1 to +1.
        /// This method has no sudden jumps in its output, unlike averageAngle();
        float averageSine();

        /// Get the current sum of the cosines of the angles.
        /// Prefer using this method instead of the averageXX() methods if possible to avoid a floating-point division.
        float cosineSum();

        /// Get the current sum of the sines of the angles.
        /// Prefer using this method instead of the averageXX() methods if possible to avoid a floating-point division.
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

#endif // CIRCULARSMOOTHER_H
