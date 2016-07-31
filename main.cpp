#include <stdlib.h>
#include <cmath>
#include <iostream>
#include "particlesystem.h"
//#ifdef FREEGLUT
#include <GL/freeglut.h>
#include <GL/glu.h>
//#else
//#include <GL/glut.h>
////#endif
using namespace std;

int xiami = 0;//see loop

int gridSize = 10;
double springStrength = 1.0;
double springDamping = 0.1; //阻尼
double physicsStep = 0.2;
Particle anchor;
//vector<Particle> anchors;
Particle anchors[4];
Particle particles[10][10];
ParticleSystem physics;
//RungeKuttaIntegrator  *rk;

int screenWidth = 400;
int screenHeight = 400;
int height =800 ,width = 600;

double xBoundsMin = 10.0;
double xBoundsMax = screenWidth - 10.0;
double yBoundsMin = 10.0;
double yBoundsMax = screenHeight - 10.0;

void cloth();
void timefunc(int i);
void myDisplay(void);
void setLight();
void reshape(GLsizei w,GLsizei h);
void glInit();
void draw();
double distance(double x1, double y1, double x2, double y2);


int main(int argc,char ** argv)
{
  /*初始化*/
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
  glutInitWindowSize(800,600);
  glutInitWindowPosition(400,400);

  /*创建窗口*/
  glutCreateWindow("cloth");

  /*绘制与显示*/
  glInit();
  glutReshapeFunc(reshape);
//  glutDisplayFunc(myDisplay);
    glutDisplayFunc(draw);
    glutTimerFunc(200, timefunc, 1);

    //在动画循环结束以后可以继续执行之后的代码
//    glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
  glutMainLoop();
//  delete
  return 0;
}


void setLight()
{
  //定义光源属性值
          GLfloat lightAmbient[] = { 0.4, 0.4, 0.4, 1.0 };           //环境光参数
          GLfloat lightDiffuse[] = { 0.1, 0.1, 0.1, 1.0 };           //漫反射光
          GLfloat lightSpecular[] = { 0.9, 0.9, 0.9 ,1.0 };          //镜面光
          GLfloat lightPosition[] = { 0.0, 2.0, 2.0, 1.0 };          //光源位置

          //设置光源属性值
          glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
          glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
          glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
          glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

          //启用光源
          glEnable(GL_LIGHTING);
          glEnable(GL_LIGHT0);
}

void reshape(GLsizei w,GLsizei h)
{
    height = h;
    width = w;
   glViewport(0,0,w,h);//设置视口
   glMatrixMode(GL_PROJECTION);//指明当前矩阵为GL_PROJECTION
   glLoadIdentity();//将当前矩阵置换为单位阵

/*
   if(w <= h)
     gluOrtho2D(-1.0,1.5,-1.5,1.5*(GLfloat)h/(GLfloat)w);//定义二维正视投影矩阵
   else
     gluOrtho2D(-1.0,1.5*(GLfloat)w/(GLfloat)h,-1.5,1.5);
     glMatrixMode(GL_MODELVIEW);//指明当前矩阵为GL_MODELVIEW
     */


     //缺省值时视点是在原点的
     gluPerspective(45.0, (GLfloat)width/(GLfloat)height, 1.0, 4000.0f);
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     gluLookAt(0.0f,0.0f, 1000.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
}

void glInit()
{
  //用户自定的初始化过程
          glClearColor(0.0, 0.0, 0.0, 0.5);
          glClearDepth(1.0);
          glDepthFunc(GL_LEQUAL);                             //如果输入的深度值小于或等于参考值，则通过
          glEnable(GL_DEPTH_TEST);
          glShadeModel(GL_SMOOTH);                           //设置着色模式.采用恒定着色时（即GL_FLAT），使用图元中某个顶点的颜色来渲染整个图元。在使用光滑着色时（即GL_SMOOTH）,对于线段图元，线段上各点的颜色将根据两个顶点的颜色通过插值得到。对于多边形图元，多边形内部区域的颜色将根据所有顶点的颜色插值得到。
          glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);//真正精细的透视修正。这一行告诉OpenGL我们希望进行最好的透视修正。这会十分轻微的影响性能。但使得透视图看起来好一点。
//         ResizeDraw(true);

         //载入纹理
        /* if(!LoadTexture())
                 {
                         cout<<"载入纹理失败"<<endl;
                 }*/
         //设置光源
//                 setLight();
                 //设置相机
//       camera.setCamera(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);

//          gluLookAt(0.0f,0.0f, 6.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
                  cloth();

                  glColor3f(1.0,0.0,0.0);//设置第一个顶点为红色
}

void timefunc(int i)
{
//  physics.tick(physicsStep);
  glutPostRedisplay();
  glutTimerFunc(200, timefunc, 1);
}

void draw()
{
  ++xiami;
  cout<<xiami<<endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//  glClear(GL_COLOR_BUFFER_BIT );
//        glLoadIdentity();
//        gluLookAt(0.0f,0.0f, 600.0f, 0.0f, 0.0f, 0.0f,0.0f, 1.0f, 0.0f);
        /*//画线测试。出现看不到图形的情况就是视点设置与坐标系的问题，导致看不到图。设置要精细。
        glColor3f(0.0, 1.0, 0.0);
        int p1 [] = {1,1};
         int p2 [] = {1, 0};
         int p3 [] = {0,0};
         int p4 [] = {1, 1};
         int p5 [] = {0, 0};
        glBegin(GL_LINES);
              glVertex2iv (p1);
              glVertex2iv (p2);
              glVertex2iv (p3);
              glVertex2iv (p4);
              glVertex2iv (p5);
          glEnd();
          */

        /*
        physics.tick(physicsStep);
        physics.
        physics.advanceTime(physicsStep);//？

	    if (mousePressed)
	    {
		anchor.moveTo(mouseX, mouseY, 0);
		anchor.velocity().clear();//速度，拉动点的速度清除
	    }*/


	    /*for (int i = 0; i < gridSize; i++)//碰到边界
	    {
		for (int j = 0; j < gridSize; j++)
		{
		    Particle p = particles[i][j];
		    float px = p.position().x();
		    float py = p.position().y();
		    float vx = p.velocity().x();
		    float vy = p.velocity().y();

		    if (px < xBoundsMin)
		    {
			vx *= -bounce;
			p.moveTo(xBoundsMin, py, 0);
			p.setVelocity(vx, vy, 0);
		    }
		    else if (px > xBoundsMax)
		    {
			vx *= -bounce;
			p.moveTo(xBoundsMax, py, 0);
			p.setVelocity(vx, vy, 0);
		    }
		    if (py < yBoundsMin)
		    {
			vy *= -bounce;
			p.moveTo(px, yBoundsMin, 0);
			p.setVelocity(vx, vy, 0);
		    }
		    else if (py > yBoundsMax)
		    {
			vy *= -bounce;
			p.moveTo(px, yBoundsMax, 0);
			p.setVelocity(vx, vy, 0);
		    }
		}
	    }
	    */

	physics.tick(physicsStep);
//	glPointSize(5.0);

	    for (int i = 0; i < gridSize; i++)//横线
	    {
		glBegin(GL_LINE_STRIP);
//		glVertex2f(particles[i][0].getPosition().x, particles[i][0].getPosition().y);
		glVertex2f(physics.particles.at(i * 10).position.x, physics.particles.at(i * 10).position.y);
		for (int j = 0; j < gridSize; j++)
		{
//		    glVertex2f(particles[i][j].getPosition().x, particles[i][j].getPosition().y);
		    glVertex2f(physics.particles.at(i * 10 + j).position.x, physics.particles.at(i * 10 + j).position.y);
		}
//		glVertex2f(particles[i][gridSize - 1].getPosition().x, particles[i][gridSize - 1].getPosition().y);
		glVertex2f(physics.particles.at(i * 10 + 9).position.x, physics.particles.at(i * 10 + 9).position.y);
		glEnd();
	    }
	    for (int j = 0; j < gridSize; j++)//竖线
	    {
		glBegin(GL_LINE_STRIP);
//		glVertex2f(particles[0][j].getPosition().x, particles[0][j].getPosition().y);
		glVertex2f(physics.particles.at( j).position.x, physics.particles.at( j).position.y);
		for (int i = 0; i < gridSize; i++)
		{
//		    glVertex2f(particles[i][j].getPosition().x, particles[i][j].getPosition().y);
		    glVertex2f(physics.particles.at(i * 10 + j).position.x, physics.particles.at(i * 10 + j).position.y);
		}
//		glVertex2f(particles[gridSize - 1][j].getPosition().x, particles[gridSize - 1][j].getPosition().y);
		glVertex2f(physics.particles.at(90 + j).position.x, physics.particles.at(90 + j).position.y);
		glEnd();
	    }



	//强制执行所有opengl命令
//	glFlush();
	    glutSwapBuffers();

}

double distance(double x1, double y1, double x2, double y2)
{
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt((dx * dx) + (dy * dy));
}

void cloth()
{
  physics = ParticleSystem(-0.2, 0.005);//gravity and drag.the original are 0.2 & 0.005
  physics.setIntegrator(0);
//  rk = RungeKuttaIntegrator(&physics);
//  physics.integrator = new RungeKuttaIntegrator(&physics);
  double gridStepX = (double) ((width / 2) / gridSize);
  double gridStepY = (double) ((height / 2) / gridSize);

  for (int i = 0; i < gridSize; i++)
  {
      for (int j = 0; j < gridSize; j++)
      {
//          particles[i][j] = physics.makeParticle(0.1, j * gridStepX - (width / 4), i * gridStepY - (height / 4), 0.0);
         particles[i][j] = physics.makeParticle(0.1,-j * gridStepX - (width / 4) + 9 * gridStepX, -i * gridStepY - (height / 4) + 9 * gridStepY , 0.0);
          if (j > 0)
          {
              Particle p1 = particles[i][j - 1];
              Particle p2 = particles[i][j];
              physics.makeSpring(p1, p2, springStrength, springDamping, gridStepY);//力，阻尼，和原长
          }
          if (i > 0)
          {
              Particle p1 = particles[i - 1][j];
              Particle p2 = particles[i][j];
              physics.makeSpring(p1, p2, springStrength, springDamping, gridStepY);
          }
      }
  }

//  particles[0][0].makeFixed();
  physics.particles.at(0).makeFixed();
//  particles[0][gridSize - 1].makeFixed();
  physics.particles.at(9).makeFixed();

  anchors[0] = particles[0][0];
  anchors[1] = particles[0][gridSize - 1];
  anchors[2] = particles[gridSize - 1][0];
  anchors[3] = particles[gridSize - 1][gridSize - 1];


}
