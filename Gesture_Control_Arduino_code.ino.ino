#include <NewPing.h>

#define TRIG_PIN_1 2  // Trigger pin of 1st Sensor
#define ECHO_PIN_1 3   // Echo pin of 1st Sensor
#define TRIG_PIN_2 4   // Trigger pin of 2nd Sensor
#define ECHO_PIN_2 5   // Echo pin of 2nd Sensor
#define MAX_DISTANCE 200 // Maximum distance to check (in cm)

NewPing sonar1(TRIG_PIN_1, ECHO_PIN_1, MAX_DISTANCE); // Create the first sensor object
NewPing sonar2(TRIG_PIN_2, ECHO_PIN_2, MAX_DISTANCE); // Create the second sensor object

void setup() {
    Serial.begin(9600);  // Start serial communication at 9600 baud
}

void loop() {
    // Calculate distances from both sensors
    int distL = sonar1.ping_cm();  // Get distance from left sensor
    int distR = sonar2.ping_cm();  // Get distance from right sensor

    // Uncomment for debugging
    /*
    Serial.print("L=");
    Serial.println(distL);
    Serial.print("R=");
    Serial.println(distR);
    */

    // Pause Mode - Detect both hands
    if ((distL > 40 && distR > 40) && (distL < 50 && distR < 50)) { // Detect both hands
        Serial.println("Play/Pause");
        delay(500); // Delay to prevent multiple triggers
    }

    // Control Modes
    // Lock Left - Control Mode
    if (distL >= 13 && distL <= 17) {
        delay(100); // Hand Hold Time
        if (distL >= 13 && distL <= 17) {
            Serial.println("Left Locked");
            while (distL <= 40) {
                distL = sonar1.ping_cm(); // Get updated distance
                if (distL < 10) { // Hand pushed in
                    Serial.println("Vup");
                    delay(300);
                }
                if (distL > 20) { // Hand pulled out
                    Serial.println("Vdown");
                    delay(300);
                }
            }
        }
    }

    // Lock Right - Control Mode
    if (distR >= 13 && distR <= 17) {
        delay(100); // Hand Hold Time
        if (distR >= 13 && distR <= 17) {
            Serial.println("Right Locked");
            while (distR <= 40) {
                distR = sonar2.ping_cm(); // Get updated distance
                if (distR < 10) { // Right hand pushed in
                    Serial.println("Rewind");
                    delay(300);
                }
                if (distR > 20) { // Right hand pulled out
                    Serial.println("Forward");
                    delay(300);
                }
            }
        }
    }

    delay(200); // Delay to stabilize readings
}