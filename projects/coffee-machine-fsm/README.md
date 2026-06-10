# Coffee Machine FSM

![Platform](https://img.shields.io/badge/Platform-ESP32%2FArduino-red) ![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

A Finite State Machine (FSM) simulation of a coffee dispenser controlled via Serial commands.

## States

`IDLE` -> `SELECTING` -> `CHECK_SUPPLIES` -> `SERVING_COFFEE` -> `SERVING_WATER` -> `FINISHED` / `ERROR_STATE`

## Features

- 7-state FSM implementation
- Serial command interface
- Supply validation before serving
- Error state with recovery
- State transition logging

## Tech Stack

- ESP32 / Arduino IDE
- C++
- Serial communication

## How to Run

1. Open `code/coffee_machine_fsm.ino` in Arduino IDE
2. Upload to ESP32 or Arduino Uno
3. Open Serial Monitor at `9600 baud`
4. Enter option number to select beverage

## What I Learned

- FSM design patterns in embedded C++
- State-based control flow
- Defensive programming with error states

## Future Improvements

- Physical buttons instead of Serial input
- LCD display for state feedback
- Real supply sensors

## Author

**Nicolas Isaza Sierra** | [@NikoAndes](https://github.com/NikoAndes)
