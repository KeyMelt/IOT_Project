const int potX = A0; // X-axis potentiometer connected to A0
const int potY = A1; // Y-axis potentiometer connected to A1
const int potZ = A2; // Z-axis potentiometer connected to A2

const int ledPin = 9; // LED to indicate an accident

const int outputMin = -10;           // Minimum accelerometer value
const int outputMax = 10;            // Maximum accelerometer value
const float accidentThreshold = 7.0; // Threshold for detecting an accident

// SoftwareSerial for debugging (virtual terminal)
#include <SoftwareSerial.h>
SoftwareSerial debugSerial(10, 11); // RX, TX for debugging

void setup()
{
    // Initialize debugging serial
    debugSerial.begin(9600);

    // Initialize LED pin
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // Debug message
    debugSerial.println("Standalone Accident Detection Test...");
}

void handleAccelerometer()
{
    // Read analog values from the potentiometers
    int rawX = analogRead(potX);
    int rawY = analogRead(potY);
    int rawZ = analogRead(potZ);

    // Map raw values (0-1023) to accelerometer range (-10 to 10)
    float accelX = map(rawX, 0, 1023, outputMin * 100, outputMax * 100) / 100.0;
    float accelY = map(rawY, 0, 1023, outputMin * 100, outputMax * 100) / 100.0;
    float accelZ = map(rawZ, 0, 1023, outputMin * 100, outputMax * 100) / 100.0;

    // Print accelerometer data to the debugging terminal
    debugSerial.print("Accel X = ");
    debugSerial.print(accelX, 2); // Limit to 2 decimal places
    debugSerial.print(" Accel Y = ");
    debugSerial.print(accelY, 2);
    debugSerial.print(" Accel Z = ");
    debugSerial.println(accelZ, 2);

    // Check for accident condition
    if (abs(accelX) > accidentThreshold || abs(accelY) > accidentThreshold || abs(accelZ) > accidentThreshold)
    {
        debugSerial.println("Accident detected!");
        digitalWrite(ledPin, HIGH); // Turn on LED
    }
    else
    {
        digitalWrite(ledPin, LOW); // Turn off LED
        debugSerial.println("Normal conditions");
    }
}

void loop()
{
    // Handle accelerometer data
    handleAccelerometer();

    delay(500); // Short delay for stability
}