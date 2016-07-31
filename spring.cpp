#include"spring.h"

 Spring::Spring(Particle &A, Particle &B,   double ks, double d,  double r,  bool On ):springConstant(ks), damping(d), restLength(r), a(A), b(B), on(On){id = -1;}

  Spring::Spring()
  {
    id = -1;
    springConstant = 0.0;
    damping = 0.0;
    restLength = 0.0;
    on = true;
  }
  Spring::Spring(const Spring &s)
  {
    id = s.id;// see attraction class.some problems  to  be solved
    springConstant = s.strength();
    damping = s.getDamping();
    restLength = s.getRestLength();
    a = s.getOneEnd();
    b = s.getTheOtherEnd();
    on = s.isOn();
  }
//  ~Spring(){}

  void Spring::turnOff()
  {
          on = false;
  }

 void Spring::turnOn()
  {
          on = true;
  }

  bool Spring::isOn()const
  {
          return on;
  }

  bool Spring::isOff()
  {
          return !on;
  }

  Particle Spring::getOneEnd()const
  {
          return a;
  }

  Particle Spring::getTheOtherEnd()const
  {
          return b;
  }

  double Spring::currentLength()
  {
          return a.getPosition().distanceTo( b.getPosition() );
  }

  double Spring::getRestLength()const
  {
          return restLength;
  }

  double Spring::strength () const
  {
          return Spring::springConstant;
  }

  void Spring::setStrength( double ks )
  {
          springConstant = ks;
  }

  double Spring::getDamping()const
  {
          return damping;
  }

  void Spring::setDamping( double d )
  {
          damping = d;
  }

  void Spring::setRestLength( double l )
  {
          restLength = l;
  }

  void Spring::apply()
  {
        if ( on && ( a.isFree() || b.isFree() ) )
        {
                double a2bX = a.getPosition().x - b.getPosition().x;
                double a2bY = a.getPosition().y - b.getPosition().y;
                double a2bZ = a.getPosition().z - b.getPosition().z;

                double a2bDistance = sqrt( a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ );

		if ( a2bDistance == 0 )
		{
			a2bX = 0;
			a2bY = 0;
			a2bZ = 0;
		}
		else
		{
			a2bX /= a2bDistance;
			a2bY /= a2bDistance;
			a2bZ /= a2bDistance;
		}


		// spring force is proportional to how much it stretched

		double springForce = -( a2bDistance - restLength ) * springConstant;


		// want velocity along line b/w a & b, damping force is proportional to this

		double Va2bX = a.getVelocity().x - b.getVelocity().x;
		double Va2bY = a.getVelocity().y - b.getVelocity().y;
		double Va2bZ = a.getVelocity().z - b.getVelocity().z;
		// dampingForce = -damping * (b.position - a.position).normal点积(b.velocity - a.velocity)
				//什么原理的公式？阻尼力怎么还与位置有关.其实是单位向量，使速度投影到ab向量上。
		double dampingForce = -damping * ( a2bX*Va2bX + a2bY*Va2bY + a2bZ*Va2bZ );


		// forceB is same as forceA in opposite direction

		double r = springForce + dampingForce;

		a2bX *= r;
		a2bY *= r;
		a2bZ *= r;

		if ( a.isFree() )
			a.force.add( a2bX, a2bY, a2bZ );
		if ( b.isFree() )
			b.force.add( -a2bX, -a2bY, -a2bZ );
	}
  }

  void Spring::setA( Particle &p )
  {
          a = p;
  }

  void Spring::setB( Particle &p )
  {
          b = p;
  }



