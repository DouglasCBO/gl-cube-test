#include "GlutApp.hpp"

class CubeApp : public dgl::GlutApp
{
public:
    static const std::unique_ptr<GlutApp>& Make() {
        return GlutApp::Make<CubeApp>();
    }

private:
    void InitGL() {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

        GLfloat lightColor[]    = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat lightPosition[] = { 50.0, 50.0, 50.0, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    }
    
    void Render() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.0, GetAspectRatio(), 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(10.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glutSolidCube(5.0f);
    }
    
    void KeyBoard(unsigned char key) {
        switch (tolower(key))
        {
        case 27: // ESC: Exit
            CloseWindow();
            return;
        }
    }
    
    void SpecialKey(int keyCode) {
        // TODO
    }

    friend class GlutApp;
};

int main(int argc, char** argv) {
    auto& app = CubeApp::Make();

    app->Init(&argc, argv);
    app->OpenWindow("Cube Test", 640, 480, 100, 100);
    app->Run();

    return 0;
}
