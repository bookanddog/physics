#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM

#include <particle.h>
#include <rungekuttaintegrator.h>
#include <eulerintegrator.h>
#include <modifiedeulerintegrator.h>
#include <spring.h>
#include <attraction.h>
#include <vector>

//class RungeKuttaIntegrator;
class ParticleSystem
{
	public:
	static const int RUNGE_KUTTA;
	static const int MODIFIED_EULER;

	public:
	static  double DEFAULT_GRAVITY ;
	static double DEFAULT_DRAG ;

public:
  std::vector<Particle> particles;
  std::vector<Spring> springs;
  std::vector<Attraction> attractions;
//  std::vector<> customForces =

//  Integrator integrator;//share i delet it. or  in c++, how to declear a object to a virtual base class which can point to it subclass
  //抽象类，可以定义指向抽象类的指针与引用实现多态
      //引用声明的时候就要初始化，并且不能改变指向的对象
//  Integrator &integrator;//or  Integrator *integrator;
//      Integrator *integrator = NULL;
//  RungeKuttaIntegrator *integrator;
  RungeKuttaIntegrator integrator;

  Vector3 gravity;
  double drag;

  bool hasDeadParticles = false;

  public:
  void setIntegrator( int integ );

  ~ParticleSystem();

  void setGravity( double x, double y, double z );

  // default down gravity
  void setGravity( double g );

  void setDrag( double d );

  void tick();//integrator step;

   void tick( double t );

  Particle makeParticle( double mass, double x, double y, double z );

  Particle makeParticle();

  Spring makeSpring( Particle &a, Particle &b, double ks, double d, double r );

  Attraction makeAttraction( Particle &a, Particle &b, double k, double minDistance );

  void clear();

  ParticleSystem( double g, double somedrag );

  ParticleSystem( double gx, double gy, double gz, double somedrag );

  ParticleSystem();

  void applyForces();

  void clearForces();

  int numberOfParticles();
  int numberOfSprings();

  int numberOfAttractions();

  Particle getParticle( int i );

  Spring getSpring( int i );

  Attraction getAttraction( int i );

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

  void removeParticle( Particle &p );

  Spring removeSpring( int i );

  Attraction removeAttraction( int i  );

  void removeAttraction( Attraction &s );

  void removeSpring( Spring &a );

//  void removeCustomForce( Force &f )
//  {
//    customForces.erase(std::remove(customForces.begin(), customForces.end(), f), customForces.end());
////          customForces.remove( f );
//  }

};

#endif // PARTICLESYSTEM

