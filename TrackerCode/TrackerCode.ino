#define BLYNK_TEMPLATE_ID "TMPL2_q8H_bJi"
#define BLYNK_TEMPLATE_NAME "AssetTracker"
#define BLYNK_AUTH_TOKEN "OkBHIdVkFTnC3pwCIv5Vs7oOYrdeuC-t"

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <BlynkSimpleStream.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

TinyGPSPlus gps;

// SoftwareSerial for VGPS
SoftwareSerial gpsSerial(2, 3); // RX, TX for SoftwareSerial (VGPS TX to pin 2)
SoftwareSerial debugSerial(10, 11);

const int potX = A0; // X-axis potentiometer connected to A0
const int potY = A1; // Y-axis potentiometer connected to A1
const int potZ = A2; // Z-axis potentiometer connected to A2

const int outputMin = -10; // Minimum accelerometer value
const int outputMax = 10;  // Maximum accelerometer value

void handleAccelerometer()
{
    int rawX = analogRead(potX);
    int rawY = analogRead(potY);
    int rawZ = analogRead(potZ);

    float accelX = map(rawX, 0, 1023, outputMin * 100, outputMax * 100) / 100.0;
    float accelY = map(rawY, 0, 1023, outputMin * 100, outputMax * 100) / 100.0;
    float accelZ = map(rawZ, 0, 1023, outputMin * 100, outputMax * 100) / 100.0;

    Blynk.virtualWrite(V2, accelX);
    Blynk.virtualWrite(V3, accelY);
    Blynk.virtualWrite(V4, accelZ);
}

void handleGPS(TinyGPSPlus &gps)
{
    if (gps.location.isValid())
    {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        Blynk.virtualWrite(V0, latitude);
        Blynk.virtualWrite(V1, longitude);

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

void setup()
{
    gpsSerial.begin(9600);
    debugSerial.begin(9600); // Initialize debugging serial
    Serial.begin(9600);
    Blynk.config(Serial, auth);
    delay(2000);
}

void loop()
{
    Blynk.run();

    while (gpsSerial.available() > 0)
    {
        char c = gpsSerial.read();
        if (gps.encode(c))
        {
            handleGPS(gps);
        }
    }

    handleAccelerometer();
    delay(100);
}