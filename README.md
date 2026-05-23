# Atmel-I2C-Monitor: Asynchronous Sensor Node
An embedded environmental monitoring node for Atmel microcontrollers, featuring SRAM-optimized data routing and an I2C hardware bus display.

## System Overview
An embedded environmental monitoring node built for Atmel microcontrollers and verified in the Wokwi virtual simulator. The system polls ambient temperature and humidity from a DHT22 sensor and dispatches real-time updates over an I2C hardware bus to a 16x2 LCD display.

**Live Virtual Simulation:** [Wokwi Simulation Link](https://wokwi.com/projects/464816320305271809)

## Technical Features
* **Asynchronous Execution:** Utilized a non-blocking `millis()` hardware clock engine instead of blocking `delay()` calls, ensuring continuous system uptime without halting the microcontroller's execution loop.
* **SRAM Optimization:** Utilized the `F()` compiler macro to push static literal strings directly into Flash memory, protecting the ATmega328P's strict 2KB SRAM limit from stack-heap collisions.

## Simulation Pin Mapping

| Component | Pin | MCU Pin | Function |
| :--- | :--- | :--- | :--- |
| **DHT22 Sensor** | DATA | Digital Pin 2 | Single-Wire Serial |
| **LCD Display** | SDA | Analog Pin 4 (A4) | I2C Serial Data |
| **LCD Display** | SCL | Analog Pin 5 (A5) | I2C Serial Clock |

*(Note: VCC and GND for both components are routed to the shared 5V and GND Arduino rails).*

---
*Status: Asynchronous prototype fully verified in Wokwi Simulator. Physical hardware deployment pending.*
