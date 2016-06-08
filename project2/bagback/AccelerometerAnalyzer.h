#ifndef ACCELEROMETERANALYZER_H
#define ACCELEROMETERANALYZER_H

#include "RingBuffer.h"
#include "Arduino.h"

class AccelerometerAnalyzer {
  public:
   AccelerometerAnalyzer();
   ~AccelerometerAnalyzer();
   void update(double acc);
   int getState();
  private:
   RingBuffer* rawBuffer;
   RingBuffer* smoothedBuffer;
   RingBuffer* stepsWindow;
   int sampleCount = 0;
   int precision=500;
   int sample_new=0;
   int sample_old=-64000;

   long lastStepTime=0;
   int state = 0;
   
};

#endif
