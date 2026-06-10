# ESP32 Bowling System

![Platform](https://img.shields.io/badge/Platform-ESP32-red) ![Language](https://img.shields.io/badge/Language-C%2B%2B-blue) ![License](https://img.shields.io/badge/License-MIT-blue)

An electronic bowling pin detection system using 10 LDR sensors connected to an ESP32. Detects knocked pins, counts them, and reports results via Serial.

## Overview

Each bowling pin is mapped to an LDR sensor. When a pin is knocked down, the sensor reading changes and crosses a configurable threshold, triggering detection.

## Features

- 10 LDR sensors (one per pin)
- Configurable detection threshold
- Pin state reading every 2 seconds
- Serial output with knocked pin count
- Prepared for OLED/LCD display expansion

## Tech Stack

- ESP32 / Arduino IDE
- C++
- LDR sensors (analog)

## Pin Assignments

```cpp
const int sensorPins[10] = {36, 39, 34, 35, 32, 33, 25, 26, 27, 14};
```

## How to Run

1. Open `code/esp32_bowling_system.ino` in Arduino IDE
2. Select board: `ESP32 Dev Module`
3. Upload and open Serial Monitor at `115200 baud`

## What I Learned

- Analog sensor reading on ESP32 ADC pins
- Threshold-based detection logic
- Mapping hardware state to software

## Future Improvements

- OLED score display
- Full bowling scoring rules (strikes, spares)
- Reset button for new frame

## Author

**Nicolas Isaza Sierra** | [@NikoAndes](https://github.com/NikoAndes)
