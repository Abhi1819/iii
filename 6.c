#include<stdio.h>

#include<stdlib.h>

#include<math.h>

#include<GL/glut.h>

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int Xa, Ya, Xb, Yb; 
int  xmin,ymin,xmax,ymax;
int computeRegionCode(int x, int y) {
    int code = INSIDE;
    if (x < xmin)
        code = LEFT;
    else if (x > xmax)
        code = RIGHT;
    if (y < ymin)
        code = BOTTOM;
    else if (y > ymax)
        code = TOP;
    return code;
}






int Round(int a)
{

return (int)(a+0.5);

}
void ddaline(int xa,int ya,int xb,int yb)
{
  int dx,dy,steps;
  dx=xb-xa;
  dy=yb-ya;
  if( abs(dx)>abs(dy))
  {
    steps=abs(dx);
  }
  else
  {
    steps=abs(dy);
   
  }
  float xincrement,yincrement;
  xincrement=dx/(float)(steps);
  yincrement=dy/(float)(steps);
  float x,y;
  x=(float)xa;
  y=(float)ya;
  glVertex2d(Round(x),Round(y));
  for(int k=0;k<steps;k++)
  {
    
    x=x+xincrement;
    y=y+yincrement;
    glVertex2d(Round(x),Round(y));
    
  }
   

}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_POINTS);
	   
     ddaline(xmin,ymin,xmax,ymin);
     ddaline(xmax,ymin,xmax,ymax);
     ddaline(xmax,ymax,xmin,ymax);
     ddaline(xmin,ymax,xmin,ymin);
     glColor3f(1.0,0.0,0.0);
     ddaline(Xa,Ya,Xb,Yb);
     glEnd();
    glFlush();

 }
 void cohenSutherlandLineClip() {
        int code1 = computeRegionCode(Xa, Ya);
    int code2 = computeRegionCode(Xb, Yb);
    int clipped = 0;

    while (1) {
        if ((code1 == 0) && (code2 == 0)) {
            
            clipped = 1;
            break;
        } else if (code1 & code2) {
            
            break;
        } else {
            int code_out = code1 ? code1 : code2;
            int x, y;

            if (code_out & TOP) {
                x = Xa + (Xb - Xa) * (ymax - Ya) / (Yb - Ya);
                y = ymax;
            } else if (code_out & BOTTOM) {
                x = Xa + (Xb - Xa) * (ymin - Ya) / (Yb - Ya);
                y = ymin;
            } else if (code_out & RIGHT) {
                y = Ya + (Yb - Ya) * (xmax - Xa) / (Xb - Xa);
                x = xmax;
            } else if (code_out & LEFT) {
                y = Ya + (Yb - Ya) * (xmin - Xa) / (Xb - Xa);
                x = xmin;
            }

            if (code_out == code1) {
                Xa = x;
                Ya = y;
                code1 = computeRegionCode(Xa, Ya);
            } else {
                Xb = x;
                Yb = y;
                code2 = computeRegionCode(Xb, Yb);
            }
        }
    }

    if (clipped) {
        printf("Line is clipped");
    } else {
        printf("Line completely outside the clipping window\n");
    }
}
 
 void mouse(int btn, int state, int x, int y)
{
  if( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POINTS);
     glColor3f(1.0,1.0,0.0);
     ddaline(xmin,ymin,xmax,ymin);
     ddaline(xmax,ymin,xmax,ymax);
     ddaline(xmax,ymax,xmin,ymax);
     ddaline(xmin,ymax,xmin,ymin);
     glColor3f(0.0,1.0,1.0);
     
     cohenSutherlandLineClip();
     ddaline(Xa,Ya,Xb,Yb);
     glEnd();
     glFlush();
}

}
 

int main(int argc , char **argv)
{

  printf("Enter the Xmin: \t");
  scanf("%d",&xmin);
    
  printf("Enter the Ymin: \t");
  scanf("%d",&ymin);
    
  printf("Enter the Xmax: \t");
  scanf("%d",&xmax);
    
  printf("Enter the Ymax: \t");
  scanf("%d",&ymax);

  printf("first points: \t");
  scanf("%d\t%d",&Xa,&Ya);
  printf("Second points: \t");
  scanf("%d\t%d",&Xb,&Yb);
     
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(640, 480);
  glutCreateWindow("Line Clipping");
  
  glClearColor(1.0, 1.0, 1.0, 0.0);
  glColor3f(1.0,0.0,0.0);
  gluOrtho2D(0, 640, 0, 480);
  
  glutDisplayFunc(draw);
  glutMouseFunc(mouse);
  glutMainLoop();
  return 0;
   
}
