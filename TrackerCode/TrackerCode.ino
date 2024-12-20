#define BLYNK_TEMPLATE_ID "TMPL2_q8H_bJi"
#define BLYNK_TEMPLATE_NAME "AssetTracker"
#define BLYNK_AUTH_TOKEN "OkBHIdVkFTnC3pwCIv5Vs7oOYrdeuC-t"

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <BlynkSimpleStream.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;


// Analog pins for accelerometer potentiometers
const int potX = A0; // X-axis
const int potY = A1; // Y-axis
const int potZ = A2; // Z-axis

const int outputMin = -10; // Minimum accelerometer value
const int outputMax = 10;  // Maximum accelerometer value

// SoftwareSerial for debugging (virtual terminal)
#include <SoftwareSerial.h>
// TinyGPS++ instance
TinyGPSPlus gps;

// SoftwareSerial for GPS module
SoftwareSerial gpsSerial(3, 4); // RX, TX for SoftwareSerial (GPS TX to pin 3)

// SoftwareSerial for debugging (virtual terminal)
SoftwareSerial debugSerial(10, 11); // RX, TX for debugging

void setup()
{
    // Initialize GPS serial
    gpsSerial.begin(9600);
    // Initialize debugging serial
    debugSerial.begin(9600);

    // Initialize hardware Serial for Blynk
    Serial.begin(9600);

    // Initialize Blynk
    Blynk.config(Serial, auth);
    debugSerial.println("Testing Blynk and GPS connection...");

    // Debug message

    debugSerial.println("Testing Blynk and Accelerometers...");
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

    // Send accelerometer data to Blynk
    Blynk.virtualWrite(V2, accelX);
    Blynk.virtualWrite(V3, accelY);
    Blynk.virtualWrite(V4, accelZ);

    // Print accelerometer data to the debugging terminal
    debugSerial.print("Accel X = ");
    debugSerial.print(accelX, 2); // Limit to 2 decimal places
    debugSerial.print(" Accel Y = ");
    debugSerial.print(accelY, 2);
    debugSerial.print(" Accel Z = ");
    debugSerial.println(accelZ, 2);

}

void loop()
{
    // Process Blynk
    Blynk.run();
    // Handle accelerometer data
    handleAccelerometer();

    // Read and process GPS data
    while (gpsSerial.available() > 0)
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

                // Print GPS data to the debugging terminal
                debugSerial.print("Latitude = ");
                debugSerial.print(latitude, 6);
                debugSerial.print(" Longitude = ");
                debugSerial.println(longitude, 6);
            }
            else
            {
                // Print invalid GPS signal message
                debugSerial.println("GPS signal not valid");
            }
        }
    }

    delay(500); // Short delay for stability
}