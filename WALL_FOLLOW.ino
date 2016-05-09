void followWall(int identity){
  if (checkUS(identity) =< 10){
    drive(30,30);  
  } else{
    if (identity == 0){
      drive(0,35);
    } else if (identity == 2){
      drive(35,0);
    }
  }
}
