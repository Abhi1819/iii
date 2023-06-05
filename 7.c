#include<stdio.h>

#include<stdlib.h>

#include<math.h>

#include<GL/glut.h>

int v;              
int i1=0;  //lout
int i2=0;  //rout
int i3=0;  //bout
int i4;  //tout

int  xmin,ymin,xmax,ymax;

float input[2][10];

float loutput[2][10];

float routput[2][10];

float toutput[2][10];

float boutput [2][10];

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
  x=xa;
  y=ya;
  glVertex2d(Round(x),Round(y));
  for(int k=0;k<steps;k++)
  {
    
    x=x+xincrement;
    y=y+yincrement;
    glVertex2d(Round(x),Round(y));
    
  }
   

}


  void left_clip(int xa,int ya,int xb,int yb)
{  
   
   int x,y;   
                                                                                                       
  float m=(yb-ya)/ (float) (xb-xa);
  

  if(xa < xmin && xb > xmin) //out-in                    

  {
      
    x=xmin;

    y=ya+(m*(x-xa));

    loutput[0][i1]=x;
    
    loutput[1][i1]=y;
    
    i1+=1;
    
    loutput[0][i1]=xb;
  
    loutput[1][i1]=yb;
     
    i1+=1;

  }

  else if(xa > xmin && xb > xmin) //in-in          

  {

    loutput[0][i1]=xb;

    loutput[1][i1]=yb;
    
    i1+=1;

  }

  else if(xa > xmin && xb < xmin)   //in-out                                                

  {

     x = xmin;                                  

    y = ya + (m*(x-xa));

    loutput [0] [i1] = x;

    loutput [1] [i1] = y;

     i1+=1;

  }
    
}

void right_clip (int xa,int ya,int xb,int yb)
 {
  int x,y;
  
  
  float m=(yb-ya)/(float)(xb-xa);

  if(xa > xmax && xb < xmax) //out-in

  {

    x = xmax;

    y = ya + (m*(x-xa));
    
    routput [0] [i2] =x;
    
    routput [1] [i2] =y;

    i2+=1;
    
    routput[0][i2] = xb;
    
    routput[1][i2] = yb;
    
    i2+=1;

  }

  else if(xa < xmax && xb < xmax) //in-in          

  {

     routput[0][i2] = xb;
     routput[1][i2] = yb;
     i2+=1;

  }

  else if(xa < xmax && xb > xmax)       //in - out                                             

  {

    x = xmax;                                  

    y = ya + (m*(x-xa));

    routput[0][i2]=x;
    
    routput[1][i2]=y;

     i2+=1;

  }

}

void bottom_clip(int xa,int ya,int xb,int yb)
{
  float m=(xb-xa)/(float)(yb-ya);
  int x,y;
  
    if(ya > ymin && yb >ymin)
    {
        boutput[0][i3]= xb;
        
        boutput[1][i3]=yb;     
      
       i3+=1;
    }
    
    else if(ya < ymin && yb > ymin)
   {
       x= xa + m*(ymin - ya);
   
      boutput[0][i3] = x;
      
      boutput[1][i3]=ymin;
   
      i3+=1;
      
      boutput[0][i3] = xb;
      
      boutput[1][i3] = yb;
      
      i3+=1;
   }
   
   else if( ya >= ymin  && yb < ymin )
   {
       x= xa + m*(ymin - ya);

       boutput[0][i3] = x;

       boutput[1][i3] = ymin;
       
       i3+=1;
   }
}   

void top_clip(int xa, int ya, int xb, int yb)
{
    float m=(xb-xa)/(float)(yb-ya);
    
    int x,y;
    if( ya < ymax && yb < ymax)
  {
     toutput[0][i4] = xb;
    
     toutput [1][i4] = yb;
    
    i4+=1;
  
  }
  else if(ya > ymax && yb <=ymax)
  {
     x= xa+ m*(ymax - ya);
     
     y = ymax;
  
     toutput[0][i4] = x;
     
     toutput[1][i4] = y;
     
     i4+=1;
     
     toutput[0][i4] = xb;
     
     toutput[1][i4] = yb;
     
     i4+=1;
  
  }
  
  else if(ya < ymax && yb > ymax)
  {
      x= xa + m*(ymax - ya);
      
      y=ymax;
      
      toutput[0][i4] = x;
  
      toutput[1][i4] = y;
      
      i4+=1;
  
  }
 
}

void drawpolygon(float output[2][10] ,int i)
{
  int n;
  for(n=0;n<i-1;n++)
  {
  ddaline(output[0][n],output[1][n],output[0][n+1],output[1][n+1]);
  }
  ddaline(output[0][n],output[1][n],output[0][0],output[1][0]);
  
  
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
     drawpolygon(input,v);
     glEnd();
    glFlush();

 }
 
 void mouse(int btn, int state, int x, int y)
{
  if( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
     glClear(GL_COLOR_BUFFER_BIT);
     glBegin(GL_POINTS);
     glColor3f(1.0,1.0,1.0);
     ddaline(xmin,ymin,xmax,ymin);
     ddaline(xmax,ymin,xmax,ymax);
     ddaline(xmax,ymax,xmin,ymax);
     ddaline(xmin,ymax,xmin,ymin);
     glColor3f(0.0,1.0,1.0);
     drawpolygon(toutput,i4);
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

  printf("Enter the number of vertex:");

  scanf("%d",&v);

  printf("Enter the points for the polygon:\n");

  for(int m=0;m<v;m++)

  {
     printf("X value: ");
     scanf("\t%f",&input[0][m]);
     printf("Y value: ");
     scanf("\t%f",&input[1][m]);
     

  }
  
  int n;
   for(  n=0; n<v-1 ;n++)
     
   {

   left_clip(input[0][n],input[1][n],input[0][n+1],input[1][n+1]);

   }

   left_clip(input[0][n],input[1][n],input[0][0],input[1][0]);
   
   for(int k=0;k<2;k++)

    {

      for(int j=0;j<i1;j++)

      {

          printf("%f\t",loutput[k][j]);

     
	}

      printf("\n");

    }
     printf("%d\n",i1);
    
    int r;
  for(r=0;r<i1-1;r++)

   {
  
   right_clip(loutput[0][r],loutput[1][r],loutput[0][r+1],loutput[1][r+1]);

   }

   right_clip(loutput[0][r],loutput[1][r],loutput[0][0],loutput[1][0]);
   
   for(int k=0;k<2;k++)

    {

      for(int j=0;j<i2;j++)

      {

          printf("%f\t",routput[k][j]);

     
	}

      printf("\n");

    }
    
    
    printf("%d\n",i2);
    
    int b ;
  for( b=0;b<i2-1;b++)

   {
  
   bottom_clip(routput[0][b],routput[1][b],routput[0][b+1],routput[1][b+1]);

   }

   bottom_clip(routput[0][b],routput[1][b],routput[0][0],routput[1][0]);
   
   for(int k=0;k<2;k++)

    {

      for(int j=0;j<i3;j++)

      {

          printf("%f\t",boutput[k][j]);

     
	}

      printf("\n");

    }
    
    
    printf("%d\n",i3);
    
    int t;
  for(t=0;t<i3-1;t++)

   {
  
   top_clip(boutput[0][t],boutput[1][t],boutput[0][t+1],boutput[1][t+1]);

   }

   top_clip(boutput[0][t],boutput[1][t],boutput[0][0],boutput[1][0]);
   
   for(int k=0;k<2;k++)

    {

      for(int j=0;j<i4;j++)

      {

          printf("%f\t",toutput[k][j]);

     
	}

      printf("\n");

    }
    
    
    printf("%d\n",i4);
    
    glutInit(&argc, argv);
        
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	
	glutInitWindowPosition(0, 0);
	
	glutInitWindowSize(640, 480);
	
	glutCreateWindow("Polygon Clipping");
	
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glColor3f(1.0,1.0,1.0);
	
	gluOrtho2D(0, 640, 0, 480);
	
        glutDisplayFunc(draw);
      
        glutMouseFunc(mouse);
        
	glutMainLoop();
	return 0;
   
}
