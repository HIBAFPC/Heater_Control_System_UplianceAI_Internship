# Embedded Systems Intern Assignment: Basic Heater Control System

**Applicant Name:** [Your Full Name]  
**Date:** July 19, 2025  

This repository contains the design and implementation of a basic heater control system for the upliance.ai Embedded Systems Intern Assignment. It includes temperature threshold monitoring, heater simulation, overheating protection, visual/audio indicators, and BLE simulation.

## 📁 Project Structure
- `sketch.ino`: Main Arduino C++ code for ESP32
- `README.md`: Detailed explanation of the project, design, wiring, features, and how to simulate in Wokwi

## ✅ Features
- State-based heater control logic
- Red LED for heating simulation
- Green LED for status indication
- Buzzer alarm for overheat
- LM35 analog temperature sensor support
- Non-blocking timing using `millis()`
- BLE simulated via Serial logs

## 🚀 How to Simulate in Wokwi
1. Go to https://wokwi.com/
2. Start a new ESP32 Arduino project
3. Add components:
   - ESP32 Dev Module
   - LM35 sensor (OUT to GPIO34)
   - Red LED (GPIO17)
   - Green LED (GPIO16)
   - Buzzer (GPIO18)
4. Paste the code from `sketch.ino` into the project
5. Run simulation and observe serial output
