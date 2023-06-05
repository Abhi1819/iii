#include <stdio.h>
#include <GL/glut.h>

int xa, ya, xb, yb, arr[2][1000], size = 0, flag = 0, ch = 0;

int ROUND(float a) {
    return abs(a + 0.5);
}


int X1, Y1, X2, Y2, Xinc, Yinc, steps, dx, dy, dE, dNE, DP ,Clickedx,Clickedy,clickCount=0;

void Draw_Bresenham(int xa , int ya , int xb, int yb)
{
    dx = xb - xa;
    dy = yb - ya;

    printf("dx = %d \n" ,dx);
    printf("dy = %d \n" ,dy);



    // DECISION PARAMETER
    DP = 2 * dy - dx;
    printf("DP = %d \n" ,DP);

    dE = 2 * dy;           // Select if DP < 0
    printf("dE = %d\n" ,dE);

    dNE = 2 * (dy - dx);   // Select if DP > 0
    printf("dNE = %d \n" ,dNE);

    Xinc = xa;
    Yinc = ya;

    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    arr[0][0] = Xinc;
    arr[1][0] = Yinc;
    // glVertex2i(Xinc, Yinc);

    for (steps = 0; steps < dx; steps++)
    {
        if (DP >= 0)
        {
            Xinc += 1;
            Yinc += 1;
            DP += dNE;     

            arr[0][steps] = Xinc;
            arr[1][steps] = Yinc;

        }
        else 
        {
            Xinc += 1;
            Yinc += 0;
            DP += dE;
            
            arr[0][steps] = Xinc;
            arr[1][steps] = Yinc;
        }

        
    }

    glEnd();
    glFlush();
}





void drawline() {
    glBegin(GL_POINTS);

    switch (ch) {
        case 1:
            for (int i = 0; i < steps;i++) {
                glVertex2d(arr[0][i], arr[1][i]);
            }
            break;
        case 2:
            for (int i = 0; i < steps; i++) {
                if ((i % 2) != 0) {
                    glVertex2d(arr[0][i], arr[1][i]);
                }
            }
            break;
        case 3:
            for (int i = 0; i < steps; i++) {
                if ((i % 4) != 0) {
                    glVertex2d(arr[0][i], arr[1][i]);
                }
            }
            break;
        case 4:
            glPointSize(10.0);
            for (int i = 0; i < steps; i++) {
                glVertex2d(arr[0][i], arr[1][i]);
            }
            break;
    }

    glEnd();
    glFlush();
}

void mouse(int btn, int state, int mx, int my) {
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        xa = mx;
        ya = 480 - my;
    }
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        xb = mx;
        yb = 480 - my;
        flag = 1;
        
        Draw_Bresenham(xa, ya, xb, yb);
    
        glutPostRedisplay();
    }
}

void draw() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    glVertex2f(320, 0);
    glVertex2f(320, 480);
    glVertex2f(0, 240);
    glVertex2f(640, 240);
    glEnd();

    if (flag == 1 && ch != 0) {
        drawline();
    }

    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Practical No 2 - BRESENHAM");

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(1.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);

    glutDisplayFunc(draw);
    glutMouseFunc(mouse);

    printf("\n1.\tSimple Line");
    printf("\n2.\tDotted Line");
    printf("\n3.\tDashed Line");
    printf("\n4.\tSolid Line");
    printf("\n5.\tExit");
    printf("\nEnter Your Choice: ");
    scanf("%d", &ch);

    glutMainLoop();
}
