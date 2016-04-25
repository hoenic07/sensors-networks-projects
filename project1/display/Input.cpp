#include "Input.h"

Input::Input(Display* d, Parameters* p){
  display = d;
  parameters = p;
  btnPin = 7;
}

Input::~Input(){
  
}

void Input::checkInput(){

  //button
  if(digitalRead(btnPin)==LOW){
    parameters->setMinMaxDefaultValues();
    pressCount++;
  }
  else{
    if(pressCount>=MIN_VALID_PRESS_COUNT){
      display->scroll(1);
    }
    pressCount=0;
  }

  //rotary encoder
  double volt=analogRead(A1);
  int newSection = (int)(volt/ROTARY_SECTION_SIZE);
  if(newSection != lastRotarySection){
    lastRotarySection=newSection;
    display->scroll(newSection);
  }
}
