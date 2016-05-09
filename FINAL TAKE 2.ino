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

char IRlist[] = {Opt1, Opt2};
char UStrg[] = {Trg1, Trg2, Trg3, Trg4};
char USech[] = {Ech1, Ech2, Ech3, Ech4};

bool MazeNotFound = true;
bool NotThroughMaze = true;
bool BlueWhaleNotFound = true;
bool NotRemoved = true;

void drive(int leftval, int rightval) {
  char Pins[] = {Ain1, Bin1, Ain2, Bin2, PWMA, PWMB};
  int values[] = {rightval, leftval};
  //drive commands to run the motors. See motor controller datasheet.
  for (int i = 0; i < 2; i++) {
    values[i] = map(values[i],0,100,0,255);
    if (values[i] == 0) {
      //Stop left motor
      digitalWrite(Pins[i], LOW); digitalWrite(Pins[i + 2], LOW); analogWrite(Pins[i + 4], 255);
    } else if (values[i] > 0) {
      //Drive left motor forwards
      digitalWrite(Pins[i], HIGH); digitalWrite(Pins[i + 2], LOW);
      if (values[i] > 255) {
        values[i] = 255;
      }
      analogWrite(Pins[i + 4], values[i]);
    } else if (values[i] < 0) {
      //drive left motor in reverse
      values[i] = -values[i]; //invert input
      digitalWrite(Pins[i], LOW);
      digitalWrite(Pins[i + 2], HIGH);
      if (values[i] > 255) {
        values[i] = 255;
      }
      analogWrite(Pins[i + 4], values[i]);
    }
  }
}

byte checkUS(int identity) { //Returns 0-255 cm distance measured on US
  // Identity Numbers:
  // 0 = Front
  // 1 = Left
  // 2 = Right
  digitalWrite(UStrg[identity], LOW);
  delayMicroseconds(2);
  digitalWrite(UStrg[identity], HIGH);
  delayMicroseconds(10);
  digitalWrite(UStrg[identity], LOW);
  long duration = pulseIn(USech[identity], HIGH);
  long distance = duration / 58.2;
  return (distance);
}

int ShortestUS() { //Returns the identity number of the US sensor with the shortest distance
  // IF there one of the sensors isn't smaller than the others it returns 3
  byte pos[] = {checkUS(0), checkUS(1), checkUS(2)};

  for (int i = 0; i < sizeof(pos); i++) {
    if (pos[i] == 0) {pos[i] = 500;}}
  if ((pos[0] < pos[1] && pos[0] < pos[2])) {
    return 0;
  } else if ((pos[1] < pos[0] && pos[1] < pos[2])) {
    return 1;
  } else if ((pos[2] < pos[0] && pos[2] < pos[1])) {
    return 2;
  } else {
    return 3;}
}


void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  for (int i = 0; i < sizeof(outPins); i++) {
    pinMode(outPins[i], OUTPUT); //initialize output pins
  }
  for (int i = 0; i < sizeof(inPins); i++) {
    pinMode(inPins[i], INPUT); //initialize input  pins
  }
}
void loop() {
  // put your main code here, to run repeatedly:
}
