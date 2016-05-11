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
};

#endif
