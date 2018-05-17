//
//  main.cpp
//  ComGraph_Project_2
//
//  Created by mac on 5/17/18.
//  Copyright © 2018 mac. All rights reserved.
//

// For MacOs users
#include <GLUT/glut.h>
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>


/*
 
 // For Windows users
 #include <GL/glut.h>
 #include <GL/gl.h>
 #include <GL/glu.h>
 
 */


#include <iostream>

using namespace std;

static GLfloat fovy = 30.1;
static GLfloat angle = 0.0;
static GLfloat trans = 0.0;
static GLfloat aspect;



void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0); // this is used to give back color to the window
    glShadeModel (GL_FLAT);
}



void drawWireSphere()
{
    
    glPushMatrix();
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fovy, aspect, .1, 100.);
    glTranslatef(trans, .0, .0);
    glRotatef(angle, .0, .0, .1);
    
    glutWireSphere(1.0, 20, 16);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

}

void display(void)
{
    glClear (GL_COLOR_BUFFER_BIT);
    glColor3f (.0, .0, .0);
    glLoadIdentity ();             /* clear the matrix */
    /* viewing transformation  */
    gluLookAt (.0, .0, 5.0, 0.0, 0.0, .0, 0.0, 1.0, 0.0);
    //glTranslatef(.0, .0, -5.);
    
    
    /*
     
     glLookAt is originally at 0,0,0 and the glutWire Cube is drawn at 0,0,0 that is where the camera is. So glLookAt(0,0,5) moves the camera back in Z axis which means the object is moving away from camera and becoming visible
     
     glTranslate(0,0,-5) just moves the object away from the camera which gives the same effect.
     
     */
    
    drawWireSphere();

    glFlush ();
}

void reshape (int w, int h)
{
    if (h == 0) h = 1;                // To prevent divide by 0
    aspect = (GLfloat)w / (GLfloat)h;
    
    // Set the viewport to cover the new window
    glViewport(0, 0, w, h);
    
    // Set the aspect ratio of the clipping volume to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset
    // Enable perspective projection with fovy, aspect, zNear and zFar
    gluPerspective(fovy, aspect, .1f, 100.0f);
    
    glMatrixMode(GL_MODELVIEW);
    
}

void myKeyboardFunc(unsigned char key, int, int)
{
    switch(key)
    {
        case 'i':
            fovy+=5;
            glutPostRedisplay();
            break;
        case 'o':
            fovy-=5;
            glutPostRedisplay();
            break;
        case 'l':
            trans-=.1;
            angle-=10;
            glutPostRedisplay();
            
            break;
        case 'r':
            trans+=.1;
            angle+=10;
            glutPostRedisplay();
            
            break;
        default : break;
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutKeyboardFunc(myKeyboardFunc);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}
