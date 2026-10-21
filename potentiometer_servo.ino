#include <Servo.h>

Servo myservo;

const int potPin = A0;
const int servoPin = 9;

int potValue = 0;
int servoPosition = 0;

void setup() {
  myservo.attach(servoPin);

  Serial.begin(9600);
  delay(100);
  Serial.println("Start");
}

void loop() {
  potValue = analogRead(potPin);

  // Map the 10-bit ADC value (0-1023) to a servo angle (0-180 degrees).
  servoPosition = map(potValue, 0, 1023, 0, 180);

  myservo.write(servoPosition);

  Serial.print("ADC: ");
  Serial.print(potValue);
  Serial.print(" | Position: ");
  Serial.println(servoPosition);

  delay(15);
}
