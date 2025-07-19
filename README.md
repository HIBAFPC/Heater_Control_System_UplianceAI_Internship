 Embedded Systems Intern Assignment: Basic Heater Control System


 Hiba Fathima P C

July 19, 2025

1. Project Overview
This repository contains the design and implementation of a basic heater control system, developed as part of the upliance.ai Embedded Systems Intern Assignment. The system aims to simulate a temperature-based control mechanism that turns a "heater" on or off based on predefined temperature thresholds, ensuring a target temperature is maintained while also incorporating overheating protection.

2. Part 1: System Design
2.1. Minimum Sensors Required
The primary and minimum sensor required for this heater control system is a temperature sensor.

An LM35 Temperature Sensor is chosen for its linear output (10mV per degree Celsius), ease of use, and direct analog output, which simplifies interfacing with the microcontroller's Analog-to-Digital Converter (ADC).

2.2. Communication Protocol Recommendation and Justification
For communication between the temperature sensor and the microcontroller, the I2C (Inter-Integrated Circuit) protocol is recommended.

Justification:

Simplicity: I2C requires only two wires for data transfer (SDA - Serial Data Line and SCL - Serial Clock Line), reducing wiring complexity compared to parallel interfaces.

Multi-device Support: It supports multiple slave devices on the same bus, which is beneficial for future expansion (e.g., adding more sensors) without requiring additional microcontroller pins.

Sufficiency for Application: For temperature sensing, the data rate offered by I2C is more than adequate, as temperature readings do not require high-speed, real-time data streaming.

Standardization: I2C is a widely adopted standard, meaning many sensors and peripherals are available with I2C interfaces, simplifying component selection.

2.3. Block Diagram
+---------------------+           +---------------------+           +---------------------+
|                     |           |                     |           |                     |
|  Temperature Sensor |<--------->|    Microcontroller  |<--------->|   Actuating Circuit |
|       (LM35)        |  (I2C/SPI)  |     (ESP32 Dev      |  (GPIO)   |   (Simulated Heater |
|                     |           |       Module)       |           |        - Red LED)   |
+---------------------+           +---------------------+           +---------------------+
           ^                                |
           |                                |
           |                                v
           |                         +----------------+
           |                         |                |
           +------------------------>|    Power Supply|
                                     |                |
                                     +----------------+

Optional Modules (Implemented for Bonus Features):

+---------------------+
|                     |
|    Serial Monitor   | <---------- (UART)
|  (Logging/Debugging)|
+---------------------+

+---------------------+
|                     |
|    Buzzer/LED       | <---------- (GPIO)
|  (Visual/Audio FB)  |
+---------------------+

Module Descriptions:

Temperature Sensor (LM35): Measures the current temperature.

Microcontroller (ESP32 Dev Module): The central processing unit. It reads temperature data, executes the control logic, and manages the output to the heater and indicators. ESP32 is chosen for its robust capabilities and built-in Wi-Fi/BLE for potential future enhancements.

Actuating Circuit (Simulated Heater - Red LED): Represents the heating element. A Red LED is used in the simulation to visually indicate when the heater is "ON." In a real system, this would typically involve a relay controlling a heating element.

Power Supply: Provides the necessary electrical power to all components.

Serial Monitor: Used for debugging and logging temperature readings and system states in real-time.

Buzzer/LED (Bonus): A buzzer provides an audible alarm for critical events (e.g., overheating), and a Green LED indicates the system's "Idle" or "Target Reached" state.

2.4. Future Roadmap
The system can evolve to support more advanced functionalities:

Overheating Protection Enhancements:

Redundant Sensing: Integrate a second, independent temperature sensor. If readings from both sensors diverge significantly or both exceed a critical threshold, the system can trigger an immediate shutdown and alarm, providing a fail-safe mechanism.

Hardware Cutoff: Implement a hardware-based thermal fuse or bimetallic switch that physically interrupts power to the heating element if a dangerous temperature is reached, acting as a last line of defense independent of software.

Intelligent Shutdown: Introduce a "cool-down" phase after an overheat event, where the system prevents the heater from turning back on until the temperature has dropped to a safe, pre-defined level, and potentially requires a manual reset.

Multiple Heating Profiles:

User Interface (UI): Develop a simple UI using an LCD display and push buttons, or a mobile application (via Wi-Fi/BLE), allowing users to select different pre-defined heating profiles (e.g., "Boil," "Simmer," "Warm," "Custom").

Profile Storage: Store multiple sets of temperature thresholds (e.g., target, heating, stabilizing ranges) in the microcontroller's non-volatile memory (e.g., EEPROM or Flash) that can be loaded based on the selected profile.

Time-Based Scheduling: Incorporate a Real-Time Clock (RTC) module to enable scheduled heating operations (e.g., "heat to 50°C at 7 AM").

PID Control: Transition from simple ON/OFF control to a Proportional-Integral-Derivative (PID) control algorithm for more precise temperature regulation, minimizing overshoot and maintaining temperature within a tighter range. This would involve continuous adjustment of heater power rather than just on/off.

Adaptive Learning: Implement basic machine learning techniques to analyze usage patterns and environmental factors, allowing the system to adapt and optimize heating cycles for better efficiency and user experience.

3. Part 2: Embedded Implementation
3.1. Platform and Language
Platform: Wokwi (Online ESP32/Arduino Simulator)

Language: C/C++ (Arduino Framework for ESP32)

3.2. Requirements Implemented
The provided sketch.ino implements the following core requirements:

Temperature-Based State Tracker: A finite state machine is implemented with the following states:

IDLE: Heater is off, temperature is below the HEATING_THRESHOLD.

HEATING: Temperature is below TARGET_TEMPERATURE, heater is active.

STABILIZING: Temperature has reached or slightly exceeded TARGET_TEMPERATURE, heater is off, allowing for thermal inertia.

TARGET_REACHED: Temperature is within the desired STABILIZE_LOWER and STABILIZE_UPPER range, heater is off.

OVERHEAT: Temperature has exceeded OVERHEAT_THRESHOLD, heater is forced off, and an alarm is triggered.

Continuous Temperature Reading: The LM35 sensor is read periodically (every 2 seconds) using a non-blocking millis() based approach.

Heater Control: A Red LED (simulating the heater) is turned ON or OFF based on the current state and temperature thresholds.

Serial Logging: Temperature readings, current system state, and heater status are continuously logged to the Serial Monitor for real-time monitoring and debugging.

3.3. Bonus Features Implemented
Buzzer/LED Indicator for Visual/Audio Feedback:

A Green LED (STATUS_LED_PIN) illuminates when the system is in IDLE or TARGET_REACHED states, indicating a safe and stable condition.

A buzzer (BUZZER_PIN) emits an alarm sound for 1 second when the system enters the OVERHEAT state.

3.4. How to Run the Simulation (Wokwi)
Open Wokwi: Go to https://www.wokwi.com/ and start a new ESP32 Arduino project.

Add Components:

ESP32 Dev Module

LM35 Temperature Sensor

LED (Red) - for Heater

LED (Green) - for Status

Buzzer (Active Buzzer recommended for simplicity with the current code)

Resistor (220 Ohm) x2 (for LEDs)

Breadboard

Wire Components:

LM35: Vout to ESP32 GPIO34 (ADC input), Vs to 3.3V, GND to GND.

Heater LED (Red): Anode to ESP32 GPIO17, Cathode via 220 Ohm resistor to GND.

Status LED (Green): Anode to ESP32 GPIO16, Cathode via 220 Ohm resistor to GND.

Buzzer: Positive (+) to ESP32 GPIO18, Negative (-) to GND.

Upload Code: Copy the content of sketch.ino from this repository and paste it into the sketch.ino tab in your Wokwi project.

Run Simulation: Click the "Run" button in Wokwi.

Monitor: Open the Serial Monitor in Wokwi to observe temperature readings and state changes. You can adjust the LM35 slider in the simulation to change the temperature and trigger different states.

4. Code Structure (sketch.ino)
The code is structured with clear pin definitions, temperature thresholds, and an enum for the state machine. The setup() function initializes pins and serial communication. The loop() function continuously reads temperature, implements the state machine logic, and controls outputs. Non-blocking millis() is used for periodic operations
