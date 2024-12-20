#define BLYNK_TEMPLATE_ID "TMPL2_q8H_bJi"
#define BLYNK_TEMPLATE_NAME "AssetTracker"
#define BLYNK_AUTH_TOKEN "OkBHIdVkFTnC3pwCIv5Vs7oOYrdeuC-t"

#include <BlynkSimpleStream.h>

// Blynk authentication token
char auth[] = BLYNK_AUTH_TOKEN;

void setup()
{
    // Initialize hardware Serial for communication with Blynk
    Serial.begin(9600);

    // Initialize Blynk
    Blynk.config(Serial, auth);

    // Debug message to ensure the code is running
    Serial.println("Testing Blynk connection...");
}

void loop()
{
    // Process Blynk
    Blynk.run();

    // Send a test message to Virtual Pin 0
    Blynk.virtualWrite(V0, "Hello, Blynk!");

    // Debug message to verify loop execution
    Serial.println("Blynk test message sent.");

    delay(1000); // Send a message every second
}