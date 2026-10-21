# Arduino Uno R3 Overview & Servo Control

This project provides an overview of the Arduino Uno R3 (powered by the ATmega328P microcontroller) and demonstrates how to control a servo motor using a potentiometer. For complete technical specifications, refer to the [ATmega328P datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-Data-Sheet-DS40002061B.pdf).

## 1. ATmega328P Architecture and Features

### Core and Memory

- **CPU:** 8-bit AVR RISC-based processor.
- **Registers:** 32 general-purpose registers connected directly to the Arithmetic Logic Unit (ALU). Two registers can be accessed simultaneously, allowing execution of approximately 1 MIPS per MHz.
- **Flash memory:** In-system programmable flash memory capable of read-while-write operations.
- **SRAM:** Static random-access memory used for temporary data storage.

### Clock Management

- **Clock speed:** The ATmega328P supports a maximum clock speed of 20 MHz. The Arduino Uno R3 typically operates at 16 MHz.
- **Clock control unit:** Manages the clock signals for the CPU, I/O, flash memory, asynchronous timer, and ADC.
- **Prescaler:** Divides the system clock frequency to reduce the clock speed supplied to selected peripherals.

## 2. Timers and Pulse-Width Modulation

### Timers and Counters

The ATmega328P includes three timer/counters:

- Two 8-bit timers
- One 16-bit timer

Timers can count based on the system clock or an external signal. They can also be used to generate timing events and PWM signals.

### Pulse-Width Modulation

Pulse-width modulation (PWM) is a digital technique that rapidly switches a signal between HIGH and LOW states to control the average output or communicate timing information.

- **Pulse width:** The amount of time a signal remains HIGH.
- **Duty cycle:** The ratio of the HIGH pulse duration to the total signal period.

## 3. Potentiometer Servo Control

### Hardware Connections

| Component | Arduino connection |
|---|---|
| Potentiometer wiper | Analog pin `A0` |
| Servo control signal | Digital pin `D9` |
| Potentiometer power | `5V` |
| Potentiometer ground | `GND` |
| Servo power and ground | `5V` and `GND` |

### Signal Chain

1. The potentiometer produces a variable analog voltage.
2. The Arduino's analog-to-digital converter (ADC) converts the voltage into a 10-bit digital value from `0` to `1023`.
3. The digital value is mapped to a target servo angle from `0°` to `180°`.
4. The `Servo.h` library converts the angle into a corresponding pulse width.
5. The pulse is sent to the servo through digital pin `D9`.

### Servo Timing

The servo control signal is typically repeated every 20 ms, which corresponds to approximately 50 Hz. The servo primarily uses the duration of the HIGH pulse to determine its position:

| Pulse width | Approximate servo position |
|---:|---:|
| `1000 µs` | `0°` |
| `1500 µs` | `90°` |
| `2000 µs` | `180°` |

The exact pulse-width range may vary depending on the servo model.

### Control Relationship

```text
Potentiometer position
        ↓
ADC value from 0 to 1023
        ↓
Mapped servo angle from 0° to 180°
        ↓
Servo pulse width
        ↓
Servo arm position
```
