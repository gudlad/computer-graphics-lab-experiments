#include<stdio.h>
#include<math.h>
#include<GL/glut.h>

GLfloat tri[3][3]={{100.0,300.0,195.0},{100.0,100.0,300.0},{1.0,1.0,1.0}};
GLfloat rot_mat[3][3]={{0},{0},{0}};
GLfloat result[3][3]={{0},{0},{0}};
GLfloat theta;
GLint ch;
GLfloat xr=300.0;
GLfloat yr=100.0;

void multiply()
{
int i,j,k;
for(i=0;i<3;i++)
{
for(j=0;j<3;j++)
{
result[i][j]=0;
for(k=0;k<3;k++)
result[i][j]=result[i][j]+rot_mat[i][k]*tri[k][j];
}
}
}

void rotate_origin()
{
rot_mat[0][0]=cos(theta);
rot_mat[0][1]=-sin(theta);
rot_mat[0][2]=0;
rot_mat[1][0]=sin(theta);
rot_mat[1][1]=cos(theta);
rot_mat[1][2]=0;
rot_mat[2][0]=0;
rot_mat[2][1]=0;
rot_mat[2][2]=1;
multiply();
}

void rotate_fixed_point()
{
GLfloat m,n;
m=xr*(1-cos(theta))+yr*sin(theta);
n=yr*(1-cos(theta))-xr*sin(theta);
rot_mat[0][0]=cos(theta);
rot_mat[0][1]=-sin(theta);
rot_mat[0][2]=m;
rot_mat[1][0]=sin(theta);
rot_mat[1][1]=cos(theta);
rot_mat[1][2]=n;
rot_mat[2][0]=0;
rot_mat[2][1]=0;
rot_mat[2][2]=1;
multiply();
}

void draw_triangle()
{
glColor3f(1.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2f(tri[0][0],tri[1][0]);
glVertex2f(tri[0][1],tri[1][1]);
glVertex2f(tri[0][2],tri[1][2]);
glEnd();
}

void draw_rotated_triangle()
{
glColor3f(0.0,0.0,1.0);
glBegin(GL_LINE_LOOP);
glVertex2f(result[0][0],result[1][0]);
glVertex2f(result[0][1],result[1][1]);
glVertex2f(result[0][2],result[1][2]);
glEnd();
}

void display()
{
glClear(GL_COLOR_BUFFER_BIT);
if(ch==1)
{
draw_triangle();
rotate_origin();
draw_rotated_triangle();
glFlush();
}
if(ch==2)
{
draw_triangle();
rotate_fixed_point();
draw_rotated_triangle();
glFlush();
}
}

void myinit()
{
glClearColor(1.0,1.0,1.0,1.0);
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(-499.0,499.0,-499.0,499.0);
}

int main(int argc,char**argv)
{
printf("Rotate :\n 1.Rotate origin \n  2.ROtate fixed point");
scanf("%d",&ch);
printf("Enter the roatation angle:\n");
scanf("%f",&theta);
theta=theta*3.142/180;
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(500,500);
glutInitWindowPosition(0,0);
glutCreateWindow("Rotation");
glutDisplayFunc(display);
myinit();
glutMainLoop();
}


