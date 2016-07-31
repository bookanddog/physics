#include"eulerintegrator.h"




	EulerIntegrator::EulerIntegrator( ParticleSystem *s )
	{
		this->s = s;
	}
//	EulerIntegrator(){}

	void EulerIntegrator::step( double t )
	{
		s->clearForces();
		s->applyForces();

		for ( int i = 0; i < s->numberOfParticles(); i++ )
		{
			Particle p = s->getParticle( i );
			if ( p.isFree() )
			{
				p.velocity.add( p.getForce().x/(p.getMass()*t), p.getForce().y/(p.getMass()*t), p.getForce().z/(p.getMass()*t) );
				//计算位置不应该是用乘法吗，速度乘于步长时间
				p.position.add( p.getVelocity().x/t, p.getVelocity().y/t, p.getVelocity().z/t );
			}
		}
	}



