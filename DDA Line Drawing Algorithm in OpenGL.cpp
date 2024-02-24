/**
 * DDA Line Drawing Algorithm in OpenGL
 * 
 * This program implements the Digital Differential Analyzer (DDA) algorithm to draw a line between two points in a 2D space. 
 * The DDA algorithm is a simple and efficient method to rasterize lines, relying on incremental calculations to plot the 
 * appropriate pixels that form the line. This implementation uses the OpenGL Utility Toolkit (GLUT) for rendering.
 * 
 * The program starts by asking the user to input the starting (x1, y1) and ending (x2, y2) coordinates of the line. It then 
 * initializes an OpenGL window and draws the calculated line on the screen using the DDA algorithm. The line is rendered as a 
 * series of GL_POINTS, with the step size determined by the greater difference in the x or y direction to ensure smoothness 
 * and accuracy.
 * 
 * Features:
 * - Input handling for starting and ending points of the line.
 * - OpenGL window initialization and configuration.
 * - Line drawing using the DDA algorithm.
 * 
 * How to Run:
 * Ensure you have OpenGL and GLUT installed on your system. Compile this program with a command appropriate for your 
 * compiler and environment. For example, using GCC on Linux:
 * 
 * gcc -o dda_line_algorithm dda_line_algorithm.c -lGL -lGLU -lglut
 * 
 * Then, run the program:
 * 
 * ./dda_line_algorithm
 * 
 * Enter the coordinates as prompted to see the line drawn in the window.
 */

#include<GL/glut.h>
#include<stdlib.h>
#include<stdio.h>

// Define global variables for starting and ending points
float x1,x2,y1,y2;

// Initialization function for OpenGL configurations
void init (void)
{
    // Set background color to light grey
    glClearColor(0.7,0.7,0.7,0.7); 
    // Set the projection matrix mode
    glMatrixMode(GL_PROJECTION);
    // Reset the projection matrix
    glLoadIdentity();
    // Set the orthogonal viewing volume (2D projection)
    gluOrtho2D(-100,100,-100,100);
}

// Function to display the line using DDA algorithm
void show(void)
{
    // Declare variables for differences and steps
    float dy,dx,step,x,y,i,Xin,Yin;

    // Calculate differences
    dx=x2-x1;
    dy=y2-y1;

    // Determine the number of steps based on the greater difference
    if(abs(dx) > abs(dy))
    {
        step=abs(dx);
    }
    else
    {
        step =abs(dy);
    }

    // Calculate the increment in x and y for each step
    Xin = dx/step;
    Yin = dy/step;

    // Start from the first point
    x=x1;
    y=y1;
    // Begin drawing points
    glBegin(GL_POINTS);
    // Set the initial point
    glVertex2i (x,y);
    glEnd();

    // Draw each point step by step
    for(i=1; i<=step; i++)
    {
        x=x+Xin;
        y=y+Yin;

        // Draw the current point
        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
    }

    // Flush the OpenGL buffers to the window
    glFlush();
}

// Main function
int main (int argc, char** argv)
{
    // Display the title and instructions
    printf("                      ===============================\n");
    printf("                             DDA ALGORITHM\n");
    printf("                      ===============================");

    // Input for the starting and ending points
    printf("\n\nEnter the value of x1: ");
    scanf("%f", &x1);
    printf("Enter the value of y1: ");
    scanf("%f", &y1);
    printf("Enter the value of x2: ");
    scanf("%f", &x2);
    printf("Enter the value of y2: ");
    scanf("%f", &y2);

    // Initialize GLUT
    glutInit(&argc, argv);
    // Set the display mode
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    // Set the initial window size
    glutInitWindowSize(500,500);
    // Set the initial window position
    glutInitWindowPosition(100,100);
    // Create the window with a title
    glutCreateWindow("DDA Line Algorithm");
    // Call the initialization function
    init();
    // Set the display callback function
    glutDisplayFunc(show);
    // Enter the GLUT main loop
    glutMainLoop();

    return
