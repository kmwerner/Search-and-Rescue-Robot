// David Robbins
// EE-101 quiz 1

#define A_1 4
#define A_2 2
#define B_1 5
#define B_2 7
#define PWMA 3
#define PWMB 6

void motorcontrol(int VA_i, int VB_i, float t){
int VA = VA_i*2.55;
int VB = VB_i*2.55;
Serial.print("Start");
Serial.print(VA);
Serial.println(VB);
//if(abs(VA)>100){VA = (VA/abs(VA)*100);}
//if(abs(VB)>100){VB = (VB/abs(VB)*100);}
if (VA>=0){
  digitalWrite(A_1,LOW);
  digitalWrite(A_2,HIGH);
  analogWrite(PWMA,VA);
  Serial.print("VA ");
  Serial.println(VA);
}
else if(VA<0){
  digitalWrite(A_1,HIGH);
  digitalWrite(A_2,LOW);
  analogWrite(PWMA,abs(VA));
  Serial.print("VA ");
  Serial.println(VA);
}
if (VB>=0){
  digitalWrite(B_1,LOW);
  digitalWrite(B_2,HIGH);
  analogWrite(PWMB,VB);
  Serial.print("BA ");
  Serial.println(VB);
}
else if(VB<0){
  digitalWrite(B_1,HIGH);
  digitalWrite(B_2,LOW);
  analogWrite(PWMB,abs(VB));
  Serial.print("BA ");
  Serial.println(VB);
}
delay(t*1000);
digitalWrite(A_1,LOW);
digitalWrite(A_2,LOW);
analogWrite(PWMA,0);
digitalWrite(B_1,LOW);
digitalWrite(B_2,LOW);
analogWrite(PWMB,0);
}

void setup(){
  pinMode(A_1,OUTPUT);
  pinMode(A_2,OUTPUT);
  pinMode(B_1,OUTPUT);
  pinMode(B_2,OUTPUT);
  Serial.begin(9600);
}

void loop(){
motorcontrol(50,0,1);
motorcontrol(0,50,1);
motorcontrol(-50,-50,1);
motorcontrol(50,50,1);
motorcontrol(50,-50,1);
motorcontrol(-50,50,1);
motorcontrol(1,1,1);
motorcontrol(100,100,1);
delay(2000);
}
