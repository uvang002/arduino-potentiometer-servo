const int potPin = A0;
const int pwmPin = 9;  // D9 is used here as ordinary PWM output (not Servo.h control pulses).

int adcValue = 0;
int pwmDuty = 0;

void setup() {
  pinMode(pwmPin, OUTPUT);
  Serial.begin(9600);
  delay(100);
  Serial.println("Potentiometer to PWM output (analogWrite)");
}

void loop() {
  adcValue = analogRead(potPin);

  // Map 10-bit ADC input (0-1023) to 8-bit PWM duty output (0-255).
  pwmDuty = map(adcValue, 0, 1023, 0, 255);

  analogWrite(pwmPin, pwmDuty);

  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | PWM duty: ");
  Serial.println(pwmDuty);

  delay(50);
}
