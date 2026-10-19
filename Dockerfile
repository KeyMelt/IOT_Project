# Reproducible firmware build environment for Asset Tracker.
FROM python:3.12-slim-bookworm

RUN pip install --no-cache-dir platformio==6.1.18

WORKDIR /project
COPY platformio.ini ./
COPY TrackerCode ./TrackerCode

RUN cp TrackerCode/secrets.h.example TrackerCode/secrets.h && pio pkg install -e uno

CMD ["pio", "run", "-e", "uno"]
