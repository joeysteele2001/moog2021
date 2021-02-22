#ifndef ACCELMAG_H
#define ACCELMAG_H

#include "Arduino.h"

class AccelMag {
  public:
    AccelMag();
    void begin();
    int8_t getMagX();
    int8_t getAccX();
 
  private:
    static constexpr int OUT_X_L = 0x28;
    static constexpr int MAGADDR = 0x1E;
    static constexpr int ACCADDR = 0x6B;
};

#endif // ACCELMAG_H
