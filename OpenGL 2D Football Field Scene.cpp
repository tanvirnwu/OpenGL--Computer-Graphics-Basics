/**
 * OpenGL 2D Football Field Scene
 *
 * This program creates a simple 2D representation of a football field using OpenGL and GLUT. It demonstrates the usage of basic
 * OpenGL primitives to draw geometric shapes including circles for the ball and the center circle of the field, rectangles for the 
 * field boundaries, and lines to represent the goalposts.
 * 
 * The scene includes:
 * - A filled circle to represent the football.
 * - An unfilled circle to denote the center circle of the football field.
 * - A large rectangle to outline the boundaries of the football field.
 * - Multiple lines to represent the goalposts on either side of the field.
 * 
 * The program utilizes OpenGL's fixed-function pipeline to set up the 2D scene, including setting the viewing volume using
 * orthographic projection. Primitives such as GL_LINE_LOOP for circles, GL_LINES for straight lines, and GL_TRIANGLE_FAN for
 * the filled circle (ball) are used to draw the scene.
 * 
 * Compilation and Execution:
 * Ensure that you have OpenGL and GLUT installed on your system. Compile this program using a command appropriate for your system,
 * for example on Linux with g++:
 * 
 * g++ -o football_scene football_scene.cpp -lGL -lGLU -lglut
 * 
 * Execute the program:
 * ./football_scene
 *
 * This will open a window displaying the football field scene.
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <string>
#define PI 3.1416
using namespace std;

int windowWidth = 700, windowHeight = 700;

// Function to draw a rectangle
void rectangle(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float r, float g, float b) {
    glBegin(GL_LINE_LOOP);
    glColor3f(r, g, b); // Set color
    glVertex2f(x1, y1); // Define rectangle vertices
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glVertex2f(x4, y4);
    glEnd();
}

// Function to draw a circle using line loop
void circle(float cx, float cy, float r, int num_segments) {
    glBegin(GL_LINE_LOOP);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0 * PI * float(ii) / float(num_segments); // Calculate angle
        float x = r * cosf(theta); // Calculate x coordinate
        float y = r * sinf(theta); // Calculate y coordinate
        glVertex2f(x + cx, y + cy); // Plot vertex
    }
    glEnd();
}

// Function to draw a filled circle (ball) using triangle fan
void ball(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0 * PI * float(ii) / float(num_segments); // Calculate angle
        float x = r * cosf(theta); // Calculate x coordinate
        float y = r * sinf(theta); // Calculate y coordinate
        glVertex2f(x + cx, y + cy); // Plot vertex
    }
    glEnd();
}

// Function to draw a line
void line(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glBegin(GL_LINES);
    glColor3f(r, g, b); // Set color
    glVertex2f(x1, y1); // Starting vertex
    glVertex2f(x2, y2); // Ending vertex
    glEnd();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix
    glLoadIdentity(); // Reset projection matrix
    gluOrtho2D(0, 700, 0, 700); // Set orthogonal projection for 2D view
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
    glLoadIdentity(); // Reset modelview matrix
    glViewport(0, 0, windowWidth, windowHeight); // Set viewport to window dimensions

    // Draw the football
    glPushMatrix();
    ball(280.0, 350.0, 10.0, 100.0); // Draw filled circle as
    glPopMatrix();

    // Draw the center circle
    glPushMatrix();
    circle(400.0, 300.0, 50.0, 100.0);
    glPopMatrix();

    // Draw the football field boundary
    glPushMatrix();
    rectangle(100.0, 100.0, 100.0, 500.0, 700.0, 500.0, 700.0, 100.0, 1.0, 0.0, 1.0);
    glPopMatrix();

    // Draw goalposts using lines
    glPushMatrix();
    line(400.0, 100.0, 400.0, 500.0, 1.0, 0.0, 0.0); // Midfield line

    // Left goalpost
    line(100.0, 200.0, 200.0, 200.0, 1.0, 0.0, 0.0);
    line(100.0, 400.0, 200.0, 400.0, 1.0, 0.0, 0.0);
    line(200.0, 200.0, 200.0, 400.0, 1.0, 0.0, 0.0);

    // Left small box
    line(100.0, 250.0, 150.0, 250.0, 1.0, 0.0, 0.0);
    line(100.0, 350.0, 150.0, 350.0, 1.0, 0.0, 0.0);
    line(150.0, 250.0, 150.0, 350.0, 1.0, 0.0, 0.0);

    // Right goalpost
    line(700.0, 200.0, 600.0, 200.0, 1.0, 0.0, 0.0);
    line(700.0, 400.0, 600.0, 400.0, 1.0, 0.0, 0.0);
    line(600.0, 200.0, 600.0, 400.0, 1.0, 0.0, 0.0);

    // Right small box
    line(700.0, 250.0, 650.0, 250.0, 1.0, 0.0, 0.0);
    line(650.0, 250.0, 650.0, 350.0, 1.0, 0.0, 0.0);
    line(650.0, 350.0, 700.0, 350.0, 1.0, 0.0, 0.0);

    glPopMatrix();

    // Complete rendering
    glFlush(); // Ensure all OpenGL commands are executed
    glutSwapBuffers(); // Swap the front and back buffers to display the rendered image

}





int main(int argc, char **argv) {
    // Initializes the GLUT library and processes any command line arguments
    glutInit(&argc, argv);

    // Specifies the display mode by enabling double buffering, RGB color model, and a depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    // Sets the initial position of the window. Here, it's set to the top-left corner of the screen
    glutInitWindowPosition(0, 0);

    // Sets the initial size of the window using the predefined windowWidth and windowHeight variables
    glutInitWindowSize(windowWidth, windowHeight);

    // Creates the window with the title "football"
    glutCreateWindow("football");

    // Registers the display callback function. This function is called whenever GLUT determines the window needs to be redrawn
    glutDisplayFunc(display);

    // Sets the shading model to smooth, which interpolates colors between vertices
    glShadeModel(GL_SMOOTH);

    // Enables depth testing, which is necessary for determining which objects are in front of others
    glEnable(GL_DEPTH_TEST);

    // Enters the GLUT event processing loop. This starts the program's main loop, waiting for events such as keyboard and mouse input
    glutMainLoop();

    return 0;
}
