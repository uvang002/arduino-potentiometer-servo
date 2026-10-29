# Arduino Uno R3 Potentiometer Servo Control

This project provides an overview of the Arduino Uno R3 (powered by the ATmega328P microcontroller) and demonstrates how to control a servo motor using a potentiometer. For complete technical specifications, refer to the [ATmega328P datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-Data-Sheet-DS40002061B.pdf).

## Digital Logic Connection

This project applies digital logic and basic embedded-systems concepts to a physical control system. The potentiometer produces an analog voltage, which the ADC converts into a 10-bit digital value. The program maps this digital value to a servo angle, and the `Servo.h` library generates the corresponding pulse-width signal that controls the servo arm's position.

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

### Testing Servo PWM with a Logic Analyzer

A logic analyzer can be used to observe the PWM signal sent to the servo.

1. Connect logic analyzer channel `CH0` to Arduino digital pin `D9`.
2. Connect the logic analyzer ground to Arduino `GND`.
3. Set the sample rate to **100 kHz**.
4. Set the capture duration to **1 second**, resulting in **100,000 samples**.
5. Start the recording.
6. Turn the potentiometer and observe the PWM signal on `CH0`.

The signal should repeat approximately every 20 ms, or 50 Hz. The pulse width should change as the potentiometer is rotated:

| Pulse width | Approximate servo position |
|---:|---:|
| `1000 µs` | `0°` |
| `1500 µs` | `90°` |
| `2000 µs` | `180°` |

The exact pulse-width range may vary depending on the servo model and the `Servo.h` library configuration.

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

## 4. How to Use

### Required Components

- Arduino Uno R3
- Standard hobby servo motor
- 10 kΩ potentiometer
- Breadboard and jumper wires
- USB cable

### Wiring

| Component | Arduino connection |
|---|---|
| Potentiometer left pin | `5V` |
| Potentiometer middle pin | `A0` |
| Potentiometer right pin | `GND` |
| Servo signal wire | Digital pin `D9` |
| Servo power wire | `5V` |
| Servo ground wire | `GND` |

The potentiometer's outer pins may be connected to `5V` and `GND` in either order. Reversing them changes the direction in which the servo moves.

### Upload the Program

1. Open `potentiometer_servo.ino` in the Arduino IDE.
2. Connect the Arduino Uno R3 to your computer with a USB cable.
3. Select **Tools → Board → Arduino Uno**.
4. Select the correct port under **Tools → Port**.
5. Verify that the Servo library is available. It is included with the Arduino IDE.
6. Click **Upload**.
7. Turn the potentiometer after the upload completes. The servo arm should move between approximately `0°` and `180°`.

### Monitor ADC and Servo Values

To view the potentiometer reading and calculated servo angle:

1. Open **Tools → Serial Monitor**.
2. Set the baud rate to **9600 baud**.
3. Turn the potentiometer and observe the output.

Example output:

```text
ADC: 0 | Position: 0
ADC: 512 | Position: 90
ADC: 1023 | Position: 180
```

The program reads the potentiometer as a 10-bit ADC value from `0` to `1023`, maps it to an angle from `0°` to `180°`, and sends the resulting position to the servo through the `Servo.h` library.

### Testing Potentiometer Output Voltage

Tools needed:

- Digital multimeter
- Two jumper wires

1. Power the Arduino.
2. Connect one jumper wire to GND and another to the potentiometer’s middle pin (wiper).
3. Set the multimeter to DC voltage.
4. Connect the black probe to the GND wire and the red probe to the wiper wire.
5. Turn the potentiometer knob. The measured voltage should vary from approximately 0 V to 5 V.

## 5. Wokwi Simulation

Try the circuit online in the Wokwi simulator:

[Open the Arduino Uno potentiometer servo simulation](https://wokwi.com/projects/477239913595995137)

The Arduino sketch used by this project is available here:

[View `potentiometer_servo.ino`](https://github.com/uvang002/arduino-servo-potentiometer/blob/main/potentiometer_servo.ino)


## Limitations

- This project is designed for an Arduino Uno R3 using the ATmega328P.
- The servo angle range may vary depending on the servo model.
- `Servo.h` is used for servo positioning instead of `analogWrite()`.
- A small servo may use the Arduino `5V` pin, but larger servos should use a separate regulated 5V power supply.
- When using an external servo power supply, connect its ground to the Arduino `GND`.
- The potentiometer and servo may produce small fluctuations due to electrical noise.
