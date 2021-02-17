#include "circularsmoother.h"
#include "smoother.h"

CircularSmoother<16> smoother;
Smoother<64> smoother2;

float angle = 0.0;
float data = 0.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float randomNoise = ((float) random(-500, 500)) / 500;
//  Serial.println(randomNoise, 4);
  
  smoother.addData(angle + randomNoise);
  smoother2.addData(data + randomNoise);

  // Serial.println(smoother.averageSine(), 4);
  Serial.println(smoother2.average(), 4);
  delay(50);

  angle += 0.05;
}
