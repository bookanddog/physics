
#include"attraction.h"

	Attraction::Attraction( Particle &a, Particle &b, double k, double distanceMin ):a(a), b(b), k(k), distanceMin(distanceMin)
	{
	  id = -1;
		on = true;
		this->distanceMinSquared = distanceMin*distanceMin;
	}
	Attraction::Attraction()
	{
	  id = -1;
	  k = 0.0;
	  on = true;
	  distanceMin = 0.0;
	  distanceMinSquared = 0.0;
	}
	Attraction::Attraction( const Attraction &attrc)
	{
	  id = attrc.id;//copy func.  It may be better that id still is -1. Now i  just  leave it  to be tested. spring and particle are the same . to be done.
	  a = attrc.getOneEnd();
	  b = attrc.getTheOtherEnd();
	  k = attrc.getStrength();
	  on = attrc.isOn();
	  distanceMin = attrc.getMinimumDistance();
	  distanceMinSquared = distanceMin * distanceMin;
	}

//	protected:
	void Attraction::setA( Particle &p )
	{
		a = p;
	}

	void Attraction::setB( Particle &p )
	{
		b = p;
	}

	 double Attraction::getMinimumDistance()const
	{
		return distanceMin;
	}

	void Attraction::setMinimumDistance( double d )
	{
		distanceMin = d;
		distanceMinSquared = d*d;
	}

	void Attraction::turnOff()
	{
		on = false;
	}

	void Attraction::turnOn()
	{
		on = true;
	}

	 void Attraction::setStrength( double k )
	{
		this->k = k;
	}

	Particle Attraction::getOneEnd()const
	{
		return a;
	}

	Particle Attraction::getTheOtherEnd()const
	{
		return b;
	}

	void Attraction::apply()
	{
		if ( on && ( a.isFree() || b.isFree() ) )
		{
			double a2bX = a.getPosition().x - b.getPosition().x;
			double a2bY = a.getPosition().y - b.getPosition().y;
			double a2bZ = a.getPosition().z - b.getPosition().z;

			double a2bDistanceSquared = a2bX*a2bX + a2bY*a2bY + a2bZ*a2bZ;

			if ( a2bDistanceSquared < distanceMinSquared )
				a2bDistanceSquared = distanceMinSquared;

			//计算弹簧之间的力，但是不科学，先进行约束使之>=mindistance之后才进行计算。并且计算还加入了两个质点质量？计算公式貌似也不科学f=k*a.mass * b.mass/a2bdist^2
			//计算的是引力。。。不是说好的弹簧么。而且引力为什么设置最小值。
			double force = k * a.getMass() * b.getMass() / a2bDistanceSquared;

			double length = sqrt( a2bDistanceSquared );

			// make unit vector/

			a2bX /= length;
			a2bY /= length;
			a2bZ /= length;

			// multiply by force

			a2bX *= force;
			a2bY *= force;
			a2bZ *= force;

			// apply

			if ( a.isFree() )
				a.force.add( -a2bX, -a2bY, -a2bZ );
			if ( b.isFree() )
				b.force.add( a2bX, a2bY, a2bZ );
		}
	}

	double Attraction::getStrength()const
	{
		return k;
	}

	bool Attraction::isOn() const
	{
		return on;
	}

	bool Attraction::isOff()
	{
		return !on;
	}
