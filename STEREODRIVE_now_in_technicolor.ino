#define IN1a 4
#define IN2a 2
#define IN1b 5
#define IN2b 7
#define PWMA 3
#define PWMB 6

int gain = 1; // one time adjust gain variable. Gain represents the lowest possible "turn on" value for the motors. 1=<gain<255

void MotorsStereo(int RightChannel, int LeftChannel, int t) {
  if (RightChannel > 100) {
    RightChannel = 100;  //clip input to 100
  }
  if (RightChannel < -100) {
    RightChannel = -100;  //clip input to -100
  }
  if (LeftChannel > 100) {
    LeftChannel = 100;  //clip input to 100
  }
  if (LeftChannel < -100) {
    LeftChannel = -100;  //clip input to -100
  }

  pinMode(IN1a, OUTPUT);
  pinMode(IN2a, OUTPUT);
  pinMode(IN1b, OUTPUT);
  pinMode(IN2b, OUTPUT);

  if (RightChannel > 0) {
    RightChannel = map(RightChannel, 1, 100, gain, 255);  //remap input to 8-bit PWM signal (0-255)
    digitalWrite(IN1a, LOW);
    digitalWrite(IN2a, HIGH);
    analogWrite(PWMA, RightChannel);
    Serial.print("PWM SIGNAL A: ");
    Serial.println(RightChannel);
  }
  else if (RightChannel < 0) {
    RightChannel = map(RightChannel, -1, -100, -gain, -255);  //remap input to 8-bit PWM signal (0-255)
    digitalWrite(IN1a, HIGH);
    digitalWrite(IN2a, LOW);
    analogWrite(PWMA, RightChannel);
    Serial.print("PWM SIGNAL A: ");
    Serial.println(RightChannel);
  }
  else
    digitalWrite(IN1a, LOW);
  digitalWrite(IN2a, LOW);
  if (LeftChannel > 0) {
    LeftChannel = map(LeftChannel, 1, 100, gain, 255);   //remap input to 8-bit PWM signal (0-255)
    digitalWrite(IN1b, LOW);              //THESE MAY NEED TO BE SWAPPED, DUE TO
    digitalWrite(IN2b, HIGH);             //MOTOR BEING ON THE OTHER SIDE OF THE VEHICLE
    analogWrite(PWMB, LeftChannel);
    Serial.print("PWM SIGNAL B: ");
    Serial.println(LeftChannel);
  }
  else if (LeftChannel < 0) {
    LeftChannel = map(LeftChannel, -1, -100, -gain, -255);   //remap input to 8-bit PWM signal (0-255)
    digitalWrite(IN1b, HIGH);            //THESE MAY NEED TO BE SWAPPED, DUE TO
    digitalWrite(IN2b, LOW);             //MOTOR BEING ON THE OTHER SIDE OF THE VEHICLE
    analogWrite(PWMB, LeftChannel);
    Serial.print("PWM SIGNAL B: ");
    Serial.println(LeftChannel);
  }
  else
  digitalWrite(IN1b, LOW);
  digitalWrite(IN2b, LOW);
  delay(t);
  
  digitalWrite(IN1a, LOW); //then kill all motors by driving output low.
  digitalWrite(IN2a, LOW);
  digitalWrite(IN1b, LOW);
  digitalWrite(IN2b, LOW);
}
void setup() {
  Serial.begin(9600);
}
void loop() {
  MotorsStereo(100, 100, 1000); //Drives full forward for 1 second
  delay(1000);
}
