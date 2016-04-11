#define MOTOR1 3
#define MOTOR2 5

void drive(byte left, byte right, bool debug = false) {
  //generic 'drive' command that drives each motor to the
  //value specified. Input is a byte (0-255)
  analogWrite(MOTOR1, left); //drives Motor1 to value 'left'
  analogWrite(MOTOR2, right); //drives MOTOR2 to value 'right'
  if(debug){ //prints debug information if flagged to do so
    Serial.print("Driving Motor1:");
    Serial.print(left);
    Serial.print("  Motor2:");
    Serial.println(right);
  }
}

void drivestraight(byte straight) {
  //simple command for telling the bot to drive straight.
  //input is a byte, so it ranges from 0-255
  drive(straight,straight);
}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
