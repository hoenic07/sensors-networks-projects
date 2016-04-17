#include "Input.h"

Input::Input(Display* d){
  display = d;
  btnPin = 7;
}

Input::~Input(){
  
}

void Input::checkInput(){
  //TODO: Debounce button ...
  if(digitalRead(btnPin)==LOW){
    display->resetValues();
  }
}


void Input::rotaryEncoderChanged(){
  //Instance::display->scroll(1); //TODO dhcnage correct number of lines
}

