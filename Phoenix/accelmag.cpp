#include "accelmag.h"

#include <Wire.h>

AccelMag::AccelMag() {}

void AccelMag::begin() {
  // Begin i2c communication with the accelerometer/magnometer
  Wire.begin();
  Wire.beginTransmission(MAGADDR);
  Wire.endTransmission();
  Wire.beginTransmission(ACCADDR);
  Wire.endTransmission(); 
}

int8_t AccelMag::getMagX() {
  Wire.beginTransmission(MAGADDR);
  Wire.write(OUT_X_L);
  Wire.endTransmission(false);
  Wire.requestFrom(MAGADDR, 2, true);
  int8_t X_out_M = (Wire.read() | Wire.read() << 8) / 256;
  Wire.endTransmission(true);

  return X_out_M;
}

int8_t AccelMag::getAccX() {
  Wire.beginTransmission(ACCADDR);
  Wire.write(OUT_X_L);
  Wire.endTransmission(false);
  Wire.requestFrom(ACCADDR, 2, true);
  int8_t X_out_ACC = (Wire.read() | Wire.read() << 8) / 256;
  Wire.endTransmission(true);

  return X_out_ACC;
}
