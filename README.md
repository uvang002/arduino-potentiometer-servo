# Arduino Uno R3 Overview & PWM Output

This project provides an overview of the Arduino Uno R3 (powered by the ATmega328P microcontroller) and demonstrates ordinary analog-output PWM control from a potentiometer. For complete technical specifications, refer to the [ATmega328P datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-Data-Sheet-DS40002061B.pdf).

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

## 3. Potentiometer-Controlled PWM Output (`analogWrite`)

### Hardware Connections

| Component | Arduino connection |
|---|---|
| Potentiometer wiper | Analog pin `A0` |
| PWM output signal | Digital pin `D9` (PWM-capable) |
| Potentiometer power | `5V` |
| Potentiometer ground | `GND` |

### Signal Chain

1. The potentiometer produces a variable analog voltage.
2. The Arduino's analog-to-digital converter (ADC) converts the voltage into a 10-bit digital value from `0` to `1023`.
3. The ADC value is mapped to an 8-bit PWM duty value from `0` to `255`.
4. `analogWrite()` outputs that duty value on digital pin `D9` as ordinary PWM.

### PWM Timing on `D9`

On the Arduino Uno, `analogWrite()` on `D9` uses a PWM carrier frequency of approximately `490 Hz`. The duty value sets how long each cycle remains HIGH:

| PWM value | Approximate duty cycle |
|---:|---:|
| `0` | `0%` |
| `128` | `50%` |
| `255` | `100%` |

### Ordinary PWM vs. Servo Control Pulses

`analogWrite()` is ordinary PWM and does **not** directly command a hobby servo position. A servo expects a repeated control pulse (typically around 50 Hz) where the HIGH-time width encodes the target angle (for example, about `1000 µs` to `2000 µs`).

In this repository, pin `D9` is used as a general PWM output pin, not as a servo-control pulse output.

### Control Relationship

```text
Potentiometer position
        ↓
ADC value from 0 to 1023
        ↓
Mapped PWM duty from 0 to 255
        ↓
PWM output on D9 (~490 Hz)
        ↓
Average output level
```
