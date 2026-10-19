#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

if [[ ! -f TrackerCode/secrets.h ]]; then
  cp TrackerCode/secrets.h.example TrackerCode/secrets.h
fi

if command -v pio >/dev/null 2>&1; then
  pio run -e uno
else
  python3 -m platformio run -e uno
fi
