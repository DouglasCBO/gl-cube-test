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

        glutInitWindowSize(w, h);
        glutInitWindowPosition(x, y);
        glutInitDisplayMode(GLUT_SINGLE);
        this->winID = glutCreateWindow(title.c_str());
        
        InitGL();

        // sets the callback functions
        glutDisplayFunc(&GlutApp::DisplayCallback);
        glutKeyboardFunc(&GlutApp::KeyBoardCallback);
        glutSpecialFunc(&GlutApp::SpecialKeyCallback);
        glutReshapeFunc(&GlutApp::ReshapeCallback);
    }

    void GlutApp::CloseWindow()
    {
        glutDestroyWindow(this->winID);
        glutLeaveMainLoop();
        this->winID = -1;
    }

    void GlutApp::Run()
    {
        glutMainLoop();
    }

    void GlutApp::Redisplay() {
        glutPostRedisplay();
    }

#pragma region "Callbacks Implementation Section"
    // --------------------------------------------------------------------------------------------------------------------------
    // Basically updates the application properties and calls the correspondent virtual method to run the user-defined handlers.
    // --------------------------------------------------------------------------------------------------------------------------

    void GlutApp::DisplayCallback()
    {
        pSelf->Render();
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