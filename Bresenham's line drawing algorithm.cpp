// Conditional compilation for cross-platform compatibility
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <stdio.h>

int x1, y1, x2, y2;

// Initialization function for OpenGL configurations
void myInit() {
    // Set background color to dark red and clear the window
    glClearColor(0.5, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    // Set color to blue
    glColor3f(0.0, 0.0, 1.0);

    // Set up a 2D orthogonal projection matrix
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 500, 0, 500);
}

// Function to plot a pixel at (x, y)
void draw_pixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// Function to draw a line using Bresenham's algorithm
void draw_line(int x1, int x2, int y1, int y2) {
    int dx, dy, i, e;
    int inc1, inc2, temp;
    int x, y;

    // Ensure that we draw the line from left to right
    if (x2 < x1) {
        temp = x1;
        x1 = x2;
        x2 = temp;

        temp = y1;
        y1 = y2;
        y2 = temp;
    }

    dx = x2 - x1;
    dy = y2 - y1;

    x = x1;
    y = y1;
    draw_pixel(x, y);

    e = 2 * dy - dx;
    inc1 = 2 * (dy - dx);
    inc2 = 2 * dy;

    for (i = 0; i < dx; i++) {
        x++;
        if (e >= 0) {
            y++;
            e += inc1;
        } else {
            e += inc2;
        }

        draw_pixel(x, y);
    }
}

// Display callback function
void myDisplay() {
    draw_line(x1, x2, y1, y2);
    glFlush(); // Flush the OpenGL pipeline to the viewport
}

// Main function
int main(int argc, char **argv) {
    printf("Starting Point: ");
    scanf("%d %d", &x1, &y1);
    printf("End Point: ");
    scanf("%d %d", &x2, &y2);

    // Initialize GLUT
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(700, 700);
    glutInitWindowPosition(30, 30);
    glutCreateWindow("Bresenham's Line Drawing");

    // Call initialization routine
    myInit();

    // Register display callback function
    glutDisplayFunc(myDisplay);

    // Enter the GLUT main loop
    glutMainLoop();

    return 0;
}
