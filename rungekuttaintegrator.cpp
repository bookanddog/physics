
//#include"rungekuttaintegrator.h"
#include"particlesystem.h"


//四阶龙格库塔法

/*
	RungeKuttaIntegrator::RungeKuttaIntegrator(ParticleSystem &s )
	{
		this->s = &s;

//		originalPositions = new ArrayList();
//		originalVelocities = new ArrayList();
//		k1Forces = new ArrayList();
//		k1Velocities = new ArrayList();
//		k2Forces = new ArrayList();
//		k2Velocities = new ArrayList();
//		k3Forces = new ArrayList();
//		k3Velocities = new ArrayList();
//		k4Forces = new ArrayList();
//		k4Velocities = new ArrayList();
	}
	*/

	RungeKuttaIntegrator::RungeKuttaIntegrator(ParticleSystem *s )
	{
	  this->s = s;
	}

	RungeKuttaIntegrator::RungeKuttaIntegrator()
	{
	  this->s = NULL;
	}

	RungeKuttaIntegrator::~RungeKuttaIntegrator()
	{

	}
	//貌似有点多余
	void RungeKuttaIntegrator::allocateParticles()
	{
//		while ( s.particles.size() > originalPositions.size() )
		while( s->particles.size() > originalPositions.size() )
		{
//		  originalPositions.reserve(s->particles.size());
//		  originalVelocities.reserve(s->particles.size());
//		  k1Forces.reserve(s->particles.size());
//		  k1Velocities.reserve(s->particles.size());
//		  k2Forces.reserve(s->particles.size());
//		  k2Velocities.reserve(s->particles.size());
//		  k3Forces.reserve(s->particles.size());
//		  k3Velocities.reserve(s->particles.size());
//		  k4Forces.reserve(s->particles.size());
//		  k4Velocities.reserve(s->particles.size());

			originalPositions.push_back(Vector3() );
			originalVelocities.push_back( Vector3() );
			k1Forces.push_back( Vector3() );
			k1Velocities.push_back( Vector3() );
			k2Forces.push_back( Vector3() );
			k2Velocities.push_back( Vector3() );
			k3Forces.push_back( Vector3() );
			k3Velocities.push_back( Vector3() );
			k4Forces.push_back( Vector3() );
			k4Velocities.push_back( Vector3() );
		}
	}

	void RungeKuttaIntegrator::step( double deltaT )
	{
		allocateParticles();
		/////////////////////////////////////////////////////////
		// save original position and velocities

		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
//				originalPositions.at( i ).set( p.position );
			    originalPositions.at( i ) = p.position ;
			    //or
			   //originalPositions.push_back( p.position) ;
//				((Vector3)originalVelocities.get( i )).set( p.velocity );
			    originalVelocities.at(i) = p.velocity;
			}

//			p.force.clear();	// and clear the forces
			s->particles.at(i).force.clear();
		}

		////////////////////////////////////////////////////////
		// get all the k1 values

		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				k1Forces.at(i) = p.force ;
				k1Velocities.at(i) = p.velocity;
			}

//			p.force.clear();
			s->particles.at(i).force.clear();
		}

		////////////////////////////////////////////////////////////////
		// get k2 values

		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				Vector3 originalPosition =originalPositions.at( i );
				Vector3 k1Velocity = k1Velocities.at( i );

				p.position.x = originalPosition.x + k1Velocity.x * 0.5 * deltaT;
				p.position.y = originalPosition.y + k1Velocity.y * 0.5 * deltaT;
				p.position.z = originalPosition.z + k1Velocity.z * 0.5 * deltaT;

				Vector3 originalVelocity = originalVelocities.at( i );
				Vector3 k1Force = k1Forces.at( i );

				p.velocity.x = originalVelocity.x + k1Force.x * 0.5 * deltaT / p.mass;
				p.velocity.y = originalVelocity.y + k1Force.y * 0.5 * deltaT / p.mass;
				p.velocity.z = originalVelocity.z + k1Force.z * 0.5 * deltaT / p.mass;
				s->particles.at(i) = p;
			}
		}

		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				k2Forces.at(i) =  p.force ;
				k2Velocities.at(i) = p.velocity ;
			}

//			p.force.clear();	// and clear the forces now that we are done with them
			s->particles.at(i).force.clear();
		}


		/////////////////////////////////////////////////////
		// get k3 values

		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				Vector3 originalPosition = originalPositions.at( i );
				Vector3 k2Velocity = k2Velocities.at( i );

				p.position.x = originalPosition.x + k2Velocity.x * 0.5 * deltaT;
				p.position.y = originalPosition.y + k2Velocity.y * 0.5 * deltaT;
				p.position.z = originalPosition.z + k2Velocity.z * 0.5 * deltaT;

				Vector3 originalVelocity = originalVelocities.at( i );
				Vector3 k2Force = k2Forces.at( i );

				p.velocity.x = originalVelocity.x + k2Force.x * 0.5 * deltaT / p.mass;
				p.velocity.y = originalVelocity.y + k2Force.y * 0.5 * deltaT / p.mass;
				p.velocity.z = originalVelocity.z + k2Force.z * 0.5 * deltaT / p.mass;
				s->particles.at(i) = p;
			}
		}

		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				k3Forces.at(i) = p.force ;
				k3Velocities.at(i) =  p.velocity ;
			}

//			p.force.clear();	// and clear the forces now that we are done with them
			s->particles.at(i).force.clear();
		}


		//////////////////////////////////////////////////
		// get k4 values

		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				Vector3 originalPosition = originalPositions.at( i );
				Vector3 k3Velocity = k3Velocities.at( i );

				p.position.x = originalPosition.x + k3Velocity.x * deltaT;
				p.position.y = originalPosition.y + k3Velocity.y * deltaT;
				p.position.z = originalPosition.z + k3Velocity.z * deltaT;

				Vector3 originalVelocity = originalVelocities.at( i );
				Vector3 k3Force = k3Forces.at( i );

				p.velocity.x = originalVelocity.x + k3Force.x * deltaT / p.mass;
				p.velocity.y = originalVelocity.y + k3Force.y * deltaT / p.mass;
				p.velocity.z = originalVelocity.z + k3Force.z * deltaT / p.mass;

				s->particles.at(i) = p;
			}
		}

		s->applyForces();

		// save the intermediate forces
		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			if ( p.isFree() )
			{
				k4Forces.at(i) = p.force ;
				k4Velocities.at(i) = p.velocity ;
			}
		}

		/////////////////////////////////////////////////////////////
		// put them all together and what do you get?

		for ( int i = 0; i < s->particles.size(); ++i )
		{
			Particle p = s->particles.at( i );
			p.age += deltaT;
			if ( p.isFree() )
			{
				// update position

				Vector3 originalPosition = originalPositions.at( i );
				Vector3 k1Velocity = k1Velocities.at( i );
				Vector3 k2Velocity = k2Velocities.at( i );
				Vector3 k3Velocity = k3Velocities.at( i );
				Vector3 k4Velocity = k4Velocities.at( i );

				p.position.x = originalPosition.x + deltaT / 6.0 * ( k1Velocity.x + 2.0*k2Velocity.x + 2.0*k3Velocity.x + k4Velocity.x );
				p.position.y = originalPosition.y + deltaT / 6.0 * ( k1Velocity.y + 2.0*k2Velocity.y + 2.0*k3Velocity.y + k4Velocity.y );
				p.position.z = originalPosition.z + deltaT / 6.0 * ( k1Velocity.z + 2.0*k2Velocity.z + 2.0*k3Velocity.z + k4Velocity.z );

				// update velocity

				Vector3 originalVelocity = originalVelocities.at( i );
				Vector3 k1Force = k1Forces.at( i );
				Vector3 k2Force = k2Forces.at( i );
				Vector3 k3Force = k3Forces.at( i );
				Vector3 k4Force = k4Forces.at( i );

				p.velocity.x = originalVelocity.x + deltaT / ( 6.0 * p.mass ) * ( k1Force.x + 2.0*k2Force.x + 2.0*k3Force.x + k4Force.x );
				p.velocity.y = originalVelocity.y + deltaT / ( 6.0 * p.mass ) * ( k1Force.y + 2.0*k2Force.y + 2.0*k3Force.y + k4Force.y );
				p.velocity.z = originalVelocity.z + deltaT / ( 6.0 * p.mass ) * ( k1Force.z + 2.0*k2Force.z + 2.0*k3Force.z + k4Force.z );

				s->particles.at(i) = p;
			}
		}
	}



