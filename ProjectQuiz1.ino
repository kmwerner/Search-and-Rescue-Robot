#define MOTOR1 3
#define MOTOR2 5

void forward(value) {
  int value = 0;
  digitalWrite(MOTOR1, HIGH);
  digitalWrite(MOTOR2, HIGH);
  analogWrite(MOTOR1, value);
  analogWrite(MOTOR2, value);
}
void backward(value) {
  int value = 0;
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
  analogWrite(MOTOR1, value);
  analogWrite(MOTOR2, value);
}
void setup() {
  // put your setup code here, to run once:
  pinMode(MOTOR1, OUTPUT);
  pinMode(MOTOR2, OUTPUT);
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
}
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(MOTOR1, HIGH); // left wheel
  analogWrite(MOTOR1, 126);
  delay(1000);
  digitalWrite(MOTOR2, HIGH); // right wheel
  analogWrite(MOTOR2, 126);
  delay(1000);
  forward(126); // both wheels move forward
  delay(1000);
  backward(126); // both wheels move backward
  delay(1000);
  digitalWrite(MOTOR1, HIGH); // left moves forward
  digitalWrite(MOTOR2, LOW);  // right moves backward
  analogWrite(MOTOR1, 126);
  analogWrite(MOTOR2, 126);
  delay(1000);
  digitalWrite(MOTOR1, LOW); // left moves backward
  digitalWrite(MOTOR2, HIGH); // right moves forward
  analogWrite(MOTOR1, 126);
  analogWrite(MOTOR2, 126);
  delay(1000);
  forward(255); // max forward speed
  delay(1000);
  forward(1); // min forward speed
  delay(1000);
}
