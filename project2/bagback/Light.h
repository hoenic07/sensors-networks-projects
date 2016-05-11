#ifndef LIGHT_H
#define LIGHT_H

class Light { 
public:
  Light();
  ~Light();
  void init();
  double getLumen();
  void update();
private:
  double lumen;
};

#endif
