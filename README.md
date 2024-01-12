# bluesense-iot

## Overview

This repository contains the source code for the BlueSense IoT device. The device is designed for water quality monitoring and utilizes ESP32, pH sensor, and TDS sensor. The device follows two main data flow processes for monitoring and logging water quality:

1. **Periodic Data Logging:**
   - Every 10 minutes, the device sends data to a REST server for logging and history purposes.
2. **Real-Time Monitoring:**
   - The device sends data to an MQTT broker whenever there is a change in the monitored parameters for real-time monitoring.

## Hardware Components

- ESP32 microcontroller
- pH sensor
- TDS (Total Dissolved Solids) sensor

## Wiring Diagram

![Bluesense IOT Device Diagram](./diagram/bluesense_iot_diagram.png)
