#include "circularsmoother.h"
#include "smoother.h"

CircularSmoother<16> smoother;
float angle = 0.0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  float randomNoise = ((float) random(-500, 500)) / 500;
//  Serial.println(randomNoise, 4);
  
  smoother.addData(angle + randomNoise);

  Serial.println(smoother.averageSine(), 4);
  delay(50);

  angle += 0.05;
}
