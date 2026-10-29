# Arduino Uno R3 Potentiometer Servo Control

This project provides an overview of the Arduino Uno R3 (driven by the ATmega328P microcontroller) and demonstrates how to control a servo motor using a potentiometer. For complete technical specifications, refer to the [ATmega328P datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/ATmega48A-PA-88A-PA-168A-PA-328-P-Data-Sheet-DS40002061B.pdf).

## Digital Logic Connection

This project applies basic embedded-systems concepts to a physical control system. The potentiometer produces an analog voltage, which the ADC converts into a 10-bit digital value. The program maps this digital value to a servo angle, and the `Servo.h` library generates the timed control pulses that position the servo arm.

## 1. ATmega328P Architecture and Features

### Core and Memory

- **CPU:** 8-bit AVR RISC-based processor.
- **Registers:** 32 general-purpose registers connected directly to the Arithmetic Logic Unit (ALU). Two registers can be accessed simultaneously, allowing execution of approximately 1 MIPS per MHz.
- **Flash memory:** In-system programmable flash memory capable of read-while-write operations.
- **SRAM:** Static random-access memory used for temporary data storage.

### Clock Management

- **Clock speed:** The ATmega328P supports operation up to 20 MHz under the appropriate supply-voltage conditions. The Arduino Uno R3 typically operates at 16 MHz.
- **Clock control unit:** Manages the clock signals for the CPU, I/O, flash memory, asynchronous timer, and ADC.
- **Prescaler:** Divides the system clock frequency to reduce the clock speed supplied to selected peripherals.

## 2. Timers and Timed Servo Position Pulses

### Timers and Counters

The ATmega328P includes three timer/counters:

- Two 8-bit timers
- One 16-bit timer

Timers can count based on the system clock or an external signal. They can also be used to generate timing events and timed position pulses. In this project, the Arduino `Servo` library uses a timer to generate the timed position pulses that represent the servo angle.

### Timed Position Pulses

Unlike ordinary PWM, a hobby servo uses the duration of each HIGH pulse to determine its position. The signal is repeated at a regular interval, while the pulse width changes with the target angle.

- **Pulse width:** The amount of time a signal remains HIGH.
- **Repeat period:** The time between successive position pulses.

## 3. Circuit Wiring

### Required Components

- Arduino Uno R3
- Standard hobby servo motor
- 10 kΩ potentiometer
- Breadboard and jumper wires
- USB cable

### Hardware Connections

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

### Monitor Servo Angle

To view the potentiometer reading and calculated servo angle:

1. Open **Tools → Serial Monitor**.
2. Set the baud rate to **9600 baud**.
3. Turn the potentiometer and observe the output.

Example output:

```text
Position: 0
Position: 90
Position: 180
```

### Servo Timing

The servo control signal is typically repeated about every 20 ms, which corresponds to approximately 50 Hz. The servo primarily uses the duration of the HIGH pulse to determine its position. The table below shows common nominal values:

| Pulse width | Approximate servo position |
|---:|---:|
| `544 µs` | `0°` |
| `1500 µs` | `90°` |
| `2400 µs` | `180°` |

In this sketch, `Servo.write()` uses the Arduino Servo library's default angle-to-pulse mapping (approximately `544–2400 µs`) unless a custom range is supplied. Individual servos may require a narrower or different range, so these values are not guaranteed limits.

### Signal Chain

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

## 5. Test the Circuit

### Measure the potentiometer voltage

A digital multimeter can verify the potentiometer output:

1. Power the Arduino.
2. Connect the multimeter black probe to `GND`.
3. Connect the red probe to the potentiometer wiper or `A0`.
4. Set the meter to DC voltage.
5. Turn the potentiometer and confirm that the voltage changes from approximately 0 V to 5 V.

### Observe the servo signal

A logic analyzer can show the control pulses on pin `D9`:

1. Connect channel `CH0` to Arduino pin `D9`.
2. Connect the analyzer ground to Arduino `GND`.
3. Set the sample rate to `100 kHz`.
4. Capture approximately one second of data.
5. Turn the potentiometer and observe the pulse width change.

The signal is typically repeated about every 20 ms, or 50 Hz, while the HIGH-pulse duration changes with the requested angle.

## 6. Wokwi Simulation

Try the circuit online in the Wokwi simulator:

[Open the Arduino Uno potentiometer servo simulation](https://wokwi.com/projects/477239913595995137)

The Arduino sketch used by this project is available here:

[View `potentiometer_servo.ino`](https://github.com/uvang002/arduino-servo-potentiometer/blob/main/potentiometer_servo.ino)


## Limitations

- This project is designed for an Arduino Uno R3 using the ATmega328P.
- The servo angle range may vary depending on the servo model.
- `Servo.h` is used to generate timed position pulses instead of `analogWrite()` PWM.
- Attaching a servo uses a timer resource and disables hardware PWM on pins `9` and `10` on the Uno while the servo is attached.
- Do not assume the Arduino `5V` pin can safely supply the servo's peak current. A small servo may work from the Arduino supply for brief, light-load tests, but a separate regulated 5V supply is recommended for reliable operation.
- When using an external servo power supply, connect its ground to the Arduino `GND`.
- The potentiometer and servo may produce small fluctuations due to electrical noise.
