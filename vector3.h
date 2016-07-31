#ifndef VECTOR3
#define VECTOR3

#include <math.h>
#include <string>

class Vector3
{
public:
 double x;
 double y;
 double z;

 public:
//    Vector3(double X,double Y,double Z):x(X), y(Y), z(Z){}
//    Vector3():x(0), y(0), z(0){}
//    Vector3(Vector3 &p){ x = p.x; y = p.y; z = p.z; }
 Vector3(double X,double Y,double Z);
 Vector3();
Vector3(const Vector3 &p);
//    ~Vector3(){}

   double getz();
   double gety();
   double getx() ;
    void setX(double X);
    void setY(double Y) ;
    void setZ(double Z );
    void set(double X,double Y,double Z );
    void set( Vector3 &p );
    void add( Vector3 &p );
    void subtract( Vector3 &p );
    void add(double a,double b,double c );
    void subtract(double a,double b,double c );
    Vector3 multiplyBy(double f ) ;
   double distanceTo(const  Vector3 &p );
   double distanceSquaredTo( const Vector3 &p )	;

   double distanceTo(double x,double y,double z );

   double dot( Vector3 &p ) ;
    double length() ;
    double lengthSquared();

    void clear() ;

//   string toString()              		{ return new string( "(" + x + ", " + y + ", " + z + ")" ); }

       Vector3 cross( Vector3 &p );

           bool isZero();

};


#endif // Vector3

