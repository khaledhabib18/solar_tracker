# Solar Tracker System with Stepper Motors, LDRs, L298N Motor Drivers, and Limit Switches

## Overview
This project implements a solar tracker system using stepper motors to adjust the position of a solar panel. The system ensures optimal solar energy capture by dynamically orienting the panel based on light intensity detected by Light Dependent Resistors (LDRs). The project employs L298N motor drivers to control the stepper motors and limit switches to prevent the motors from exceeding their physical boundaries.

## Features
- Real-time tracking of sunlight using LDRs.
- Dual-axis movement: horizontal (azimuth) and vertical (tilt).
- Stepper motors controlled via L298N motor drivers.
- Limit switches to protect the system from over-rotation or over-tilting.
- Adjustable sensitivity and delay settings for fine-tuned operation.

## Components
### Hardware
1. **L298N Motor Driver Modules**
2. **Stepper Motors**
3. **Light Dependent Resistors (LDRs)**
4. **Limit Switches**
5. **Arduino Board**
6. **Solar Panel (optional for full implementation)**
7. **Miscellaneous**: Breadboard, jumper wires, resistors, and a power source.

### Software
1. Arduino IDE

## Pin Configuration
### Motor Driver Pins
#### Horizontal Motor
- **IN1_H**: Pin 9  
- **IN2_H**: Pin 10
- **IN3_H**: Pin 11
- **IN4_H**: Pin 12

#### Vertical Motor
- **IN1_V**: Pin 3
- **IN2_V**: Pin 4
- **IN3_V**: Pin 5
- **IN4_V**: Pin 6

### LDR Pins
- **Top Left (LDR_TOP_LEFT)**: A0
- **Top Right (LDR_TOP_RIGHT)**: A3
- **Bottom Left (LDR_BOTTOM_LEFT)**: A1
- **Bottom Right (LDR_BOTTOM_RIGHT)**: A2

### Limit Switch Pins
- **Top**: Pin 7
- **Bottom**: Pin 8
- **Left**: Pin 13
- **Right**: Pin 2

## Arduino Code Structure
### Key Components
1. **Pin Definitions**: All hardware pins are defined at the top of the code.
2. **Stepper Motor Sequences**: A 2D array controls the stepper motor phases.
3. **LDR Readings**: Analog values from LDRs determine the position of the sun.
4. **Movement Logic**:
   - Calculates the difference in light intensity.
   - Adjusts motor direction based on LDR readings.
5. **Limit Switch Logic**: Prevents motors from moving beyond their physical limits.

### Functions
- **`setup()`**: Initializes motor driver pins, limit switches, and serial communication.
- **`loop()`**: Continuously reads LDR values, calculates differences, and adjusts motor positions.
- **`moveMotor()`**: Executes stepper motor movements based on direction and steps.

## How to Use
1. **Wiring**:
   - Connect the hardware components as per the pin configuration.
   - Ensure the LDRs are positioned on the four corners of the solar panel.
2. **Upload Code**:
   - Open the Arduino IDE and load the provided code.
   - Upload the code to the Arduino board.
3. **Power the System**:
   - Provide sufficient power to the stepper motors and motor drivers.
4. **Testing**:
   - Observe the panel's movement as it adjusts to varying light intensities.

## Adjustable Settings
- **`tolerance`**: Sets the sensitivity to light intensity differences.
- **`delayTime`**: Determines the delay between motor steps for smooth motion.

## Future Enhancements
- Add real-time data logging for solar panel positions.
- Integrate with IoT platforms for remote monitoring and control.
- Use a more advanced control algorithm, such as PID, for smoother tracking.
- Incorporate a battery management system to utilize captured solar energy efficiently.

## Contributing
Feel free to contribute to this project by submitting pull requests or reporting issues.

## License
This project is licensed under the MIT License. See the `LICENSE` file for details.

---
### Contact
For any queries or suggestions, please reach out through the GitHub issues section.
