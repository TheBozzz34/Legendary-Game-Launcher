#pragma once

#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <GL/glui.h>
#include "launch.h"


int   wireframe = 0;
int   segments = 8;
int   main_window;

GLUI* glui_window;

void GlutIdle(void)
{
    /* According to the GLUT specification, the current window is
       undefined during an idle callback.  So we need to explicitly change
       it if necessary 
    if (glutGetWindow() != main_window)
    glutSetWindow(main_window);
    */

    glutPostRedisplay();
}


void GlutReshape(int x, int y)
{
    float xy_aspect;

    xy_aspect = (float)x / (float)y;
    glViewport(0, 0, x, y);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-xy_aspect * .08, xy_aspect * .08, -.08, .08, .1, 15.0);

    glutPostRedisplay();
}

void GlutDisplay(void)
{
    static float rotationX = 0.0, rotationY = 0.0;

    glClearColor(.9f, .9f, .9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glutSwapBuffers();
}

void button_callback()
{
    std::cout << "Button pressed." << std::endl;
}


int gui(int* argcp, char** argv)
{

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    try {
        glutInit(argcp, argv);
        std::cout << "GLUT initialized sucessfully." << std::endl;
    }
    catch (std::exception& e) {
		glfwTerminate();
        std::cout << "Failed to initialize GLUT" << std::endl;
		throw;
	}

    
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(300, 300);
    main_window = glutCreateWindow("GLUI Example 1");

    glutDisplayFunc(GlutDisplay);
    glutReshapeFunc(GlutReshape);

    /****************************************/
    /*       Set up OpenGL lights           */
    /****************************************/

    GLfloat light0_ambient[] = { 0.1f, 0.1f, 0.3f, 1.0f };
    GLfloat light0_diffuse[] = { .6f, .6f, 1.0f, 1.0f };
    GLfloat light0_position[] = { 1.0f, 1.0f, 1.0f, 0.0f };

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);

    /****************************************/
    /*          Enable z-buffering          */
    /****************************************/

    glEnable(GL_DEPTH_TEST);

    /****************************************/
    /*         Here's the GLUI code         */
    /****************************************/

    GLUI* glui = GLUI_Master.create_glui_subwindow(main_window, GLUI_SUBWINDOW_TOP);

    GLUI_Button* button = new GLUI_Button(glui, "Button", 0, (GLUI_Update_CB)button_callback);
    GLUI_Button* quit_bitton = new GLUI_Button(glui, "Quit", 0, (GLUI_Update_CB)exit);
    glui->set_main_gfx_window(main_window);

    button->set_w(180);


    

    /* We register the idle callback with GLUI, *not* with GLUT */
    GLUI_Master.set_glutIdleFunc(GlutIdle);

    glutMainLoop();
    
    return 0;
}
