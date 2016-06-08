#include "AccelerometerAnalyzer.h"

AccelerometerAnalyzer::AccelerometerAnalyzer(){
  rawBuffer = new RingBuffer(5);
  smoothedBuffer = new RingBuffer(50);
  stepsWindow = new RingBuffer(4);
}

AccelerometerAnalyzer::~AccelerometerAnalyzer(){
  
}

void AccelerometerAnalyzer::update(double sample){
  sample = sample - 1; // remove earth gravity
  int fpSample = sample*10000; // convert to int to avoid floating point ops
  
  //smooth value
  rawBuffer->add(fpSample);
  int smoothedSample = rawBuffer->getAverage();

  // get min / max
  smoothedBuffer->add(smoothedSample);
  if(sampleCount++ % 50 == 0){
    smoothedBuffer->calcMinMax();
  }

  // Step detection
  int max = smoothedBuffer->getMax();
  int min = smoothedBuffer->getMin();
  int thr = (max+min)/2;
  int isStep = 0;
  if(abs(smoothedSample-sample_new)>precision){
    sample_old = sample_new;
    sample_new = smoothedSample;

    if(sample_old != -64000 && 
        sample_new < sample_old &&
        sample_new < thr &&
        sample_old > thr){
          isStep=1;
        }
  }

  int lastStepTimeAgo=0;
  int stepInsert = -1;

  //Debug
  if(isStep==1){
    Serial.print(lastStepTime-sampleCount);
    Serial.print(";");
    Serial.println(smoothedSample);
  }

  // Step frequency
  if(isStep==1 && lastStepTime != 0){
    stepInsert = abs(lastStepTime-sampleCount);
    lastStepTime=sampleCount;
  }
  else if(isStep==1&&lastStepTime==0){
    lastStepTime=sampleCount;
    stepInsert=lastStepTime;
  }
  else if(isStep==0){
    lastStepTimeAgo = abs(lastStepTime-sampleCount);
  }

  //insert the stepTime into the window
  if(stepInsert != -1){
    if(stepInsert > 25) stepInsert = 25;
    stepsWindow->add(stepInsert);
  }
  
  //sum of steps within last 10 seconds
  int stepFreq = stepsWindow->getAverage(); 

  // 1 step = 1/20 sec
  if(lastStepTimeAgo >= 25 || stepFreq == -1){
    state = 0;
    stepsWindow->clear();
  }
  else if(stepFreq < 9) state = 2;
  else if(stepFreq < 25) state  = 1;
  else state = 0;
}

int AccelerometerAnalyzer::getState(){
  return state;
}



