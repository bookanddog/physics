//计算位置的时候好像有问题。。。。
#ifndef EULERINTEGRATOR
#define EULERINTEGRATOR

#include <integrator.h>
#include <particlesystem.h>

class ParticleSystem;
class EulerIntegrator : virtual public Integrator
{
  public:
        ParticleSystem *s;

	public:
	EulerIntegrator( ParticleSystem *s );
//	EulerIntegrator(){}
	~EulerIntegrator()
	{
//	  if(s != NULL)
//	    {
//	      delete s;
//	      s = NULL;
//	      }
	  }

	void step( double t );
};

#endif // EULERINTEGRATOR

