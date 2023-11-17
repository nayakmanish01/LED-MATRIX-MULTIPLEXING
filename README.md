# LED MATRIX MULTIPLEXING PROJECT

## Overview

This project demonstrates LED matrix multiplexing using the 74HC595 shift register with an 8x8 LED matrix and Atmega32 microcontroller. The simulation is designed using Proteus, and the firmware is developed using Atmel Studio. This Repository contains code files and schematic files of all intermediate steps as well .

## Components Used

- Atmega32 Microcontroller
- 74HC595 Shift Register
- 8x8 LED Matrix
- Proteus Simulation Environment
- Atmel Studio for Firmware Development

## Project Description

The project showcases the technique of LED matrix multiplexing to control an 8x8 LED matrix efficiently. The 74HC595 shift register is used to reduce the number of pins required to drive the LED matrix, providing a more organized and manageable solution.

## How It Works

The Atmega32 microcontroller communicates with the 74HC595 shift register using SPI (Serial Peripheral Interface) to control the LED matrix. The microcontroller sends data serially to the shift register, which then outputs the data in parallel to the LED matrix. This multiplexing technique allows us to control individual LEDs in the matrix while using a minimal number of microcontroller pins.

## Proteus Simulation

The Proteus simulation file (provided in the 'Proteus_Simulation' directory) allows you to visualize the LED matrix multiplexing in action. It includes the Atmega32 microcontroller, 74HC595 shift register, and the 8x8 LED matrix. Connect the components as per the schematic in the 'Documentation' folder.

## Atmel Studio Firmware

The 'Firmware' directory contains the Atmel Studio project for the Atmega32 microcontroller. The C code configures the microcontroller and implements the logic for LED matrix multiplexing. Repository contains code for all the intermediate steps in between for easy understanding and implementation.

## How to Use

1. Open the Proteus simulation file in Proteus.
2. Load the Atmel Studio project and program the Atmega32 microcontroller.
3. Connect the virtual terminal in Proteus to see the output.

## Schematic

Refer to the schematic diagram in the Documentation for proper wiring of components.
