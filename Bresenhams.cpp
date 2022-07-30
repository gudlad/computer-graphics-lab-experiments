#include<GL/glut.h>
#include<stdio.h>
#include<math.h>

GLint xOne,yOne,xTwo,yTwo;
void init();
void display();
void LineBres_L1(GLint,GLint,GLint,GLint,GLfloat);
void setPixel(GLint,GLint);
void LineBres_GE1(GLint,GLint,GLint,GLint,GLfloat);

int main(int argc,char**argv)
{
printf("Bresen demo;\n");
printf("Enter the coordinates of linex(x0,y0,xtwo,ytwo):\n");
scanf("%d%d%d%d",&xOne,&yOne,&xTwo,&yTwo);
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(0,0);
glutCreateWindow("Bresen window");
glutDisplayFunc(display);
init();
glutMainLoop();
}

void init()
{
glClearColor(1.0,1.0,1.0,1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,500.0,0.0,500.0);
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
GLfloat m;
m=(float)(yTwo-yOne)/(xTwo-xOne);
if(fabs(m)>=1)
{
LineBres_GE1(xOne,yOne,xTwo,yTwo,m);
}
else
 LineBres_L1(xOne,yOne,xTwo,yTwo,m);
}

void LineBres_L1(GLint x0,GLint y0,GLint xEnd,GLint yEnd,GLfloat m)
{
GLint dx=abs(xEnd-x0);
GLint dy=abs(yEnd-y0);
GLint p=2*dy-dx;
GLint twoDy=2*dy;
GLint twoDyMinusDx=2*(dy-dx);
GLint x=x0,y=y0;
if(x0>xEnd)
{
x=xEnd;
y=yEnd;
xEnd=x0;
}
else
{
x=x0;
y=y0;
}
setPixel(x,y);
while(x<xEnd)
{
x++;
if(p<0)
	p+=twoDy;
else
{
  if(m<0)
  {
  y--;
  }
  else
  {
  y++;
  p+=twoDyMinusDx;
  }
}
setPixel(x,y);
}
}

void setPixel(GLint xCor,GLint yCor)
{
glColor3f(1.0,0.0,0.0);
glBegin(GL_POINTS);
glVertex2i(xCor,yCor);
glEnd();
glFlush();
}

void LineBres_GE1(GLint x0,GLint y0,GLint xEnd,GLint yEnd,GLfloat m)
{
GLint dx=abs(xEnd-x0);
GLint dy=abs(yEnd-y0);
GLint p=2*dx-dy;
GLint twoDx=2*dx;
GLint twoDxMinusDy=2*(dx-dy);
GLint x=x0,y=y0;
if(y0>yEnd)
{
x=xEnd;
y=yEnd;
yEnd=y0;
}
else
{
x=x0;
y=y0;
}
setPixel(x,y);
while(y<yEnd)
{
y++;
if(p<0)
{
p+=twoDx;
}
else
{
if(m<0)
{
x--;
}
else
{
x++;
p+=twoDxMinusDy;
}
}
setPixel(x,y);
}
}
