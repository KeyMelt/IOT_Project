#!/usr/bin/env bash
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$ROOT"

if ! command -v clang-format >/dev/null 2>&1; then
  echo "clang-format is required for lint (install via apt or llvm)."
  exit 1
fi

npx prettier --check "**/*.{md,yml,yaml,json}"

find TrackerCode tests -type f \( -name '*.h' -o -name '*.cpp' \) -print0 |
  xargs -0 clang-format --dry-run --Werror
