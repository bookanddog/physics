#include"modifiedeulerintegrator.h"



	ModifiedEulerIntegrator::ModifiedEulerIntegrator( ParticleSystem *s )
	{
		this->s = s;
	}

	void ModifiedEulerIntegrator::step( double t )
	{
		s->clearForces();
		s->applyForces();

		double halftt = 0.5*t*t;

		for ( int i = 0; i < s->numberOfParticles(); i++ )
		{
			Particle p = s->getParticle( i );
			if ( p.isFree() )
			{
				double ax = p.getForce().x/p.getMass();
				double ay = p.getForce().y/p.getMass();
				double az = p.getForce().z/p.getMass();

				p.position.add( p.getVelocity().x/t, p.getVelocity().y/t, p.getVelocity().z/t );
				p.position.add( ax*halftt, ay*halftt, az*halftt );
				p.velocity.add( ax/t, ay/t, az/t );
			}
		}
	}



