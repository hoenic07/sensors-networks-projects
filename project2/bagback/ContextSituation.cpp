#include "ContextSituation.h"


ContextSituation::ContextSituation(){
  piezo = new Piezo();
  accAnalyzer = new AccelerometerAnalyzer();
  piezo->init();

  standingLed = new Led(LED_ID_STANDING);
  standingLed->init();
  walkingLed = new Led(LED_ID_WALKING);
  walkingLed->init();
  runningLed = new Led(LED_ID_RUNNING);
  runningLed->init();
  rgbLed = new RGBLed(LED_ID_RED, LED_ID_BLUE, LED_ID_GREEN);
  rgbLed->init();
}

ContextSituation::~ContextSituation() {
}

void ContextSituation::update() {
  if(lumen > THRESHOLD_OPEN) {
    piezo->setActivated(true);
    applyDiscoMode(true);
  }else{
    piezo->setActivated(false);
    applyDiscoMode(false);
  }
 
  runningLed->setActive(false);
  walkingLed->setActive(false);
  standingLed->setActive(false);

  if(accAnalyzer->getState() == 0){
  	runningLed->setActive(true);
  }
  else if(accAnalyzer->getState() == 1){
  	walkingLed->setActive(true);
  }
  else{
  	standingLed->setActive(true);
  }
}

void ContextSituation::setAcc(double x, double y, double z){
  accX = x;
  accY = y;
  accZ = z;
  double totalAcc = sqrt(x*x+y*y+z*z); // calc total acceleration
  accAnalyzer->update(totalAcc);
}
void ContextSituation::setTemperature(double t){
  temp = t;
}
void ContextSituation::setLumen(double l){
  lumen = l;
}

void ContextSituation::applyDiscoMode(boolean active){
  if(active){
     switch(discoCnt){
      case 0:
        rgbLed->setColor(0,0,255);
        break;
      case 1:
        rgbLed->setColor(0,255,0);
        break;
      case 2:
        rgbLed->setColor(255,0,0);
        break;
    }
    discoCnt++;
    if(discoCnt >= DISCO_CNT_MAX){
      discoCnt = 0;
    }
  }else{
    rgbLed->setColor(0,0,0);
  }
}

