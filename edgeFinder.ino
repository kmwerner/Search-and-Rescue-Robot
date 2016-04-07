#define triggerPin 6
#define echoingPin 7
#define servoingPin 8
#define LED 13
long distance;
int angle = 0;
int astep = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoingPin, INPUT);
  pinMode(servoingPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  distance = ultrasonicPulse(triggerPin, echoingPin);
  while(distance > 20){
    servoPulse(servoingPin, angle);
    distance = ultrasonicPulse(triggerPin, echoingPin);
    Serial.print("Degree: ");
    Serial.println(angle);
    Serial.print("Ultrasonic: ");
    Serial.print(distance);
    Serial.println(" cm");
    angle = angle + astep;
    delay(50);
    if(angle >= 170 || angle <= 0){
      astep = astep*-1;
    }
  }
digitalWrite(LED,HIGH);
delay(1000);
digitalWrite(LED,LOW);
}

void servoPulse(int servo, int angle) {
  int pwm = (angle * 11) + 500; //convert angle to microseconds
  digitalWrite(servo, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(servo, LOW);
  delay(10);

}

long ultrasonicPulse(int trigPin, int echoPin) {
  delay(10);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH);
  long distance = duration / 58.2;
  //     Serial.println(distance);
  return distance;
}



//  float duration;
//  float distance;
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//
//  //Listen to Ultrasonic
//  duration = pulseIn(echoPin, HIGH,500);
//  return distance = (duration / 2) / 29.1;
//
//  if (distance >= 100 || distance <= 0) {
//    Serial.println("Out of Range");
//  }
//  else {
//    Serial.print(distance);
//    Serial.println(" cm");
//  }
//  delay(10);


