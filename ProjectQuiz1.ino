#define Ain1 2
#define Ain2 3
#define Bin1 4
#define Bin2 5
#define PWMA 9
#define PWMB 10

char outPins[] = {Ain1, Ain2, Bin1, Bin2, PWMA, PWMB};

void motorA(int motorspeed){
  //Low level motor control. Drives motorA at PWM rate proportional to input byte. -100 = full reverse, 100 = full forward
  
  if(motorspeed>100){
    // input protection; clamps input to 100
    motorspeed = 100;
  }
  else if(motorspeed<-100){
    // input protection; clamps input to -100
    motorspeed = -100;
  }
  
  if(motorspeed>0){
    // drive motor according to spec sheet (CW)
    byte drive_rate = map(motorspeed,1,100,1,255); // scales motorspeed into PWM drive_rate
    digitalWrite(Ain1,HIGH);
    digitalWrite(Ain2,LOW);
    analogWrite(PWMA,drive_rate);
  }
  else if(motorspeed<0){
    // drive motor according to spec sheet (CCW)
    motorspeed = -motorspeed;
    byte drive_rate = map(motorspeed,1,100,1,255); // scales motorspeed into PWM drive_rate
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,HIGH);
    analogWrite(PWMA,drive_rate);
  }
  else{
    //MOTOR STOP command according to datasheet
    digitalWrite(Ain1,LOW);
    digitalWrite(Ain2,LOW);
    analogWrite(PWMA,255);
  }
}
void motorB(int motorspeed){
  //Drives motorA at PWM rate proportional to input byte. -100 = full reverse, 100 = full forward
  
  if(motorspeed>100){
    // input protection; clamps input to 100
    motorspeed = 100;
  }
  else if(motorspeed<-100){
    // input protection; clamps input to -100
    motorspeed = -100;
  }
  if(motorspeed>0){
    byte drive_rate = map(motorspeed,1,100,1,255); // scales motorspeed into PWM drive_rate
    digitalWrite(Bin1,HIGH);
    digitalWrite(Bin2,LOW);
    analogWrite(PWMB,drive_rate);
  }
  else if(motorspeed<0){
    motorspeed = -motorspeed;
    byte drive_rate = map(motorspeed,1,100,1,255); // scales motorspeed into PWM drive_rate
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,HIGH);
    analogWrite(PWMB,drive_rate);
  }
  else{
    //MOTOR STOP command according to datasheet
    digitalWrite(Bin1,LOW);
    digitalWrite(Bin2,LOW);
    analogWrite(PWMB,255);
  }
}

void drive(int left, int right, int bias = 0 ,bool debug = false) {
  //generic 'drive' command that drives each motor to the
  //value specified. Input for each motor is -100 to 100, with 
  //-100 as full reverse and 100 as full power forward.
  //bias variable is used to calibrate driving straight. It will
  //add this value to the right motor and remove it from the left motor.
  //
  //Ensure motors are calibrated properly. May include a function for this.
  motorA(left); //drives MotorA to value 'left'
  motorB(right); //drives MOTORB to value 'right'
  if(debug){ //prints debug information if flagged to do so
    Serial.print("Driving Motor1:");
    Serial.print(left);
    Serial.print("  Motor2:");
    Serial.println(right);
  }
}

void drivestraight(int straight) {
  //High level driving command for telling the bot to drive straight.
  //input is a byte, so it ranges from 0-255
  drive(straight,straight);
}

void tankright(int tankrightspeed = 20){
  //Skid-steers the bot to the right.
  drive(-tankrightspeed, tankrightspeed);
}

void tankleft(int tankleftspeed = 20){
  //skid-steers the bot to the left.
  drive(tankleftspeed,-tankleftspeed);
}

void setup() {
  // put your setup code here, to run once:
  for(int i = 0;i < sizeof(outPins);i++){
    pinMode(outPins[i],OUTPUT);
  } 
}

void loop() {
  // put your main code here, to run repeatedly:
  drive(50,0);
  delay(1000);
  drive(0,50);
  delay(1000);
  drive(-50,-50);
  delay(1000);
  drive(50,50);
  delay(1000);
  drive(50,-50);
  delay(1000);
  drive(-50,50);
  delay(1000);
  drive(1,1);
  delay(1000);
  drive(100,100);
  delay(1000);
}
