#define IR_left #_#
#define IR_right #_#

void ArenaIR(bool IRSensor){
bool IRSensor = FALSE; // stores whether the robot is on a black line. True = Black Line

if(IRSensor){ //We are about to run over a line!
// things to do if we run over a black line; //this loop should be very fast (<1ms)
delay(5)
}
else{ //We're all good.
//things to do if we are in the regular arena; //this loop should be very fast (<1ms)
delay(5)
}
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
