#ifndef PIEZO_H
#define PIEZO_H

class Piezo { 
public:
  Piezo();
  ~Piezo();
  void init();
  void setActivated(bool isActive);
private:
  bool isActive;
  int cnt = 0;
  int tones[8] = {150, 300, 450, 600, 750, 900, 1100, 1450};
};

#endif
