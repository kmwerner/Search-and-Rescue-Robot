#define triggerPin1 13
#define echoingPin1 12
#define triggerPin2 A5
#define echoingPin2 A4
#define A_1 4
#define A_2 2
#define B_1 5
#define B_2 7
#define PWMA 3
#define PWMB 6
#define SWITCHPIN1 A1
#define SWITCHPIN2 A0
const int RED = A3;
const int BLUE = 11;
const int GREEN = 10;
const int AREAD =  A2;
int  switch_state1;
int  switch_state2;
long distance1;
long distance2;
int angle = 0;
int astep = 3;
int lspeed = -25;
int rspeed = 25;
int block_out;
int find_line;
int primer;
int linecount;
int cl;
int check_color;
// Color order: 0 is red, 1 is blue, and 2 is green
int color_order[3] = {
  0,2,1};
int block_number = 0;
int abort1;
int abort2;
int correct;
int LED[3] = {
  RED,GREEN,BLUE};
int red[3];
int green[3];
int blue[3];
int color[3];
int countdown = 0;

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Motor control function.

void motorcontrol(int VA_i, int VB_i, float t){
  // left turn with black wires inside
  //motorcontrol(20,-20,1);
  // right turn with black wires inside
  //motorcontrol(-20,20,1);
  int VA = VA_i*2.55;
  int VB = VB_i*2.55;
  if (VA>=0){
    digitalWrite(A_1,LOW);
    digitalWrite(A_2,HIGH);
    analogWrite(PWMA,VA);
  }
  else if(VA<0){
    digitalWrite(A_1,HIGH);
    digitalWrite(A_2,LOW);
    analogWrite(PWMA,abs(VA));
  }
  if (VB>=0){
    digitalWrite(B_1,LOW);
    digitalWrite(B_2,HIGH);
    analogWrite(PWMB,VB);
  }
  else if(VB<0){
    digitalWrite(B_1,HIGH);
    digitalWrite(B_2,LOW);
    analogWrite(PWMB,abs(VB));
  }
  delay(t*1000);
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,LOW);
  analogWrite(PWMA,0);
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,LOW);
  analogWrite(PWMB,0);
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Distance function for the ultrasonic sensor.  Returns distance in cm.
//////////////////////////////////////////////////////////////////////////////

long ultrasonicPulse(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(7);
  digitalWrite(trigPin, LOW);
  long duration = pulseIn(echoPin, HIGH,5820);  //Added third arg to reduce cornering time
  long distance = duration / 58.2;
  //     Serial.println(distance);
  if(distance == 0){
    distance = 100;
  }
  return distance;
}
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Line following function.  Robot drives along the line, looking inside for
// a block.  Whenever one is detected, it breaks from the line following code
// in order to find the block.
//////////////////////////////////////////////////////////////////////////////
// This code is designed for counter-clockwise travel
// SWITCHPIN1 reads from an optical sensor mounted on the back left
// SWITCHPIN2 reads from an optical senor mountaed on the back right
//////////////////////////////////////////////////////////////////////////////
void line_follow(){
  distance2 = ultrasonicPulse(triggerPin2, echoingPin2);
  while(distance2 > 40 || countdown > 1){
    countdown--;
    distance2 = ultrasonicPulse(triggerPin2, echoingPin2);
    Serial.println(distance2);
    switch_state1 = digitalRead(SWITCHPIN1);
    if (switch_state1 == HIGH){
      //motorcontrol(20,35,.07);
      //motorcontrol(30,45,.03);
      motorcontrol(20,40,.03);
    }
    else{
      //motorcontrol(40,25,.07);
      //motorcontrol(47,32,.03);
      motorcontrol(45,25,.03);
    }
  }
  motorcontrol(20,25,.5);
} // end line follow

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Function for finding and pushing out block.  Turns until it sees a block,
// and then drives forward once a block is found.  Once block is out of the
// the arena, reveses and then moves back into the arena.
// The timer is put in place go make sure that the robot doesn't read the first
// line it crosses as the end line.  It is set for about a 2 second delay, and
// each loop takes about 30 ms, so it counts 67 cycles
//////////////////////////////////////////////////////////////////////////////
void block_find(){
  distance1 = ultrasonicPulse(triggerPin1, echoingPin1);
  Serial.println("BLock find");
  Serial.println("Ultrasonic1:"+distance1);
  block_out = 0;
  check_color = 0;
  correct = 0;
  int time = 0;
  int time2= 0;
  while(block_out == 0){
    time++;
    distance1 = ultrasonicPulse(triggerPin1, echoingPin1);
    while(distance1 > 50){
      time2++;
      motorcontrol(rspeed,lspeed,.03);
      distance1 = ultrasonicPulse(triggerPin1, echoingPin1);
      Serial.println(distance1);
      switch_state2 = digitalRead(SWITCHPIN2);
      if(switch_state2 == HIGH && time2 > 65){
        motorcontrol(-20,-25,.35);
        distance1 = 49;
        block_out = 1;
      }

    }
    Serial.println("Forward");
//    if(distance1 > 12){
//      motorcontrol(30,29,.07);
//    }
//    else{
      motorcontrol(33,33,.07);
//    }
    Serial.print("Distance before color: ");
    Serial.println(distance1);
    color_test();
    if(correct == 0 && check_color == 1){
      return;
    }
    switch_state2 = digitalRead(SWITCHPIN2);
    if(switch_state2 == HIGH && time > 67){
      block_out = 1;
      if(check_color == 1){
        block_number++;
      }
      motorcontrol(-20,-25,.35);
    }
  }
  find_line = 0;
  while(find_line == 0 && block_number < 3){
    motorcontrol(25,-25,.05);
    switch_state1 = digitalRead(SWITCHPIN1);
    if(switch_state1 == HIGH){
      find_line = 1;
    }
  }
} // end block_find

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Color testing function.  Checks the color.  If it's right, it continues to
// push out the block.  If not, it reverses and begins to follow the line again.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void color_test(){
  abort1 = 0;
  abort2 = 0;
  if(distance1 < 8 && check_color == 0){
    cl = colorcheck();
    check_color = 1;
    if(cl != color_order[block_number] && block_number < 2){
      Serial.print("color wrong");
      correct = 0;
      while(abort1 == 0){
        motorcontrol(-20,-25,.05);
        switch_state1 = digitalRead(SWITCHPIN1);
        if(switch_state1 == HIGH){
          abort1 = 1;
          motorcontrol(17,17,.5);
        }
      }
      while(abort2 == 0){
        motorcontrol(-25,25,.05);
        switch_state2 = digitalRead(SWITCHPIN2);
        if(switch_state2 == HIGH){
          abort2 = 1;
          countdown = 80;
        }
      }
    }
    else{
      correct = 1;
      Serial.print("color correct");
    }
  }
} // end color_test

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Color sensor code
//////////////////////////////////////////////////////////////////////////////

int setred(){
  delay(2000);
  Serial.println("Set red in:");
  for(int k=3; k > 0; k--){
    delay(1000);
    Serial.println(k);
  }
  for(int i = 0; i < 3; i++){
    digitalWrite(LED[i],LOW);
    delay(100);
    red[i] = analogRead(AREAD);
    digitalWrite(LED[i],HIGH);
  }
  for(int i = 0; i < 3; i++){
    Serial.print(red[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}
int setgreen(){
  delay(2000);
  Serial.println("Set green in:");
  for(int k=3; k > 0; k--){
    delay(1000);
    Serial.println(k);
  }
  for(int i = 0; i < 3; i++){
    digitalWrite(LED[i],LOW);
    delay(100);
    green[i] = analogRead(AREAD);
    digitalWrite(LED[i],HIGH);
  }
  for(int i = 0; i < 3; i++){
    Serial.print(green[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}

int setblue(){
  delay(2000);
  Serial.println("Set blue in:");
  for(int k=3; k > 0; k--){
    delay(1000);
    Serial.println(k);
  }
  for(int i = 0; i < 3; i++){
    digitalWrite(LED[i],LOW);
    delay(100);
    blue[i] = analogRead(AREAD);
    digitalWrite(LED[i],HIGH);
  }
  for(int i = 0; i < 3; i++){
    Serial.print(blue[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
}

int colorcheck(){
  float range = .15;
  for(int i = 0; i < 3; i++){
    digitalWrite(LED[i],LOW);
    delay(100);
    color[i] = analogRead(AREAD);
    digitalWrite(LED[i],HIGH);
  }
  if(color[0] < (1+range)*red[0] && color[0] > (1-range)*red[0] &&
color[1] < (1+range)*red[1] && color[1] > (1-range)*red[1] && color[2]
< (1+range)*red[2] && color[2] > (1-range)*red[2]){
    cl = 0; // Red
  }
  else if(color[0] < (1+range)*blue[0] && color[0] > (1-range)*blue[0]
&& color[1] < (1+range)*blue[1] && color[1] > (1-range)*blue[1] &&
color[2] < (1+range)*blue[2] && color[2] > (1-range)*blue[2]){
    cl = 1; // Blue
  }
  else if(color[0] < (1+range)*green[0] && color[0] >
(1-range)*green[0] && color[1] < (1+range)*green[1] && color[1] >
(1-range)*green[1] && color[2] < (1+range)*green[2] && color[2] >
(1-range)*green[2]){
    cl = 2; // Green
  }
  else{
    cl = 3; // ???
  }
  return cl;
}

void pulse(){
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED[i], LOW);
    delay(100);
    digitalWrite(LED[i], HIGH);
  }
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// Exit Code.  Reverses cart out of arena.
//////////////////////////////////////////////////////////////////////////////

void exit(){
  int done = 0;
  int time = 0;
  if(block_number > 2){
    while(done == 0){
      time++;
      motorcontrol(-90,-99,.05);
      switch_state1 = digitalRead(SWITCHPIN1);
      if(switch_state1 == HIGH && time > 60){
        done = 1;
      }
    }
    delay(10000);
  }
}

void setup(){
  Serial.begin(9600);
  pinMode(A_1,OUTPUT);
  pinMode(A_2,OUTPUT);
  pinMode(B_1,OUTPUT);
  pinMode(B_2,OUTPUT);
  pinMode(SWITCHPIN1,INPUT);
  pinMode(SWITCHPIN2,INPUT);
  pinMode(triggerPin1, OUTPUT);
  pinMode(echoingPin1, INPUT);
  pinMode(triggerPin2, OUTPUT);
  pinMode(echoingPin2, INPUT);
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(AREAD, INPUT);
  pulse();
  int red = setred();
  int green = setgreen();
  int blue = setblue();
  Serial.begin(9600);
  delay(5000);
}

void loop(){
  line_follow();
  block_find();
  exit();
}
