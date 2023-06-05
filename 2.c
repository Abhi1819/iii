#include <stdio.h>
#include <GL/glut.h>

int xa, ya, xb, yb, arr[2][1000], size = 0, flag = 0, ch = 0;

int ROUND(float a) {
    return abs(a + 0.5);
}

void Brehanhams(int Xa, int Ya, int Xb, int Yb) {
    int dx, dy, d, c, r, f;
    dx = Xb - Xa;
    dy = Yb - Ya;

    if (abs(dx) > abs(dy)) {
        d = 2 * abs(dy) - abs(dx);
        if (dx > 0) {
            c = Xa;
            r = Ya;
            f = Xb;
        } else {
            c = Xb;
            r = Yb;
            f = Xa;
        }
        arr[0][0] = c;
        arr[1][0] = r;
        size = 1;
        while (f > c) {
            if (d < 0) {
                c = c + 1;
                d = d + 2 * abs(dy);
                size += 1;
            } else {
                c = c + 1;
                d = d + 2 * abs(dy) - 2 * abs(dx);
                size += 1;
                if ((dy > 0 && dx > 0) || (dy < 0 && dx < 0)) {
                    r = r + 1;
                } else {
                    r = r - 1;
                }
            }
            arr[0][size] = c;
            arr[1][size] = r;
        }
    } else {
        d = 2 * abs(dx) - abs(dy);
        if (dy > 0) {
            c = Xa;
            r = Ya;
            f = Yb;
        } else {
            c = Xb;
            r = Yb;
            f = Ya;
        }
        arr[0][0] = c;
        arr[1][0] = r;
        size = 1;
        while (f > r) {
            if (d < 0) {
                r = r + 1;
                d = d + 2 * abs(dx);
                size += 1;
            } else {
                r = r + 1;
                d = d + 2 * abs(dx) - abs(dy);
                size += 1;
                if ((dy > 0 && dx > 0) || (dy < 0 && dx < 0)) {
                    c = c + 1;
                } else {
                    c = c - 1;
                }
            }
            arr[0][size] = c;
            arr[1][size] = r;
        }
    }
}

void dda(int xa, int ya, int xb, int yb) {
    int dx, dy, steps;
    dx = xb - xa;
    dy = yb - ya;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    } else {
        steps = abs(dy);
    }

    float x, y, xinc, yinc;
    x = xa;
    y = ya;
    xinc = dx / (float) steps;
    yinc = dy / (float) steps;

    arr[0][0] = ROUND(x);
    arr[1][0] = ROUND(y);
    size = 1;

    for (int i = 1; i < steps; i++) {
        x = x + xinc;
        y = y + yinc;
        arr[0][i] = ROUND(x);
        arr[1][i] = ROUND(y);
        size += 1;
    }
}

void drawline() {
    glBegin(GL_POINTS);

    switch (ch) {
        case 1:
            for (int i = 0; i < size; i++) {
                glVertex2d(arr[0][i], arr[1][i]);
            }
            break;
        case 2:
            for (int i = 0; i < size; i++) {
                if ((i % 2) != 0) {
                    glVertex2d(arr[0][i], arr[1][i]);
                }
            }
            break;
        case 3:
            for (int i = 0; i < size; i++) {
                if ((i % 4) != 0) {
                    glVertex2d(arr[0][i], arr[1][i]);
                }
            }
            break;
        case 4:
            glPointSize(10.0);
            for (int i = 0; i < size; i++) {
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
        int chf = 0;
        printf("\n1.\tDDA");
        printf("\n2.\tBrehanhams");
        printf("\n\tEnter Choice: ");
        scanf("%d", &chf);
        switch (chf) {
            case 1:
                dda(xa, ya, xb, yb);
                break;
            case 2:
                Brehanhams(xa, ya, xb, yb);
                break;
        }
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
    glutCreateWindow("Practical No 2");

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
