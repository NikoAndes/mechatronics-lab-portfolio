# FitzHugh-Nagumo Neuron Simulator

![Platform](https://img.shields.io/badge/Platform-ESP32-red) ![Language](https://img.shields.io/badge/Language-C%2B%2B-blue)

An educational simulation of neuron excitability using ESP32 LEDs and buttons, inspired by the FitzHugh-Nagumo model.

## Overview

The FitzHugh-Nagumo model captures the essential behavior of excitable systems like neurons. This is an educational hardware approximation demonstrating neural firing, propagation and recovery using LEDs on ESP32.

## States

`RESTING` -> `FIRING` -> `PROPAGATING` -> `RECOVERY` -> `RESTING`

## Features

- 2-neuron simulation (LED1 and LED2)
- Button/touch stimulus trigger
- Propagation delay between neurons
- Serial state logging
- Refractory period simulation

## Tech Stack

- ESP32 / Arduino IDE
- C++ / Digital I/O

## How to Run

1. Open `code/neuron_simulator.ino` in Arduino IDE
2. Upload to ESP32
3. Press trigger button and observe LEDs + Serial output

## Note

This is an educational approximation. It does not implement the actual FitzHugh-Nagumo differential equations.

## Author

**Nicolas Isaza Sierra** | [@NikoAndes](https://github.com/NikoAndes)
