#define IR_left #_#
#define IR_right #_#

void ArenaIR(byte IRleft, byte IRright){
  int Light = ____;
  int Dark = ____;

  if ((IRleft == Dark)&(IRright == Dark)){
    //stop
    //reverse for X millisecs
    //stop
    //turn Y degrees
    //go straight 
  } if else ((IRleft == Light)&(IRright == Dark)){
    //stop
    //turn Z degrees
    //go straight
  } if else ((IRleft == Dark)&(IRright == Light)){
    //stop
    //turn -Z degrees
    //go straight
  } else {
    // contuine
  }
}
