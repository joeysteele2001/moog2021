/*
    CIRCULARSMOOTH: simulates reading data from a rotating compass with added
                    random noise, then prints smoothed data to serial
*/

#include <smoothers.h>
#include <smoother.h>
#include <circularsmoother.h>

// Make a new smoother with default smooth length.
CircularSmoother<> cs;

// The current angle the simulated compass is facing, in radians.
float currentAngle = 0.0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Get some random noise from -1 to 1 radian.
    float noise = (float) random(-500, 500) / 500;
    float data = currentAngle + noise;

    // Feed the simulated compass value to the smoother.
    cs.addData(data);

    // Print the smoothed data to 4 decimal places.
    float smoothed = cs.averageAngle();
    
    /* 
        Try running the following line instead of the previous line. If you use 
        averageCosine(), you will eliminate the sharp drop between -180 deg 
        and +180 deg.
    */

    // float smoothed = cs.averageCosine();

    Serial.println(smoothed, 4);

    // Increment the current angle, as if the compass is spinning slowly.
    currentAngle += 0.05;
    delay(50);
}
