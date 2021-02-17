#ifndef SMOOTHER_H
#define SMOOTHER_H

/// Smooth data with random noise using a simple averager.
/// Template parameter LEN is the number of past points to average.
template <int LEN=32>
class Smoother {
    public:
        Smoother() {}
        
        /// Feed a new data point to the Smoother.
        void addData(float data);

        /// Get the current average.
        float average();

        /// Get the current sum of data.
        /// Prefer using this method instead of average() if possible to avoid a floating-point division.
        float sum();

    private:
        float _data[LEN] = { 0.0 };
        float _sum = 0.0;
        int _smoothIndex = 0;
};

////// TEMPLATE IMPLEMENTATIONS //////

template <int LEN>
void Smoother<LEN>::addData(float data) {
    // update the sum
    _sum -= _data[_smoothIndex];
    _sum += data;

    // update the data buffer
    _data[_smoothIndex] = data;

    // increment and wrap the current data index
    _smoothIndex++;
    _smoothIndex %= LEN;
}

template <int LEN>
float Smoother<LEN>::average() {
    return _sum / LEN;
}

template <int LEN>
float Smoother<LEN>::sum() {
    return _sum;
}

#endif // SMOOTHER_H
