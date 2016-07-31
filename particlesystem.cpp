#include"particlesystem.h"
#include <algorithm>
#include<iostream>

int const ParticleSystem::RUNGE_KUTTA = 0;
 int const ParticleSystem::MODIFIED_EULER = 1;


double  ParticleSystem::DEFAULT_GRAVITY = 0.0;
 double  ParticleSystem::DEFAULT_DRAG = 0.001;

 ParticleSystem::ParticleSystem( double g, double somedrag )
 {
//    RungeKuttaIntegrator rk = RungeKuttaIntegrator(this);
//        integrator = &rk;
//       integrator = RungeKuttaIntegrator(this);
//    particles = new ArrayList();
//    springs = new ArrayList();
//    attractions = new ArrayList();
   gravity = Vector3( 0, g, 0 );
   drag = somedrag;
 }

 ParticleSystem::ParticleSystem( double gx, double gy, double gz, double somedrag )
 {
//    RungeKuttaIntegrator rk = RungeKuttaIntegrator(this);
//        integrator = &rk;
//   integrator = RungeKuttaIntegrator(this);
//    particles = new ArrayList();
//    springs = new ArrayList();
//    attractions = new ArrayList();
   gravity = Vector3( gx, gy, gz );
   drag = somedrag;
 }

 ParticleSystem::ParticleSystem()
 {
//    RungeKuttaIntegrator rk = RungeKuttaIntegrator(this);
//        integrator = &rk;
//   integrator =  RungeKuttaIntegrator(this);
//	particles = new ArrayList();
//	springs = new ArrayList();
//	attractions = new ArrayList();
       gravity = Vector3( 0, DEFAULT_GRAVITY, 0 );
       drag = DEFAULT_DRAG;
 }

 ParticleSystem::~ParticleSystem()
 {
   std::cout<<"jimi";
//    if(integrator != NULL)
//      {
//        delete integrator;
//        integrator = NULL;
//      }
 }

  void ParticleSystem::setIntegrator( int integ )
  {
        switch ( integ )
        {
                case RUNGE_KUTTA:
            {
//                        RungeKuttaIntegrator rk = RungeKuttaIntegrator(this);
//                        integrator =  &rk;
                        integrator = RungeKuttaIntegrator(this);
                        break;
                        }
                case MODIFIED_EULER:
            {
//                        ModifiedEulerIntegrator me = ModifiedEulerIntegrator(this);
//                        integrator = &me;
//                        integrator = ModifiedEulerIntegrator(this);
                        break;
                        }
        }
  }


  void ParticleSystem::setGravity( double x, double y, double z )
  {
          gravity.set( x, y, z );
  }

  // default down gravity
  void ParticleSystem::setGravity( double g )
  {
          gravity.set( 0, g, 0 );
  }

  void ParticleSystem::setDrag( double d )
  {
          drag = d;
  }

  void ParticleSystem::tick()//integrator step
  {
          tick( 1 );
  }

   void ParticleSystem::tick( double t )
  {
//          *integrator.step( t );
     integrator.step(t);
  }

  Particle ParticleSystem::makeParticle( double mass, double x, double y, double z )
  {
          Particle p = Particle( mass );
          p.setPosition(x, y, z);
          p.id = particles.size();
          particles.push_back( p );
          return p;
  }

  Particle ParticleSystem::makeParticle()
  {
          return makeParticle( 1.0, 0.0, 0.0, 0.0 );
  }

  Spring ParticleSystem::makeSpring( Particle &a, Particle &b, double ks, double d, double r )
  {
          Spring s = Spring( a, b, ks, d, r );
          s.id = springs.size();
          springs.push_back( s );
          return s;
  }

  Attraction ParticleSystem::makeAttraction( Particle &a, Particle &b, double k, double minDistance )
  {
          Attraction m = Attraction( a, b, k, minDistance );
          m.id = attractions.size();
          attractions.push_back( m );
          return m;
  }

  void ParticleSystem::clear()
  {
          particles.clear();
          springs.clear();
          attractions.clear();
  }




  void ParticleSystem::applyForces()
  {
          if ( !gravity.isZero() )//gravity force if have
          {
                  for ( int i = 0; i < particles.size(); ++i )
                  {
                          Particle p = particles.at( i );
                          p.force.add( gravity );
                          particles.at(i) = p;
                  }
          }

	  for ( int i = 0; i < particles.size(); ++i )//运动阻尼，小量，默认0.001
	  {
		  Particle p = particles.at( i );
		  p.force.add( p.getVelocity().x * -drag, p.getVelocity().y * -drag, p.getVelocity().z * -drag );
		  particles.at(i) = p;
	  }

	  for ( int i = 0; i < springs.size(); i++ )//add  spring  force
	  {
		  Spring f = springs.at( i );
		  f.apply();
		  springs.at(i) = f;
	  }

	  for ( int i = 0; i < attractions.size(); i++ )//add attraction force
	  {
		  Attraction f = attractions.at( i );
		  f.apply();
		  attractions.at(i) = f;
	  }

//	  for ( int i = 0; i < customForces.size(); i++ )//it's abstract class.and there must be some problems
//	  {
//		  Force f = customForces.at( i );
//		  f.apply();
//	  }
  }

  void ParticleSystem::clearForces()
  {
          std::vector<Particle>::iterator i = particles.begin();
          while ( i != particles.end())
          {
              i->force.clear();
//                  i->getForce().clear();
              ++i;
          }
  }

  int ParticleSystem::numberOfParticles()
  {
          return particles.size();
  }

  int ParticleSystem::numberOfSprings()
  {
          return springs.size();
  }

  int ParticleSystem::numberOfAttractions()
  {
          return attractions.size();
  }

  Particle ParticleSystem::getParticle( int i )
  {
          return particles.at( i );
  }

  Spring ParticleSystem::getSpring( int i )
  {
          return springs.at( i );
  }

  Attraction ParticleSystem::getAttraction( int i )
  {
          return attractions.at( i );
  }

//  void addCustomForce( Force &f )//add customforce,error
//  {
//          customForces.push_back( f );
//  }

// int numberOfCustomForces()
//  {
//          return customForces.size();
//  }

//  Force getCustomForce( int i )//customforces,still error
//  {
//          return customForces.at( i );
//  }

//  Force removeCustomForce( int i )//still error
//  {

//          return customForces.remove( i );
//  }

  void ParticleSystem::removeParticle( Particle &p )
  {
    particles.erase(std::find(particles.begin(), particles.end(), p));
//          particles.remove( p );
  }

  Spring ParticleSystem::removeSpring( int i )
  {
    std::vector<Spring>::iterator iter;
    int j = 0;
    Spring s ;
    for(iter = springs.begin(); iter != springs.end();++iter)
      {
        if(j == i)
          {
            s = *iter;
            springs.erase(iter);
            break;
          }
      }
    return s;
//          return (Spring)springs.remove( i );
  }

  Attraction ParticleSystem::removeAttraction( int i  )
  {
    std::vector<Attraction>::iterator iter;
    int j = 0;
    Attraction s ;
    for(iter = attractions.begin(); iter != attractions.end();++iter)
      {
        if(j == i)
          {
            s = *iter;
            attractions.erase(iter);
            break;
          }
      }
    return s;
//         return (Attraction)attractions.remove( i );
  }

  void ParticleSystem::removeAttraction( Attraction &s )
  {
//    attractions.erase(std::remove(attractions.begin(), attractions.end(), s), attractions.end());
    attractions.erase(std::find(attractions.begin(), attractions.end(), s));
//          attractions.remove( s );
  }

  //从spring容器中找到指定spring a方法，应该得重载。此处暂不考虑
  void ParticleSystem::removeSpring( Spring &a )
  {
    springs.erase(std::find(springs.begin(), springs.end(), a));
//          springs.remove( a );
  }

//  void removeCustomForce( Force &f )
//  {
//    customForces.erase(std::remove(customForces.begin(), customForces.end(), f), customForces.end());
////          customForces.remove( f );
//  }


