#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "Arduino.h"

class RingBuffer {
  public:
   int showDebug=0;
   RingBuffer(int size){
    this->size=size;
    buffer = new int[size];
   }
   ~RingBuffer();
   
   void add(int val){

    //add new value to total sum
    sum+=val;    

    if(length==size){
      //ringbuffer full
      currentPositionIndex = (currentPositionIndex+1)%size;
      sum -= buffer[currentPositionIndex];
    }
    else{
      //still space left
      length++;
      currentPositionIndex++;
    }

    //Store new value
    buffer[currentPositionIndex]=val;
   }
   
   int getSum(){
    return sum;
   }
   
   int getAverage(){
    return sum / length;
   }

   void calcMinMax(){
    max = -1000;
    min = 1000;
    int i;
    for(i=0;i<length;i++){
      int idx = (currentPositionIndex+i)%size;
      if(buffer[idx] < min){
        min = buffer[idx];
      }
      if(buffer[idx] > max){
        max = buffer[idx];
      }
    }
   }

   int getMin(){
    return min;
   }

   int getMax(){
    return max;
   }

  private:
   int size=0;
   int min=100;
   int max=-100;
   int length=0;
   long sum=0;
   int* buffer;
   int currentPositionIndex=-1;
};

#endif
