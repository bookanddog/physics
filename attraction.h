//引力计算，取一个最小距离。原理
#ifndef ATTRACTION
#define ATTRACTION

#include <particle.h>
#include <force.h>

class Attraction : virtual public  Force//引力
{
public:
  int id;
  public:
        Particle a;
        Particle b;
        double k; //Strength
        bool on;
        double distanceMin;
        double distanceMinSquared;

	public:
	Attraction( Particle &a, Particle &b, double k, double distanceMin );
	Attraction();
	Attraction( const Attraction &attrc);

	bool operator == (const Attraction &x)
	{
	  return this->id == x.id ;
	}
//	protected:
	void setA( Particle &p );

	void setB( Particle &p );

	 double getMinimumDistance()const;

	void setMinimumDistance( double d );

	void turnOff();

	void turnOn();
	 void setStrength( double k );

	Particle getOneEnd() const;

	Particle getTheOtherEnd() const;

	void apply();

	double getStrength() const;

	bool isOn()const;

	bool isOff();
};

#endif // ATTRACTION

