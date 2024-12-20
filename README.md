Asset Tracker Project

Overview

The Asset Tracker project is a GPS-enabled system for tracking the location and motion of assets (e.g., vehicles or equipment). The system includes accident detection capabilities based on accelerometer readings. The project is designed to work with the Blynk IoT platform for remote monitoring and control, providing real-time data to users.

Features
	1.	GPS Tracking:
	•	Continuously captures and updates the latitude and longitude of the tracked asset.
	•	Sends GPS data to the Blynk platform for remote monitoring.
	2.	Accelerometer Monitoring:
	•	Tracks motion along the X, Y, and Z axes using potentiometers (simulating accelerometers).
	•	Sends motion data to Blynk for visualization.
	3.	Accident Detection:
	•	Detects potential accidents when accelerometer values exceed a predefined threshold.
	•	Turns on an LED indicator and notifies the Blynk platform about the accident.
	4.	Debugging Support:
	•	Outputs GPS and accelerometer data to a virtual terminal for debugging and testing purposes.

Hardware Requirements
	•	Arduino Uno
	•	GPS Module (VGPS)
	•	3 Potentiometers (to simulate X, Y, and Z axes of an accelerometer)
	•	LED (for accident indication)
	•	10k Resistors (optional, for potentiometer setup)
	•	USB Cable (for power and programming)
	•	Wires and Breadboard

Pin Layout

Component	Pin
X-axis Potentiometer	A0
Y-axis Potentiometer	A1
Z-axis Potentiometer	A2
GPS TX	3
GPS RX	4
LED	9
Debug RX	10
Debug TX	11

Software Requirements
	•	Arduino IDE
	•	Blynk Library: For IoT functionality.
	•	TinyGPS++ Library: For parsing GPS data.
	•	SoftwareSerial Library: For creating virtual serial ports.

Setup Instructions
	1.	Install Required Libraries:
	•	Open the Arduino IDE.
	•	Go to Sketch > Include Library > Manage Libraries.
	•	Search for and install:
	•	“Blynk”
	•	“TinyGPS++”
	•	“SoftwareSerial”
	2.	Hardware Connections:
	•	Connect the GPS module to pins 3 (RX) and 4 (TX).
	•	Connect the potentiometers to analog pins A0, A1, and A2.
	•	Connect the LED to pin 9 with a resistor.
	•	Connect the virtual terminal to pins 10 (RX) and 11 (TX).
	3.	Blynk Setup:
	•	Create a new project in the Blynk app.
	•	Add widgets:
	•	Label or Value Display for latitude (V0) and longitude (V1).
	•	Gauge or Graph for accelerometer data (V2, V3, V4).
	•	LED Widget for accident status (V5).
	•	Copy your Blynk Auth Token and paste it in the code.
	4.	Upload Code:
	•	Open the provided code in the Arduino IDE.
	•	Select the appropriate board (Arduino Uno) and port.
	•	Upload the code to the Arduino board.

Operation
	1.	Power the Arduino using a USB cable or external power source.
	2.	Open the Blynk app to view live GPS and accelerometer data.
	3.	Simulate motion by adjusting the potentiometers.
	4.	Trigger accident detection by exceeding the defined threshold (default: ±7.0) on any axis.
	5.	Monitor accident notifications on the Blynk app and LED indicator.

Testing
	•	GPS Testing:
	•	Verifies the GPS module is providing valid location data.
	•	Sends data to the debugging terminal and Blynk.
	•	Accelerometer Testing:
	•	Simulates accelerometer data using potentiometers.
	•	Sends data to the debugging terminal and Blynk.
	•	Accident Detection Testing:
	•	Exceeds the threshold values to test the accident detection logic.
	•	Confirms LED and Blynk notification behavior.

Troubleshooting
	1.	No GPS Data:
	•	Ensure the GPS module is connected correctly.
	•	Verify the baud rate matches the module’s specification (9600 in the code).
	2.	No Data on Blynk:
	•	Check the Blynk Auth Token.
	•	Ensure the device is connected to the correct serial port.
	3.	Accident Detection Not Triggering:
	•	Check the potentiometer connections.
	•	Ensure the accident threshold (7.0) is reasonable for your simulation.

Future Improvements
	•	Replace potentiometers with an actual accelerometer module (e.g., MPU6050).
	•	Add real-time notifications via SMS or email in case of accidents.
	•	Implement data logging to an SD card or cloud storage for post-incident analysis.
	•	Add battery-powered operation for portable use.

Acknowledgments

This project is part of the university IoT course project, supervised by Dr.Ehab Awad & Eng.Hussien , and demonstrates practical applications of IoT, GPS, and sensor data.
