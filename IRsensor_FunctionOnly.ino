#define IR A0

int IRvalue;
int IRflag_value = 10;
bool flag = false;

bool IRflag(){
  IRvalue = analogRead(IR);
  if (IRvalue < IRflag_value){ //We are about to run over a line!
    flag = true;
  }else{ //We're all good.
    flag = false;
  }
  return flag;
}

/*void line_follow(){
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
