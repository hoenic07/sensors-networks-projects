#include "Input.h"
#include "Instance.h"

Input::Input(){
  
}

Input::~Input(){
  
}

void Input::checkInput(){
  //TODO: Debounce button ...
}

void Input::buttonPressed(){
  //Reset values
}

void Input::rotaryEncoderChanged(){
  Instance::display->scroll(1); //TODO dhcnage correct number of lines
}

