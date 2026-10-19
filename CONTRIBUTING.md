# Contributing to Asset Tracker

Thank you for your interest in improving this project. This repository is an Arduino Uno firmware plus Proteus schematics for a GPS and motion-tracking IoT asset tracker.

## Development setup

### Option A — Arduino IDE (recommended for hardware upload)

1. Install [Arduino IDE](https://www.arduino.cc/en/software) 2.x or later.
2. Install libraries via **Library Manager**:
   - Blynk
   - TinyGPS++
3. Copy `TrackerCode/secrets.h.example` to `TrackerCode/secrets.h` and add your Blynk template ID and auth token (see `.env.example` for variable names).
4. Open `TrackerCode/TrackerCode.ino`, select board **Arduino Uno**, and upload.

### Option B — PlatformIO (recommended for CI-parity builds)

1. Install [PlatformIO](https://platformio.org/) (VS Code extension or CLI).
2. `cp TrackerCode/secrets.h.example TrackerCode/secrets.h` and fill in credentials.
3. From the repo root: `pio run -e uno`

### Docker

```bash
docker build -t asset-tracker .
docker run --rm asset-tracker
```

## Code style

- C/C++ in `TrackerCode/` follows `.clang-format` (LLVM-based, 4-space indent).
- Run `clang-format -i TrackerCode/*.h` before committing if you change headers.

## Testing

Host-side unit tests cover accident-detection logic (no hardware required):

```bash
g++ -std=c++17 -Wall -Wextra -I TrackerCode tests/test_accident_logic.cpp -o test_runner
./test_runner
```

CI runs the same tests and compiles the firmware on every push and pull request.

## Pull requests

1. Fork the repo and create a branch from `main`.
2. Keep changes focused; update `README.md` if behavior or setup changes.
3. Ensure CI passes (tests + firmware compile).
4. Open a pull request using the template and describe how you tested (simulation, hardware, or unit tests).

## Reporting issues

Use the GitHub issue templates for bugs and feature requests. Do **not** include Blynk auth tokens or other secrets in issues or PRs.

## Security

See [SECURITY.md](SECURITY.md) for vulnerability reporting.
