#include"vector3.h"

    Vector3::Vector3(double X,double Y,double Z):x(X), y(Y), z(Z){}
    Vector3::Vector3():x(0), y(0), z(0){}
    Vector3::Vector3(const Vector3 &p){ x = p.x; y = p.y; z = p.z; }
//    ~Vector3(){}

   double Vector3::getz()
   {
     return z;
   }
   double Vector3::gety(){ return y; }
   double Vector3::getx() { return x; }
    void Vector3::setX(double X){ x = X; }
    void Vector3::setY(double Y)         			{ y = Y; }
    void Vector3::setZ(double Z )				{ z = Z; }
    void Vector3::set(double X,double Y,double Z )	{ x = X; y = Y; z = Z; }
    void Vector3::set( Vector3 &p )	{ x = p.x; y = p.y; z = p.z; }
    void Vector3::add( Vector3 &p ){ x += p.x; y += p.y; z += p.z; }
    void Vector3::subtract( Vector3 &p ){ x -= p.x; y -= p.y; z -= p.z; }
    void Vector3::add(double a,double b,double c ){ x += a; y += b; z += c; }
    void Vector3::subtract(double a,double b,double c ){ x -= a; y -= b; z -= c; }
    Vector3 Vector3::multiplyBy(double f ) { x *= f; y *= f; z*= f; return *this; }
   double Vector3::distanceTo(const Vector3 &p )  { return sqrt( distanceSquaredTo( p ) ); }
   double Vector3::distanceSquaredTo(const Vector3 &p )		{double dx = x-p.x;double dy = y-p.y;double dz = z-p.z; return dx*dx + dy*dy + dz*dz; }

   double Vector3::distanceTo(double x,double y,double z )
           {
                   double dx = this->x - x;
                   double dy = this->y - y;
                   double dz = this->z - z;
                   return sqrt( dx*dx + dy*dy + dz*dz );
           }

   double Vector3::dot( Vector3 &p )         			{ return x*p.x + y*p.y + z*p.z; }
    double Vector3::length()                 			{ return sqrt( x*x + y*y + z*z ); }
    double Vector3::lengthSquared()				{ return x*x + y*y + z*z; }

    void Vector3::clear()                   		{ x = 0; y = 0; z = 0; }

//   string toString()              		{ return new string( "(" + x + ", " + y + ", " + z + ")" ); }

    Vector3 Vector3::cross( Vector3 &p )
           {
                   return Vector3(y*p.z - z*p.y, x*p.z - z*p.x, x*p.y - y*p.x);
           }

           bool Vector3::isZero()
           {
                   return x == 0 && y == 0 && z == 0;
           }
