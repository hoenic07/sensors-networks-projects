#include "AccelerometerAnalyzer.h"

AccelerometerAnalyzer::AccelerometerAnalyzer(){
  rawBuffer = new RingBuffer(5);
  smoothedBuffer = new RingBuffer(50);
  stepsWindow = new RingBuffer(100);
  stepsWindow->showDebug=1;
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
          //Serial.print("Step ");
          //Serial.println(sampleCount);
        }
  }

  stepsWindow->add(isStep);

  //sum of steps within last 10 seconds
  int sumSteps = stepsWindow->getSum(); 

  Serial.print(sumSteps);

  if(sumSteps < 2){
    state = 0;
    Serial.println(" Standing");
  }
  else if(sumSteps < 8){
    state  = 1;
    Serial.println(" Walking");
  }
  else if(sumSteps >= 8){
    state = 2;
    Serial.println(" Running");
  }    
}

int AccelerometerAnalyzer::getState(){
  return state;
}



