#include "Input.h"

Input::Input(Display* d, Parameters* p){
  display = d;
  parameters = p;
  btnPin = 7;
}

Input::~Input(){
  
}

void Input::checkInput(){
  if(digitalRead(btnPin)==LOW){
    //display->scroll(1);
    pressCount++;
  }
  else{
    if(pressCount>=MIN_VALID_PRESS_COUNT){
      display->scroll(1);
    }
    pressCount=0;
  }
}


void Input::rotaryEncoderChanged(){
  //Instance::display->scroll(1); //TODO dhcnage correct number of lines
}

