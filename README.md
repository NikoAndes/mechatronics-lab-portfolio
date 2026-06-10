# Mechatronics Lab Portfolio

![Badge](https://img.shields.io/badge/Platform-ESP32%20%7C%20Arduino-00979D?style=flat-square&logo=arduino)
![Badge](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=flat-square&logo=c%2B%2B)
![Badge](https://img.shields.io/badge/License-MIT-green?style=flat-square)
![Badge](https://img.shields.io/badge/Status-Active-brightgreen?style=flat-square)

Personal laboratory portfolio documenting embedded systems, electronics and automation projects built with ESP32 and Arduino as part of my Mechatronics Engineering studies.

## Overview

This repository serves as a technical lab notebook. Each project folder contains source code, wiring diagrams, and documentation. Projects range from sensor systems and finite state machines to motor control and signal simulation.

Built by: **Nicolas Isaza Sierra** | Mechatronics Engineering Student | UMNG Colombia

## Projects

| # | Project | Description | Status |
|---|---|---|---|
| 1 | [ESP32 Bowling System](./projects/esp32-bowling-system/) | Detect fallen bowling pins with LDR sensors and score tracking | Complete |
| 2 | [Coffee Machine FSM](./projects/coffee-machine-fsm/) | Finite state machine simulating a coffee maker | Complete |
| 3 | [FitzHugh-Nagumo Neuron Simulator](./projects/fitzhugh-nagumo-neuron-simulator/) | Neuron firing simulation with digital/analog signals | Complete |
| 4 | [L298N Motor Control](./projects/l298n-motor-control/) | DC motor control with ESP32 and L298N H-bridge | Complete |

## Skills Demonstrated

- Embedded C++ programming for ESP32 and Arduino
- Finite State Machine (FSM) design and implementation
- Analog and digital sensor reading (LDR, touch, buttons)
- PWM signal generation for motor and LED control
- Serial communication for debugging and output
- Modular code structure and documentation

## Repository Structure

```txt
mechatronics-lab-portfolio/
├── README.md
├── LICENSE
├── .gitignore
│
├── projects/
│   ├── esp32-bowling-system/
│   ├── coffee-machine-fsm/
│   ├── fitzhugh-nagumo-neuron-simulator/
│   └── l298n-motor-control/
│
└── assets/
    └── images/
```

## How to Run

1. Install [Arduino IDE](https://www.arduino.cc/en/software) or use PlatformIO
2. Install ESP32 board support package
3. Open the `.ino` file inside the desired project's `code/` folder
4. Select board: `ESP32 Dev Module`
5. Upload to your device or use Serial Monitor to simulate

## Screenshots

> Screenshots and wiring photos will be added for each project. See each project's folder for diagram placeholders.

## What I Learned

- How to design and implement FSMs in embedded systems
- Reading analog sensor values and applying thresholds
- Controlling DC motors with PWM and H-bridge drivers
- Structuring embedded projects for readability and reuse
- Documenting hardware projects clearly

## Future Improvements

- [ ] Add real hardware photos for each project
- [ ] Implement MQTT or WiFi connectivity in selected projects
- [ ] Add display output (OLED/LCD) to bowling and coffee projects
- [ ] Create KiCad schematics for each circuit
- [ ] Add PlatformIO config files

## Author

**Nicolas Isaza Sierra**
GitHub: [NikoAndes](https://github.com/NikoAndes)

## License

MIT License
