#ifndef PARTICLE
#define PARTICLE

#include <vector3.h>
class Particle
{
  public :
  int  id;
  Vector3 position;
  Vector3 velocity;
  Vector3 force;
  double mass;
  double age;
  bool dead;

  bool fixed;

  public:
  Particle( double m );
  Particle();
  Particle(const Particle &p);

  //overload ==operate to find this object
bool operator == (const Particle &x)
{
  return this->id == x.id ;
}

double distanceTo( Particle &p );

 void makeFixed();

 bool isFixed()const;


bool isFree();

void makeFree();

 Vector3 getPosition() const;
void setPosition(const Vector3 &p);
void setPosition(double x, double y, double z);

 Vector3 getVelocity()const;
 void setVelocity(const Vector3 &p);
 void setVelocity(double x, double y, double z);

double getMass()const;

void setMass( double m );

Vector3 getForce()const;
void setForce(const Vector3 &p);
void setForce(double x, double y, double z);

double getAge()const;
void setAge(double p);


 void reset();
};
#endif // PARTICLE

