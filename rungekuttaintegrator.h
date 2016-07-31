#ifndef RUNGEKUTTAINTEGRATOR
#define RUNGEKUTTAINTEGRATOR

#include <integrator.h>
//#include <particlesystem.h>
#include <vector>
#include"vector3.h"

class ParticleSystem;
//四阶龙格库塔法
class RungeKuttaIntegrator:virtual public Integrator
{
	public:
	std::vector<Vector3> originalPositions;
	std::vector<Vector3> originalVelocities;
	std::vector<Vector3> k1Forces;
	std::vector<Vector3> k1Velocities;
	std::vector<Vector3> k2Forces;
	std::vector<Vector3> k2Velocities;
	std::vector<Vector3> k3Forces;
	std::vector<Vector3> k3Velocities;
	std::vector<Vector3> k4Forces;
	std::vector<Vector3> k4Velocities;

	ParticleSystem *s;

	public:
//	RungeKuttaIntegrator( ParticleSystem &s );
	RungeKuttaIntegrator(ParticleSystem *s );
	RungeKuttaIntegrator();
	~RungeKuttaIntegrator();

	//貌似有点多余
	void allocateParticles();

	void step( double deltaT );
};

#endif // RUNGEKUTTAINTEGRATOR

