#define Ain1 3
#define Ain2 2
#define Bin1 4
#define Bin2 5
#define PWMA 9
#define PWMB 10

// To drive a motor CCW:
// in1 -> LOW
// in2 -> HIGH
// PWM -> HIGH PWM 

void motorA(byte rate){
  //Drives motorA at PWM rate proportional to input byte. 0 = Full reverse, 255 = Full forward
  int drive_rate = 2 * rate-128;
  if(drive_rate>0){
    digitalWrite(Ain1,HIGH);
    digitalWrite(Ain2,LOW);
    analogWrite(PWMA,drive_rate);
  }
  else if(drive_rate<0){
    drive_rate= ~drive_rate;
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,HIGH);
    analogWrite(PWMA,drive_rate);
  }
  else{
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
    analogWrite(PWMA,255);
  }
}
void motorB(byte rate){
  //Drives motorB at PWM rate proportional to input byte. 0 = Full reverse, 255 = Full forward
  int drive_rate = 2 * rate-128;
  if(drive_rate>0){
    digitalWrite(Bin1,HIGH);
    digitalWrite(Bin2,LOW);
    analogWrite(PWMB,drive_rate);
  }
  else if(drive_rate<0){
    drive_rate= ~drive_rate;
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,HIGH);
    analogWrite(PWMB,drive_rate);
  }
  else{
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
    analogWrite(PWMB,255);
  }
}

void drive(byte left, byte right, bool debug = false) {
  //generic 'drive' command that drives each motor to the
  //value specified. Input is a byte (0-255)
  motorA(left); //drives MotorA to value 'left'
  motorB(right); //drives MOTORB to value 'right'
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
  pinMode(Ain1,OUTPUT);
  pinMode(Ain2,OUTPUT);
  pinMode(Bin1,OUTPUT);
  pinMode(Bin2,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  drive(192,0);
  delay(1000);
  drive(0,192);
  delay(1000);
  drive(64,64);
  delay(1000);
  drive(192,192);
  delay(1000);
  drive(192,64);
  delay(1000);
  drive(64,192);
  delay(1000);
  drive(129,129);
  delay(1000);
  drive(255,255);
  delay(1000);

}
