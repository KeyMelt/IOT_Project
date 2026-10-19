#include "secrets.h"
#include "accident_logic.h"

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <BlynkSimpleStream.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

// TinyGPS++ instance
TinyGPSPlus gps;

// SoftwareSerial for GPS
SoftwareSerial gpsSerial(3, 4); // RX, TX for SoftwareSerial (VGPS TX to pins 3 and 4)

// SoftwareSerial for debugging (virtual terminal)
SoftwareSerial debugSerial(10, 11); // RX, TX for debugging (pins 10 and 11)

// Accelerometer pins
const int potX = A0; // X-axis potentiometer connected to A0
const int potY = A1; // Y-axis potentiometer connected to A1
const int potZ = A2; // Z-axis potentiometer connected to A2

// LED pin to indicate an accident
const int ledPin = 9;

// Accelerometer range and threshold
const int outputMin = -10;
const int outputMax = 10;
const float accidentThreshold = 7.0;

void handleAccelerometer()
{
    // Read analog values from the potentiometers
    int rawX = analogRead(potX);
    int rawY = analogRead(potY);
    int rawZ = analogRead(potZ);

    float accelX = mapPotentiometerToAccel(rawX, 0, 1023, outputMin, outputMax);
    float accelY = mapPotentiometerToAccel(rawY, 0, 1023, outputMin, outputMax);
    float accelZ = mapPotentiometerToAccel(rawZ, 0, 1023, outputMin, outputMax);

    // Send accelerometer data to Blynk
    Blynk.virtualWrite(V2, accelX);
    Blynk.virtualWrite(V3, accelY);
    Blynk.virtualWrite(V4, accelZ);

    // Send accelerometer data to the virtual terminal (debugging)
    debugSerial.print("Accel X = ");
    debugSerial.print(accelX, 2);
    debugSerial.print(" Accel Y = ");
    debugSerial.print(accelY, 2);
    debugSerial.print(" Accel Z = ");
    debugSerial.println(accelZ, 2);

    // Accident detection logic
    if (isAccidentDetected(accelX, accelY, accelZ, accidentThreshold))
    {
        debugSerial.println("Accident detected!");
        digitalWrite(ledPin, HIGH); // Turn on LED
        Blynk.virtualWrite(V5, 1);  // Send accident signal to Blynk
    }
    else
    {
        digitalWrite(ledPin, LOW); // Turn off LED
        Blynk.virtualWrite(V5, 0); // Clear accident signal in Blynk
        debugSerial.println("Normal conditions");
    }
}

void handleGPS()
{
    while (gpsSerial.available())
    {
        char c = gpsSerial.read();
        if (gps.encode(c))
        {
            if (gps.location.isValid())
            {
                float latitude = gps.location.lat();
                float longitude = gps.location.lng();

                // Send GPS data to Blynk
                Blynk.virtualWrite(V0, latitude);
                Blynk.virtualWrite(V1, longitude);

                // Send GPS data to the virtual terminal (debugging)
                debugSerial.print("Latitude = ");
                debugSerial.print(latitude, 6);
                debugSerial.print(" Longitude = ");
                debugSerial.println(longitude, 6);
            }
            else
            {
                debugSerial.println("GPS signal not valid");
            }
        }
    }
}

void setup()
{
    // Initialize GPS serial
    gpsSerial.begin(9600);

    // Initialize debugging serial
    debugSerial.begin(9600);

    // Initialize hardware serial for Blynk
    Serial.begin(9600);

    // Initialize LED pin
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);

    // Initialize Blynk
    Blynk.config(Serial, auth);

    // Delay to ensure GPS initialization
    delay(2000);

    // Debug message
    debugSerial.println("GPS + Accelerometer + Accident Detection + Blynk Initialized");
}

void loop()
{
    // Process Blynk
    Blynk.run();

    // Handle GPS data
    handleGPS();

    // Handle accelerometer data and accident detection
    handleAccelerometer();

    delay(100); // Short delay for stability
}