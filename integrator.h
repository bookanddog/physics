#ifndef INTEGRATOR
#define INTEGRATOR

class Integrator
{
	public:
	virtual ~Integrator(){}
	virtual void step(double t) = 0;
};

#endif // INTEGRATOR

