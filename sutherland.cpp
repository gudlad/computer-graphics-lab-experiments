#include<GL/glut.h>
#include<stdio.h>
#include<stdbool.h>
#define outcode int

float x0,y0,x1,y1;
float xmin,ymin,xmax,ymax;
double xvmin=200,yvmin=200,xvmax=300,yvmax=300;
const int TOP=8;
const int BOTTOM=4;
const int RIGHT=2;
const int LEFT=1;

outcode computeOutcode(double x,double y);


void cohenSutherlandLineclipandDraw(double x0,double y0,double x1,double y1)
{
outcode outcode0,outcode1,outcodeout;
bool accept=false,done=false;
outcode0=computeOutcode(x0,y0);
outcode1=computeOutcode(x1,y1);
do{
if(!(outcode0|outcode1))
{
done=true;
accept=true;
}
else if(outcode0 & outcode1)
{
done=true;
}
else
{
double x,y;
outcodeout=outcode0?outcode0:outcode1;
if(outcodeout & TOP)
{
x=x0+(x1-x0)*(ymax-y0)/(y1-y0);
y=ymax;
}
else if(outcodeout & BOTTOM)
{
x=x0+(x1-x0)*(ymin-y0)/(y1-y0);
y=ymin;
}
else if(outcodeout & RIGHT)
{
y=y0+(y1-y0)*(xmax-x0)/(x1-x0);
x=xmax;
}
else 
{
y=y0+(y1-y0)*(xmin-x0)/(x1-x0);
x=xmin;
}

if(outcodeout == outcode0)
{
x0=x;
y0=y;
outcode0=computeOutcode(x0,y0);
}
else
{
x1=x;
y1=y;
outcode1=computeOutcode(x1,y1);
}
}
}while(!done);

if(accept)
{
double sx=(xvmax-xvmin)/(xmax-xmin);
double sy=(yvmax-yvmin)/(ymax-ymin);
double Vx0=xvmin+(x0-xmin)*sx;
double Vy0=yvmin+(y0-ymin)*sy;
double Vx1=xvmin+(x1-xmin)*sx;
double Vy1=yvmin+(y1-xmin)*sy;
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(xvmin,yvmin);
glVertex2f(xvmax,yvmin);
glVertex2f(xvmax,yvmax);
glVertex2f(xvmin,yvmax);
glEnd();

glColor3f(0.0,0.0,1.0);
glBegin(GL_LINES);
glVertex2d(Vx0,Vy0);
glVertex2d(Vx1,Vy1);
glEnd();
}
}
outcode computeOutcode(double x,double y)
{
outcode code=0;
if(y>ymax)
{
code|=TOP;
}
else if(y<ymin)
{
code|=BOTTOM;
}

if(x>xmax)
{
code|=RIGHT;
}
else if(x<xmin)
{
code|=LEFT;
}
return code;
}

void drawLine()
{
glBegin(GL_LINES);
glVertex2f(x0,y0);
glVertex2f(x1,y1);
glEnd();
}

void drawRect()
{
glBegin(GL_LINE_LOOP);
glVertex2f(xmin,ymin);
glVertex2f(xmax,ymin);
glVertex2f(xmax,ymax);
glVertex2f(xmin,ymax);
glEnd();

}

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0,0.0,0.0);
drawLine();
glColor3f(0.0,0.0,1.0);
drawRect();
cohenSutherlandLineclipandDraw(x0,y0,x1,y1);
glFlush();
}


void myinit()
{
glClearColor(1.0,1.0,1.0,1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,600.0,0.0,600.0);
glMatrixMode(GL_MODELVIEW);
}


int main(int argc,char**argv)
{
printf("Enter the end points of the line:\n");
scanf("%f%f%f%f",&x0,&y0,&x1,&y1);
printf("Enter the coordinates of the clipping window:\n");
scanf("%f%f%f%f",&xmin,&ymin,&xmax,&ymax);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(600,600);
glutInitWindowPosition(0,0);
glutCreateWindow("cohensuther land");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}
