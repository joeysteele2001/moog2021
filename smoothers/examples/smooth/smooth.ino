/*
    SMOOTH: reads analog data from INPUT_PIN and prints a smoothed average of
            the data to serial
*/

#include <smoothers.h>
#include <smoother.h>
#include <circularsmoother.h>

// The pin to read analog data from. Change this to your desired pin.
#define INPUT_PIN A0

// Make a new smoother with default smooth length.
Smoother<> s;

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Read in data, between 0 and 1023.
    int data = analogRead(INPUT_PIN);

    // Scale data to between 0 and 10.
    s.addData((float) data / 1024 * 10);

    // Print the smoothed data to 4 decimal places.
    float smoothed = s.average();
    Serial.println(smoothed, 4);

    delay(50);
}
