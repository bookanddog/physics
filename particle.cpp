
#include"particle.h"

  Particle::Particle( double m )
  {
//	  position = Vector3();
//	  velocity =  Vector3();
//	  force =  Vector3();
    id = -1;
	  mass = m;
	  fixed = false;
	  age = 0.0;
	  dead = false;
  }
  Particle::Particle()
  {
//    position = Vector3();
//    velocity =  Vector3();
//    force =  Vector3();
    id = -1;
    mass = 0.0;
    fixed = false;
    age = 0.0;
    dead = false;
  }
  Particle::Particle(const Particle &p)
  {
    id = p.id;// see attraction class.some problems  to  be solved
    position = p.getPosition();
    velocity =  p.getVelocity();
    force =  p.getForce();
    mass = p.getMass();
    fixed = p.isFixed();
    age = p.getAge();
    dead = false;//useless sofar .default
  }

double Particle::distanceTo( Particle &p )
  {
          return this->getPosition().distanceTo( p.getPosition() );
  }

 void Particle::makeFixed()
  {
          fixed = true;
          velocity.clear();
  }

 bool Particle::isFixed() const
  {
          return fixed;
  }


bool Particle::isFree()
  {
          return !fixed;
  }


void Particle::makeFree()
  {
          fixed = false;
  }

 Vector3 Particle::getPosition()const
  {
          return position;
  }
void Particle::setPosition(const Vector3 &p)
{
  position = p;
}
void Particle::setPosition(double x, double y, double z)
{
  position.x = x;
  position.y = y;
  position.z = z;
}

 Vector3 Particle::getVelocity()const
  {
          return velocity;
  }
 void Particle::setVelocity(const Vector3 &p)
 {
   velocity = p;
 }
 void Particle::setVelocity(double x, double y, double z)
 {
   velocity.x = x;
   velocity.y = y;
   velocity.z = z;
 }

double Particle::getMass()const
  {
          return mass;
  }

void Particle::setMass( double m )
  {
          mass = m;
  }

Vector3 Particle::getForce()const
  {
  return force;
}

void Particle::setForce(const Vector3 &p)
{
  force = p;
}

void Particle::setForce(double x, double y, double z)
{
  force.x = x;
  force.y = y;
  force.z = z;
}

double Particle::getAge()const
  {
  return age;
}

void Particle::setAge(double p)
{
  age = p;
}

 void Particle::reset()
  {
          age = 0.0;
          dead = false;
          position.clear();
          velocity.clear();
          force.clear();
          mass = 1.0;
  }

