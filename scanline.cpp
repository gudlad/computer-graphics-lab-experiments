#include<stdio.h>
#include<stdlib.h>
#include<GL/glut.h>

GLint x1=200,y1=200,x2=100,y2=300,x3=200,y3=400,x4=300,y4=300;
float R=0.0,G=0.0,B=0.0;
int color_menu;
int le[500],re[500];

void edgedetect(GLint x1,GLint y1,GLint x2,GLint y2,GLint*le,GLint*re)
{
float mx,x,temp;
int i;
if((y2-y1)<0)
{
temp=y1;
y1=y2;
y2=temp;
temp=x1;
x1=x2;
x2=temp;
}

if((y2-y1)!=0)
{
mx=(x2-x1)/(y2-y1);
}
else
{
mx=(x2-x1);
}
x=x1;
for(i=y1;i<y2;i++)
{
if(x<le[i])
{
le[i]=x;
}
if(x>re[i])
{
re[i]=x;
}
x+=mx;
}
}

void drawPixel(int m,int n)
{
glColor3f(R,G,B);
glBegin(GL_POINTS);
glVertex2i(m,n);
glEnd();
glFlush();
}

void scanfill()
{
int i,y;
for(i=0;i<500;i++)
{
le[i]=500;
re[i]=0;
}
edgedetect(x1,y1,x2,y2,le,re);
edgedetect(x2,y2,x3,y3,le,re);
edgedetect(x3,y3,x4,y4,le,re);
edgedetect(x4,y4,x1,y1,le,re);

for(y=0;y<500;y++)
{
for(i=le[y];i<=re[y];i++)
    drawPixel(i,y);
}

}

void display()
{
glClearColor(1.0,1.0,1.0,1.0);
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(R,G,B);
glBegin(GL_LINE_LOOP);
/*
glVertex2f(x1,y1);
glVertex2f(x2,y2);
glVertex2f(x3,y3);
glVertex2f(x4,y4); */

glVertex2i(x1,y1);
glVertex2i(x2,y2);
glVertex2i(x3,y3);
glVertex2i(x4,y4); 
glEnd();
scanfill();
glFlush();
}

void colorMenu(int id)
{
switch(id)
{
case 1:
	R=1.0;
	G=0.0;
	B=0.0;
	glutPostRedisplay();
	break;
case 2:
        R=0.0;
	G=1.0;
	B=0.0;
	glutPostRedisplay();
	break;
case 3:
	R=0.0;
	G=0.0;
	B=1.0;
	glutPostRedisplay();
	break;

}

}

int main(int argc,char**argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
//glutInitWindowSize(800,600);
glutInitWindowSize(700,500);
glutInitWindowPosition(0,0);
glutCreateWindow("scanline algo");
gluOrtho2D(0.0,500.0,0.0,500.0);
glutDisplayFunc(display);
color_menu=glutCreateMenu(colorMenu);
glutAddMenuEntry("Red",1);
glutAddMenuEntry("Green",2);
glutAddMenuEntry("Blue",3);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMainLoop();
return 0;
}
