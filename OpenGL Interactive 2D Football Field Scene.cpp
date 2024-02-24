/**
 * OpenGL Interactive 2D Football Field Scene
 *
 * This program creates a 2D representation of a football field with an interactive ball that can be moved around the field
 * using keyboard inputs. It demonstrates the use of OpenGL and GLUT for basic 2D graphics rendering and interactive controls.
 *
 * Features include:
 * - A football field drawn using a rectangle.
 * - An interactive ball that can be moved with the keyboard.
 * - Keyboard controls to move the ball up, down, left, and right.
 *
 * The program initializes a window using GLUT and sets up a simple 2D orthographic projection. The football field is drawn as
 * a large rectangle, and the ball is a filled circle that can be moved within the field boundaries. Keyboard inputs are handled
 * to update the ball's position on the field.
 *
 * Compilation (Linux):
 * g++ -o interactive_field interactive_field.cpp -lGL -lGLU -lglut
 *
 * Execution:
 * ./interactive_field
 *
 * Control the ball with the following keys:
 * - 'r': Move right
 * - 'l': Move left
 * - 'u': Move up
 * - 'd': Move down
 * - 'q': Quit the program
 */

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <bits/stdc++.h>
#include <string>
#define PI 3.1416
using namespace std;

static int xp = 120; // Ball's initial x position
static int yp = 120; // Ball's initial y position
int xf = 20; // x-axis movement factor
int yf = 20; // y-axis movement factor
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

// Function to draw a line
void line(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glBegin(GL_LINES);
    glColor3f(r, g, b); // Set color
    glVertex2f(x1, y1); // Starting vertex
    glVertex2f(x2, y2); // Ending vertex
    glEnd();
}

// Function to draw a filled circle (ball)
void circle1(float cx, float cy, float r, int num_segments) {
    glBegin(GL_TRIANGLE_FAN);
    for (int ii = 0; ii < num_segments; ii++) {
        float theta = 2.0 * PI * float(ii) / float(num_segments); // Calculate angle
        float x = r * cosf(theta); // Calculate x coordinate
        float y = r * sinf(theta); // Calculate y coordinate
        glVertex2f(x + cx, y + cy); // Plot vertex
    }
    glEnd();
}






// Display callback function
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear color and depth buffers
    glMatrixMode(GL_PROJECTION); // Switch to projection matrix
    glLoadIdentity(); // Reset projection matrix
    gluOrtho2D(0, 800, 0, 800); // Set orthogonal projection for 2D view
    glMatrixMode(GL_MODELVIEW); // Switch back to modelview matrix
    glLoadIdentity(); // Reset modelview matrix
    glViewport(0, 0, windowWidth, windowHeight); // Set viewport to window dimensions

    // Draw the football field
    glPushMatrix();
    rectangle(100.0, 100.0, 100.0, 500.0, 700.0, 500.0, 700.0, 100.0, 1.0, 1.0, 1.0);
    glPopMatrix();

    // Draw the interactive ball
    glPushMatrix();
    glTranslatef(xp, yp, 0); // Translate ball to its current position
    circle1(120, 120, 20, 10); // Draw filled circle as the ball
    glPopMatrix();

    glFlush(); // Ensure all OpenGL commands are executed
    glutSwapBuffers(); // Swap the front and

}

// Keyboard input callback function
static void key(unsigned char key, int x, int y) {
    switch (key) {
        case 'q': // Quit the application
            exit(0);
            break;
        case 'r': // Move right
            if (xp < 700) xp += xf;
            break;
        case 'l': // Move left
            if (xp > 120) xp -= xf;
            break;
        case 'u': // Move up
            if (yp < 500) yp += yf;
            break;
        case 'd': // Move down
            if (yp > 120) yp -= yf;
            break;
    }
    glutPostRedisplay(); // Request display update
}

// Idle callback function
static void idle(void) {
    glutPostRedisplay(); // Continuously update the display
}

// Main function: Sets up OpenGL, GLUT, and enters the main loop
int main(int argc, char **argv) {
    glutInit(&argc, argv); // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // Double buffering, RGB color, Depth buffer
    glutInitWindowPosition(0, 0); // Window position
    glutInitWindowSize(windowWidth, windowHeight); // Window size
    glutCreateWindow("Interactive Football Field"); // Create window with title

    glutDisplayFunc(display); // Display callback
    glutKeyboardFunc(key); // Keyboard input callback
    glutIdleFunc(idle); // Idle callback

    glShadeModel(GL_SMOOTH); // Smooth shading
    glEnable(GL_DEPTH_TEST); // Enable depth testing

    glutMainLoop(); // Enter the GLUT event processing loop

    return 0; // Standard C main function return
}
