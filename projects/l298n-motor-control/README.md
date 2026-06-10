# L298N Motor Control

![Platform](https://img.shields.io/badge/Platform-ESP32-red) ![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

DC motor control using the L298N H-Bridge driver and ESP32. Supports forward, backward, stop and PWM speed control via Serial.

## Features

- `f` command: forward rotation
- `b` command: backward rotation
- `s` command: stop
- PWM speed control via ENA pin
- Serial command interface

## Hardware Connections

```
GPIO 26 -> IN1
GPIO 25 -> IN2
GPIO 27 -> ENA (PWM)
```

## How to Run

1. Wire motor + L298N to ESP32
2. Open `code/l298n_motor_control.ino` in Arduino IDE
3. Upload to ESP32
4. Open Serial Monitor at `9600 baud`
5. Type `f`, `b`, or `s`

## What I Learned

- H-Bridge operation principles
- PWM speed control on ESP32
- Serial command parsing for hardware

## Future Improvements

- Encoder feedback
- PID speed controller
- Multiple motors

## Author

**Nicolas Isaza Sierra** | [@NikoAndes](https://github.com/NikoAndes)
