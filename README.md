# Arduino Environmental Monitor (8-Bit Parallel Architecture)

## Overview
This repository contains the C++ logic and hardware mapping for an Arduino-based environmental monitoring system. It reads real-time temperature and humidity data via a DHT11/DHT22 sensor and displays it on a standard 16x2 character LCD.

To ensure fast, reliable data transmission and precise manual control over the hardware logic, the LCD is wired using a full **8-bit parallel data bus** rather than relying on an I2C backpack. 

## Live Simulation
[Wokwi Simulation Link](https://wokwi.com/projects/464816320305271809)

## Hardware Architecture

### Components
* Elegoo UNO R3 (Arduino-compatible)
* DHT11 (or DHT22) Digital Temperature & Humidity Sensor
* 16x2 Character LCD (HD44780 compatible)
* 10K Potentiometer (for hardware contrast control)

### Pin Mapping (8-Bit Parallel Logic)
The ATmega328P directly controls the LCD's instruction registers and data lines sequentially across Digital Pins 3 through 13.

| Component / Pin | Function | Arduino Pin |
| :--- | :--- | :--- |
| **DHT Sensor** | Data Line | D2 |
| **LCD RS** | Register Select | D3 |
| **LCD R/W** | Read / Write | D4 |
| **LCD E** | Enable | D5 |
| **LCD D0 - D7** | 8-Bit Data Bus | D6 - D13 |

## Code Structure
The system utilizes a non-blocking `millis()` timer loop. Instead of halting the ATmega328P with a standard `delay()` function, the microcontroller continuously evaluates the elapsed time. This architecture ensures the primary loop remains fully open for concurrent multitasking, polling additional sensors, and rapidly processing state flags triggered by hardware interrupts, all while maintaining a precise 2000ms screen refresh rate.
