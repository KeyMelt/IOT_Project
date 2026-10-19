# syntax=docker/dockerfile:1

# Builder: install toolchains and compile firmware.
FROM python:3.12-slim-bookworm AS builder

WORKDIR /project
COPY requirements.txt ./
RUN pip install --no-cache-dir -r requirements.txt

COPY platformio.ini ./
COPY TrackerCode ./TrackerCode

RUN cp TrackerCode/secrets.h.example TrackerCode/secrets.h \
    && pio pkg install -e uno \
    && pio run -e uno

# Runtime: minimal image with the compiled HEX artifact only.
FROM debian:bookworm-slim AS runtime

RUN apt-get update \
    && apt-get install -y --no-install-recommends ca-certificates \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /firmware
COPY --from=builder /project/.pio/build/uno/firmware.hex ./firmware.hex

LABEL org.opencontainers.image.title="asset-tracker-firmware"

CMD ["sh", "-c", "wc -c firmware.hex && echo 'Flash firmware.hex to Arduino Uno with avrdude or the Arduino IDE.'"]
