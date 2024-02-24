#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int xc, yc; // Center of the circle
int r; // Radius of the circle

// Initialization function for OpenGL configurations
void Init() {
    // Set background color to dark red and clear the window
    glClearColor(0.5, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set color to blue
    glColor3f(0.0, 0.0, 1.0);

    // Set up a 2D orthogonal projection matrix
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

// Function to plot symmetric points of the circle
void plot_point(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
    glEnd();
}

// Function to draw a circle using Bresenham's circle drawing algorithm
void bresenham_circle(int r) {
    int x = 0, y = r;
    float pk = 1 - r;
    plot_point(x, y);

    while (x < y) {
        x = x + 1;
        if (pk < 0)
            pk = pk + 2 * x + 1;
        else {
            y = y - 1;
            pk = pk + 2 * (x - y) + 1;
        }
        plot_point(x, y);
    }
    glFlush();
}

// Display callback function
void circles(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham_circle(r);
}

int main(int argc, char **argv) {
    printf("Center:");
    scanf("%d %d", &xc, &yc);
    printf("Radius:");
    scanf("%d", &r);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Bresenham's Circle");

    // Call initialization routine
    Init();

    // Register display callback function
    glutDisplayFunc(circles);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
