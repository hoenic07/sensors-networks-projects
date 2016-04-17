#include "Display.h"
//#include "Instance.h"

Display::Display() {
  curTopLine = CUR_TEMP;
  lcd = new SoftwareSerial(0, 2);
  lcd->begin(9600);
  clearDisplay();

  resetValues();
}

Display::~Display(){
 
}


void Display::update(){
  lcdPosition(0,0);
  showLine(curTopLine);
  lcdPosition(1,0);
  showLine(static_cast<Line>(curTopLine + 1));
}

void Display::resetValues() {

  tempDeg = -1;
  minTempDeg = 100;
  maxTempDeg = -100;
}

void Display::scroll(int lines){
  curTopLine = static_cast<Line>(curTopLine + lines);
  
}


void  Display::showCurrentTemp() {
  lcd->print(tempDeg, DEC);
  lcd->print((char)223); //TODO clear prev value if lower
  lcd->print("C");
}

void  Display::showMinTemp() {
  lcd->print("Min: ");
  lcd->print(minTempDeg, DEC);
  lcd->print((char)223);
  lcd->print("C");
}

void  Display::showMaxTemp() {
  lcd->print("Max: ");
  lcd->print(maxTempDeg, DEC);
  lcd->print((char)223);
  lcd->print("C");
}

void  Display::showLine(Line line){
  
   switch(line) {
    case CUR_TEMP:
      showCurrentTemp();
      break;
    case TEMP_MIN:
      showMinTemp();
      break;
    case TEMP_MAX:
      showMaxTemp();
      break;
  }
}

void Display::setTemp(int degrees) {
  
  tempDeg = degrees;

  //update min and max temperature
  if(tempDeg < minTempDeg) {
    minTempDeg = tempDeg;
  }else if(tempDeg > maxTempDeg){
    maxTempDeg = tempDeg; 
  }
}

void Display::clearDisplay(){
  lcd->write(0xFE);   //command flag
  lcd->write(0x01);   //clear command.
  delay(LCD_DELAY);
}
void Display::lcdPosition(int row, int col) {
  lcd->write(0xFE);   //command flag
  lcd->write((col + row*64 + 128));    //position 
  delay(LCD_DELAY);
}

