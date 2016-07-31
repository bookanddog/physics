#ifndef SPRING
#define SPRING

//计算弹簧力的时候好像有问题，总是一个定值不变。
//带改动 ，心理憔悴
#include <particle.h>
#include <force.h>

class Spring : virtual public Force
{
public:
  int id;
  public:
  double springConstant;
  double damping;
  double restLength;
  Particle a, b;
  bool on;

  public:
  Spring(Particle &A, Particle &B,   double ks, double d,  double r,  bool On = true);
  Spring();
  Spring(const Spring &s);
//  ~Spring(){}
  bool operator == (const Spring &x)
  {
    return this->id == x.id ;
  }

  void turnOff();

 void turnOn() ;

  bool isOn() const;

  bool isOff();

  Particle getOneEnd()const;

  Particle getTheOtherEnd()const;

  double currentLength();

  double getRestLength() const;

  double strength ()const;

  void setStrength( double ks );

  double getDamping() const;

  void setDamping( double d );

  void setRestLength( double l );

  void apply();

  void setA( Particle &p );

  void setB( Particle &p );
};

#endif // SPRING

