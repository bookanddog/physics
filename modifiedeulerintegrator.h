//同样的，计算位置使，用速度/时间步长而不是乘于
#ifndef MODIFIEDEULERINTEGRATOR
#define MODIFIEDEULERINTEGRATOR

#include <integrator.h>
#include <particlesystem.h>

class ParticleSystem;
class ModifiedEulerIntegrator :virtual public Integrator
{
	public:
	ParticleSystem *s;

	public:
	ModifiedEulerIntegrator(ParticleSystem *s );
	~ModifiedEulerIntegrator()
	{}
	void step( double t );

};

#endif // MODIFIEDEULERINTEGRATOR

