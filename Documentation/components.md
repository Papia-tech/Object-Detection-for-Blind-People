# Hardware Components

This document contains the hardware components used in the Assistive Obstacle Detection System.

## 1. Main Components

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Uno | 1 | Main microcontroller that processes sensor inputs |
| IR Obstacle Detection Sensor | 2 | Detects nearby obstacles |
| Touch Sensor | 1 | Provides touch-based input to control the system |
| Buzzer | 1 | Provides audio alerts when obstacles are detected |
| Jumper Wires | As required | Connects the electronic components |
| Power Supply | 1 | Provides power to the system |

## 2. Component Description

### Arduino Uno
The Arduino Uno acts as the central processing unit of the system. It receives signals from the sensors and controls the alert mechanism.

### IR Obstacle Detection Sensors
IR sensors detect obstacles within their sensing range. They send digital signals to the Arduino when an obstacle is detected.

### Touch Sensor
The touch sensor allows the user to interact with the system through touch. It can be used to activate or control the obstacle detection functionality.

### Buzzer
The buzzer provides audio alerts to notify the user when an obstacle is detected.

### Jumper Wires
Jumper wires establish electrical connections between the Arduino and other components.

### Power Supply
The power supply provides the required electrical power for the circuit.

## 3. Component Connections

| Component | Arduino Pin |
|---|---|
| Left IR Sensor OUT | D2 |
| Right IR Sensor OUT | D4 |
| Touch Sensor OUT | Verify actual connection |
| Buzzer Positive (+) | D8 |
| Sensor VCC | 5V |
| Sensor GND | GND |
| Buzzer Negative (-) | GND |

*Note: Update the touch sensor pin according to your actual circuit wiring.*

## 4. Working Principle

1. The IR sensors continuously monitor the surroundings.
2. The touch sensor provides an input to activate or control the system.
3. When an obstacle enters the detection range, the corresponding IR sensor sends a signal to the Arduino.
4. The Arduino processes the received signals.
5. The buzzer generates an audio alert to notify the user.

---

**Project:** Assistive Obstacle Detection System  
**Category:** Arduino / Embedded Systems / Assistive Technology