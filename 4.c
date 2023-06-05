#include<stdio.h>
#include<GL/glut.h>
int xa,ya,xb,yb,vertex[2][20],v,xf,yf,check=0;;
float boundry[3],fill[3],old[3];
int ROUND(float a){
	return abs(a+0.5);

}
void dda(int xa,int ya,int xb,int yb){
	int dx,dy,steps;
	dx=xb-xa;
	dy=yb-ya;

	if(abs(dx)>abs(dy)){
		steps=abs(dx);

	}else{
		steps=abs(dy);
	}
	float x,y,xinc,yinc;
	x=xa;
	y=ya;
	xinc=dx/(float)steps;
	yinc=dy/(float)steps;

	glVertex2d(ROUND(x),ROUND(y));
	for(int i=1;i<steps;i++){
		x=x+xinc;
		y=y+yinc;
		glVertex2d(ROUND(x),ROUND(y));
	}
}



void boundaryfill(int x,int y,float boundary[3], float fill[3])
{
float current[3];
glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,current);

if((current[0]!=boundary[0] ||current[1]!=boundary[1] ||current[2]!=boundary[2]) && (current[0]!=fill[0] ||current[1]!=fill[1] || current[2]!=fill[2]))
{
glColor3f(fill[0],fill[1],fill[2]);
glBegin(GL_POINTS);
glVertex2d(x,y);
glEnd();
glFlush();

boundaryfill(x+1,y,boundary,fill);
boundaryfill(x-1,y,boundary,fill);
boundaryfill(x,y+1,boundary,fill);
boundaryfill(x,y-1,boundary,fill);

}
}
void FloodFill(int x,int y,float old[3],float fill[3]){
	float current[3];
	glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,current);

	if((current[0]==old[0] && current[1]==old[1] && current[2]==old[2]) && (current[0]!=fill[0] ||current[1]!=fill[1] || current[2]!=fill[2])){
		glColor3f(fill[0],fill[1],fill[2]);
		glBegin(GL_POINTS);
		glVertex2d(x,y);
		glEnd();
		glFlush();

		FloodFill(x+1,y,old,fill);
		FloodFill(x-1,y,old,fill);
		FloodFill(x,y+1,old,fill);
		FloodFill(x,y-1,old,fill);
		
		


	}

}

void draw(){
  glBegin(GL_POINTS);
  
  int j;
  for(j=0;j<v-1;j++){
  	dda(vertex[0][j],vertex[1][j],vertex[0][j+1],vertex[1][j+1]);
  }
  dda(vertex[0][j],vertex[1][j],vertex[0][0],vertex[1][0]);
  glEnd();
  glFlush();
}
void mouse(int btn,int state,int x,int y){
	if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
      xf=x;
      yf=480-y;
      if(check==1){
      boundaryfill(xf,yf,boundry,fill);
      }else if(check==2){
      	FloodFill(xf,yf,old,fill);
      	old[0]=fill[0];
        old[1]=fill[1];
        old[2]=fill[2];
      }else{
      	printf("\n\tPlease Right Click and Select Filling Algorithm!!!\t\n");
      }
	}
}

void keyboard(unsigned char key,int x,int y){
  switch(key){
  case 'r':
  	      fill[0]=1.0;
          fill[1]=0.0;
          fill[2]=0.0;
          break;
  case 'g':
  	      fill[0]=0.0;
          fill[1]=1.0;
          fill[2]=0.0;
          break;
  case 'b':
  	      fill[0]=0.0;
          fill[1]=0.0;
          fill[2]=1.0;
          break;


  }
}

void menu(int option){
	switch(option){
	case 1:
		check=1;
		break;
	case 2:
		check=2;
		break;
	case 3:
		break;
	}

}
int main(int argc, char **argv)
{
	printf("\nEnter No of Vertex to Draw Polygon:\t");
	scanf("%d",&v);

	for(int i=0;i<v;i++){
		printf("\nX value:\t");
		scanf("%d",&vertex[0][i]);

		printf("\nY value:\t");
		scanf("%d",&vertex[1][i]);
	}

	printf("\nEnter boundry Colour in RGB: ");
	for(int k=0;k<3;k++){
		scanf("%f",&boundry[k]);
	}

	printf("\nEnter fill Colour in RGB: ");
	for(int k=0;k<3;k++){
		scanf("%f",&fill[k]);
	}
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(640,480);
  glutCreateWindow("Practical No 4");

  glClearColor(1.0,1.0,1.0,0.0);
  old[0]=1.0;
  old[1]=1.0;
  old[2]=1.0;
  glColor3f(boundry[0],boundry[1],boundry[2]);
  
  
  
  gluOrtho2D(0,640,0,480);

  glClear(GL_COLOR_BUFFER_BIT);
  
  
  glutDisplayFunc(draw);
  glutMouseFunc(mouse);
  glutKeyboardFunc(keyboard);
  glutCreateMenu(menu);
  glutAddMenuEntry("boundry Fill",1);
  glutAddMenuEntry("Flood Fill",2);
  glutAddMenuEntry("Exit",3);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
	return 0;
}
