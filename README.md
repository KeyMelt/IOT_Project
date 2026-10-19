# Asset Tracker Project

[![CI](https://github.com/KeyMelt/IOT_Project/actions/workflows/ci.yml/badge.svg)](https://github.com/KeyMelt/IOT_Project/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/github/license/KeyMelt/IOT_Project)](LICENSE)
[![PlatformIO](https://img.shields.io/badge/build-PlatformIO-orange)](platformio.ini)

GPS-enabled IoT firmware for tracking asset location and motion, with accident detection from
accelerometer readings and remote monitoring via [Blynk](https://blynk.io/).

![Asset Tracker demo](https://github.com/user-attachments/assets/2cc0cdcd-4c62-4d64-8076-6f85302a5567)

## Quick start

```bash
# Clone and configure Blynk credentials
git clone https://github.com/KeyMelt/IOT_Project.git
cd IOT_Project
npm ci
cp TrackerCode/secrets.h.example TrackerCode/secrets.h
# Edit secrets.h with your Blynk template ID and auth token

npm test              # unit tests (no hardware)
npm run build:firmware # PlatformIO compile
# Or open TrackerCode/TrackerCode.ino in Arduino IDE and upload to Uno
```

Minimal wiring check in `setup()`:

```cpp
#include "secrets.h"
#include "accident_logic.h"
// GPS on pins 3/4, debug serial 10/11, LED on 9, pots on A0–A2
Blynk.config(Serial, auth);
```

See [CONTRIBUTING.md](CONTRIBUTING.md) for full setup, testing, and PR guidelines.

## Demo

- **Live monitoring**: Configure the [Blynk](https://blynk.io/) mobile app with virtual pins V0–V5
  (see [Setup Instructions](#setup-instructions)).
- **Video walkthrough**:
  [Project demo recording](https://github.com/user-attachments/assets/2cc0cdcd-4c62-4d64-8076-6f85302a5567)

## Overview

The **Asset Tracker** project is a GPS-enabled system for tracking the location and motion of assets
(e.g., vehicles or equipment). The system includes accident detection capabilities based on
accelerometer readings. The project is designed to work with the Blynk IoT platform for remote
monitoring and control, providing real-time data to users.

---

## Features

1. **GPS Tracking**:

   - Continuously captures and updates the latitude and longitude of the tracked asset.
   - Sends GPS data to the Blynk platform for remote monitoring.

2. **Accelerometer Monitoring**:

   - Tracks motion along the X, Y, and Z axes using potentiometers (simulating accelerometers).
   - Sends motion data to Blynk for visualization.

3. **Accident Detection**:

   - Detects potential accidents when accelerometer values exceed a predefined threshold.
   - Turns on an LED indicator and notifies the Blynk platform about the accident.

4. **Debugging Support**:
   - Outputs GPS and accelerometer data to a virtual terminal for debugging and testing purposes.

---

## Hardware Requirements

- **Arduino Uno**
- **GPS Module (VGPS)**
- **3 Potentiometers** (to simulate X, Y, and Z axes of an accelerometer)
- **LED** (for accident indication)
- **10k Resistors** (optional, for potentiometer setup)
- **USB Cable** (for power and programming)
- **Wires and Breadboard**

### Pin Layout

| Component                | Pin  |
| ------------------------ | ---- |
| **X-axis Potentiometer** | `A0` |
| **Y-axis Potentiometer** | `A1` |
| **Z-axis Potentiometer** | `A2` |
| **GPS TX**               | `3`  |
| **GPS RX**               | `4`  |
| **LED**                  | `9`  |
| **Debug RX**             | `10` |
| **Debug TX**             | `11` |

---

## Software Requirements

- **Arduino IDE** or **PlatformIO** (`platformio.ini` at repo root)
- **Blynk Library**: For IoT functionality.
- **TinyGPS++ Library**: For parsing GPS data.
- **SoftwareSerial Library**: For creating virtual serial ports (Arduino core).

Copy `TrackerCode/secrets.h.example` to `TrackerCode/secrets.h` (or see `.env.example` for variable
names). Never commit real tokens.

---

## Install and run

### Install dependencies

**Arduino IDE**: Install **Blynk** and **TinyGPS++** from Library Manager.

**PlatformIO** (from repo root):

```bash
cp TrackerCode/secrets.h.example TrackerCode/secrets.h
pio run -e uno
```

### Run on hardware

1. Connect the Arduino Uno and select the correct serial port.
2. Upload `TrackerCode/TrackerCode.ino` (IDE) or run `pio run -e uno -t upload`.
3. Power the board; open the Blynk app to view live data (see **Operation** below).

### Run tests (no hardware)

```bash
npm test
```

---

## Setup Instructions

1. **Install Required Libraries**:

   - Open the Arduino IDE.
   - Go to **Sketch** > **Include Library** > **Manage Libraries**.
   - Search for and install:
     - "Blynk"
     - "TinyGPS++"
     - "SoftwareSerial"

2. **Hardware Connections**:

   - Connect the GPS module to pins `3` (RX) and `4` (TX).
   - Connect the potentiometers to analog pins `A0`, `A1`, and `A2`.
   - Connect the LED to pin `9` with a resistor.
   - Connect the virtual terminal to pins `10` (RX) and `11` (TX).

3. **Blynk Setup**:

   - Create a new project in the Blynk app.
   - Add widgets:
     - **Label or Value Display** for latitude (V0) and longitude (V1).
     - **Gauge or Graph** for accelerometer data (V2, V3, V4).
     - **LED Widget** for accident status (V5).
   - Copy your **Blynk Auth Token** into `TrackerCode/secrets.h`.

4. **Upload Code**:
   - Open the provided code in the Arduino IDE.
   - Select the appropriate board (**Arduino Uno**) and port.
   - Upload the code to the Arduino board.

---

## Operation

1. Power the Arduino using a USB cable or external power source.
2. Open the Blynk app to view live GPS and accelerometer data.
3. Simulate motion by adjusting the potentiometers.
4. Trigger accident detection by exceeding the defined threshold (default: ±7.0) on any axis.
5. Monitor accident notifications on the Blynk app and LED indicator.

---

## Testing

- **GPS Testing**:
  - Verifies the GPS module is providing valid location data.
  - Sends data to the debugging terminal and Blynk.
- **Accelerometer Testing**:
  - Simulates accelerometer data using potentiometers.
  - Sends data to the debugging terminal and Blynk.
- **Accident Detection Testing**:
  - Exceeds the threshold values to test the accident detection logic.
  - Confirms LED and Blynk notification behavior.
- **Automated**: `tests/test_accident_logic.cpp` validates mapping and threshold logic in CI.

---

## Troubleshooting

1. **No GPS Data**:
   - Ensure the GPS module is connected correctly.
   - Verify the baud rate matches the module's specification (`9600` in the code).
2. **No Data on Blynk**:
   - Check the Blynk Auth Token in `secrets.h`.
   - Ensure the device is connected to the correct serial port.
3. **Accident Detection Not Triggering**:
   - Check the potentiometer connections.
   - Ensure the accident threshold (`7.0`) is reasonable for your simulation.

---

## Future Improvements

- Replace potentiometers with an actual accelerometer module (e.g., MPU6050).
- Add real-time notifications via SMS or email in case of accidents.
- Implement data logging to an SD card or cloud storage for post-incident analysis.
- Add battery-powered operation for portable use.

---

## License

MIT — see [LICENSE](LICENSE).

## Acknowledgments

This project is part of the university IoT course project, supervised by **Dr. Ehab Awad &
Eng.Hussein**, and demonstrates practical applications of IoT, GPS, and sensor data.
