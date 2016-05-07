//  ___  ___  _   __   _   ___  _              _ 
// | __|| __|/ | /  \ / | | __|(_) _ _   __ _ | |
// | _| | _| | || () || | | _| | || ' \ / _` || |
// |___||___||_| \__/ |_| |_|  |_||_||_|\__,_||_|
                                               
//Define Digital Pins - These match up with the motor shield pinout.
#define Ech2 0
#define Trg2 1
#define Ain2 2
#define Ain1 3
#define Bin1 4
#define Bin2 5
#define Trg4 6
#define Ech4 7
#define Grn 8
#define PWMA 9
#define PWMB 10
#define Red 11
#define Ech1 12
#define Trg1 13
//Define Analog Pins - These match up with the motor shield pinout.
#define Trg3 A5
#define Ech3 A4
#define Meas A3
#define Blue A2
#define Opt2 A1
#define Opt1 A0

char outPins[] = {Trg2, Ain2, Ain1, Bin1, Bin2, Trg4, Grn, PWMA, PWMB, Red, Trg1, Trg3, Blue,};
char inPins[] = {Ech2, Ech4, Ech1, Ech3, Meas, Opt2, Opt1};

char IRlist[] = {Opt1,Opt2};
char UStrg[] = {Trg1, Trg2, Trg3, Trg4};
char USech[] = {Ech1, Ech2, Ech3, Ech4};

void drive(int leftval, int rightval){
  char Pins[] = {Ain1, Bin1, Ain2, Bin2, PWMA, PWMB};
  int values[] = {leftval,rightval};  
  //drive commands to run the motors. See motor controller datasheet.
  for(int i=0;i<2;i++){
    if(values[i]==0){
      //Stop left motor
      digitalWrite(Pins[i],LOW); digitalWrite(Pins[i+2],LOW); analogWrite(Pins[i+4],255);
    }else if(values[i]>0){
      //Drive left motor forwards
      digitalWrite(Pins[i],HIGH); digitalWrite(Pins[i+2],LOW);
      if(values[i]>255){values[i]=255;}
      analogWrite(Pins[i+4],values[i]);
    }else if(values[i]<0){
      //drive left motor in reverse
      values[i]=-values[i]; //invert input
      digitalWrite(Pins[i],LOW);
      digitalWrite(Pins[i+2],HIGH);
      if(values[i]>255){values[i]=255;}
      analogWrite(Pins[i+4],values[i]);
    }
  }
}

bool checkIR(int identity){ //Returns TRUE if opt is on a black line
  int IRvalue = analogRead(IRlist[identity]);
  if(IRvalue<10){return true;}
  else{return false;}
}

byte checkUS(int identity){ //Returns 0-255 cm distance measured on US
  digitalWrite(UStrg[identity],LOW);
  delayMicroseconds(2);
  digitalWrite(UStrg[identity],HIGH);
  delayMicroseconds(10);
  digitalWrite(UStrg[identity],LOW);
  long duration = pulseIn(USech[identity],HIGH);
  long distance = duration/58.2;
  return(distance);
}

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  for(int i=0; i<sizeof(outPins);i++){pinMode(outPins[i],OUTPUT);} //initialize output pins
  for(int i=0; i<sizeof(inPins);i++){pinMode(inPins[i],INPUT);}    //initialize input  pins
}

void loop() {
  // put your main code here, to run repeatedly:
  if(checkIR(0)){ //Right Side IR sensor
    drive(20,55);
    delay(200);
  }else if(checkIR(1)){ //Left Side IR sensor
    drive(55,20);
    delay(200);
  }else if((checkUS(0)< 5 && checkUS(0) != 0)){ //Front Facing Upper (FFU) US sensor
    // What happens when the top US sensor sees a wall
    
  } else if((checkUS(1)< 5 && checkUS(1) != 0)){ //When the FFU US Sensor doesn't see a wall but the Front Facing Lower US sensor does
    // Stop
    // Activate Color Sensor
    // Color statement (what happens when the correct is found) -- Use one LED and search for only Blue. Boolean?
  } else if(checkUS(1)>5){
    //drive straight - towards the object
  } else if((checkUS(2)!=0 && checkUS(3)==0)){ //If the Right Side US sensor doesn't see anything but the Left Side US sensor does
    //Turn to the left
  } else if((checkUS(2)==0 && checkUS(3)!=0)){ //If the Left Side US sensor doesn't see anything but the Right Side US sensor does
    //Turn to the right
  }
  else{
    drive(60,60);
  }
}
