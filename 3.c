#include <GL/glut.h>
#include <math.h>

void plot_circle(int xc, int yc, int r) {
    int x = 0, y = r;
    
    int d = 3 - 2 * r;
    
    glVertex2d(xc + x, yc + y);
    
    while (x <= y) {
        
        glVertex2d(xc + x, yc + y);
        glVertex2d(xc - x, yc + y);
        glVertex2d(xc + x, yc - y);
        glVertex2d(xc - x, yc - y);
        glVertex2d(xc + y, yc + x);
        glVertex2d(xc - y, yc + x);
        glVertex2d(xc + y, yc - x);
        glVertex2d(xc - y, yc - x);
        
        if (d < 0) {
            d += 4 * x + 6;
        } else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}

void display() {
    
    
    
    glBegin(GL_LINES);
    glVertex2f(-320,0);
    glVertex2f(320,0);
    glVertex2f(0,-240);
    glVertex2f(0,240);
    glEnd();
    glFlush();
    // Plot the circle in all quadrants with respect to center and radius
    glBegin(GL_POINTS);
    plot_circle(0, 0, 190);
    glEnd();
    // Swap the front and back buffers
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham Circle Drawing Algorithm");
    // Set the display function
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    gluOrtho2D(-320, 320,-240,240);
    glutDisplayFunc(display);
    // Start the main loop
    glutMainLoop();
    return 0;
}

