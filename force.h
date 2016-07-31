#ifndef FORCE
#define FORCE
class Force
{
        public :
 virtual void turnOn() = 0;
  virtual void turnOff() = 0;
  virtual bool isOn()const = 0;
 virtual  bool isOff() = 0;
 virtual void apply() = 0;
};
#endif // FORCE

