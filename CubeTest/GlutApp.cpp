#include "GlutApp.hpp"

#include <iostream>

using namespace std;

namespace dgl
{
    // create the unique instance of GlutApp class
    unique_ptr<GlutApp> GlutApp::pSelf;

    void GlutApp::Init(int* argc, char* argv[])
    {
        glutInit(argc, argv);
    }

    void GlutApp::OpenWindow(const string& title, GLint w, GLint h, GLint x, GLint y)
    {
        if (this->winID != -1) return;
        this->width = w;
        this->heigth = h;

        // setup window size and position
        glutInitWindowSize(w, h);
        glutInitWindowPosition(x, y);
        // request double buffered rendering with depth component
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
        // create the window
        this->winID = glutCreateWindow(title.c_str());
        
        // calls user-defined opengl initialization
        InitGL();

        // sets the callback functions
        glutDisplayFunc(&GlutApp::DisplayCallback);
        glutKeyboardFunc(&GlutApp::KeyBoardCallback);
        glutSpecialFunc(&GlutApp::SpecialKeyCallback);
        glutReshapeFunc(&GlutApp::ReshapeCallback);
    }

    void GlutApp::CloseWindow()
    {
        // destroy the created window and goes off the main loop
        glutDestroyWindow(this->winID);
        glutLeaveMainLoop();
        this->winID = -1;
    }

    void GlutApp::Run()
    {
        // start application main loop
        glutMainLoop();
    }

    void GlutApp::Redisplay() {
        // request the screen update
        glutPostRedisplay();
    }

    void GlutApp::DrawAxis(GLfloat s) {
        glScalef(s, s, s);
        // draws xyz axis
        glBegin(GL_LINES);
        glColor3ub(128, 0, 0);  // red x-axis
        glVertex3f(-0.5f, 0.0f, 0.0f);
        glVertex3f(+0.5f, 0.0f, 0.0f);

        glColor3ub(0, 128, 0);  // green y-axis
        glVertex3f(0.0f, -0.5f, 0.0f);
        glVertex3f(0.0f, +0.5f, 0.0f);

        glColor3ub(0, 0, 128);  // blue z-axis
        glVertex3f(0.0f, 0.0f, -0.5f);
        glVertex3f(0.0f, 0.0f, +0.5f);
        glEnd();

        // draw the arrowhead
        // +z direction
        glPushMatrix();
        glTranslated(0.0, 0.0, 0.5);
        glutSolidCone(0.01, 0.02, 8, 8);
        glPopMatrix();
        // +y direction
        glColor3ub(0, 128, 0);
        glPushMatrix();
        glTranslated(0.0, 0.5, 0.0);
        glRotated(-90, 1.0, 0.0, 0.0);
        glutSolidCone(0.01, 0.02, 8, 8);
        glPopMatrix();
        // +x direction
        glColor3ub(128, 0, 0);
        glPushMatrix();
        glTranslated(0.5, 0.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glutSolidCone(0.01, 0.02, 8, 8);
        glPopMatrix();
    }

#pragma region "Callbacks Implementation Section"
    // --------------------------------------------------------------------------------------------------------------------------
    // Basically updates the application properties and calls the correspondent virtual method to run the user-defined handlers.
    // --------------------------------------------------------------------------------------------------------------------------

    void GlutApp::DisplayCallback()
    {
        pSelf->Render();
        glutSwapBuffers();
    }

    void GlutApp::KeyBoardCallback(unsigned char key, int x, int y)
    {
        pSelf->mousex = x;
        pSelf->mousey = y;
        pSelf->KeyBoard(key);
    }

    void GlutApp::SpecialKeyCallback(int keyCode, int x, int y)
    {
        pSelf->mousex = x;
        pSelf->mousey = y;
        pSelf->SpecialKey(keyCode);
    }

    void GlutApp::ReshapeCallback(int w, int h)
    {
        pSelf->width = w;
        pSelf->heigth = h;
        glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    }

#pragma endregion

}