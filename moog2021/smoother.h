template <int LEN=32>
class Smoother {
    public:
        Smoother() {}
        
        void addData(float data);
        float average();
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
