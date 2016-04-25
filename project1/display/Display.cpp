#include "Display.h"
Display::Display(Parameters* p, Accelerometer *a) {
  parameters=p;
  accelerometer=a;
  curTopLine = (Line)0;
  lcd = new SoftwareSerial(0, 2);
  lcd->begin(9600);
  clearDisplay();
}

Display::~Display(){
 
}

void Display::update(){
  lcdPosition(0,0);
  showLine(curTopLine);
  lcdPosition(1,0);
  showLine((Line)(curTopLine+1));
}

void Display::scroll(int newLine){
  
  int cLineNumber = (int)curTopLine;
  if(newLine<0 && newLine>5) return;

  clearDisplay();
  curTopLine = (Line)(newLine);
}

void  Display::showCurrentTemp() {
  lcd->print("Temp ");
  lcd->print(tempDeg, DEC);
  lcd->print((char)223); //TODO clear prev value if lower
  lcd->print("C");
}

void  Display::showMinTemp() {
  int minVal = (int)parameters->getValue(MIN_TEMP);
  lcd->print("Min T: ");
  lcd->print(minVal, DEC);
  lcd->print((char)223);
  lcd->print("C");
}

void  Display::showMaxTemp() {
  int maxVal = (int)parameters->getValue(MAX_TEMP);
  lcd->print("Max T: ");
  lcd->print(maxVal, DEC);
  lcd->print((char)223);
  lcd->print("C");
}

void Display::showAccX() {
  double maxVal = parameters->getValue(MAX_ACC_X);
  double val = accelerometer->getX();
  lcd->print("X ");
  printFloat(val);
  lcd->print("g Mx ");
  printFloat(maxVal);
}

void Display::showAccY() {
  double maxVal = parameters->getValue(MAX_ACC_Y);
  double val = accelerometer->getY();
  lcd->print("Y ");
  printFloat(val);
  lcd->print("g Mx ");
  printFloat(maxVal);
}

void Display::showAccZ() {
  double maxVal = parameters->getValue(MAX_ACC_Z);
  double val = accelerometer->getZ();
  lcd->print("Z ");
  printFloat(val);
  lcd->print("g Mx ");
  printFloat(maxVal);
}

void Display::showPitchRoll() {
  int valP = (int)accelerometer->getPitch();
  int valR = (int)accelerometer->getRoll();
  lcd->print("P ");
  lcd->print(valP, DEC);
  lcd->print((char)223);
  lcd->print(" R ");
  lcd->print(valR, DEC);
  lcd->print((char)223);
}

void Display::printFloat(double val){
  int first=(int)val;
  int second = (int)((val-first)*100);
  lcd->print(first, DEC);
  lcd->print(".");
  if(second<10)lcd->print("0");
  lcd->print(second, DEC);
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
    case ACC_X:
      showAccX();
      break;
    case ACC_Y:
      showAccY();
      break;
    case ACC_Z:
      showAccZ();
      break;
    case PITCH_ROLL:
      showPitchRoll();
      break;
  }
}

void Display::setTemp(int degrees) {
  tempDeg = degrees;
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

