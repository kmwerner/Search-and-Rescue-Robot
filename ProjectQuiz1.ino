#define MOTOR1 3
#define MOTOR2 5

void forward(int value) {
  digitalWrite(MOTOR1, HIGH);
  digitalWrite(MOTOR2, HIGH);
  analogWrite(MOTOR1, value);
  analogWrite(MOTOR2, value);
}
void backward(int value) {
  digitalWrite(MOTOR1, LOW);
  digitalWrite(MOTOR2, LOW);
  analogWrite(MOTOR1, value);
  analogWrite(MOTOR2, value);
}
void turn_left(int value) {
  digitalWrite(MOTOR1, HIGH); 
  digitalWrite(MOTOR2, LOW); 
  analogWrite(MOTOR1, value);
  analogWrite(MOTOR2, value);
}

void turn_right(int value) {
  digitalWrite(MOTOR1, LOW); 
  digitalWrite(MOTOR2, HIGH); 
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
  forward(126); 
  delay(1000);
  backward(126); 
  delay(1000);
  turn_left(126);
  delay(1000);
  turn_right(126);
  delay(1000);
  forward(255); // max forward speed
  delay(1000);
  forward(1); // min forward speed
  delay(1000);
}
