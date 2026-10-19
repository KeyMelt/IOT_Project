#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

g++ -std=c++17 -Wall -Wextra -I TrackerCode tests/test_accident_logic.cpp -o /tmp/asset-tracker-test
/tmp/asset-tracker-test
