#define BLYNK_TEMPLATE_ID "TMPL2_q8H_bJi"
#define BLYNK_TEMPLATE_NAME "AssetTracker"
#define BLYNK_AUTH_TOKEN "OkBHIdVkFTnC3pwCIv5Vs7oOYrdeuC-t"

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <BlynkSimpleStream.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

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

    // Debug message
    debugSerial.println("Testing Blynk and GPS connection...");
}

void loop()
{
    // Process Blynk
    Blynk.run();

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