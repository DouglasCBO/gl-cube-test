#include "GlutApp.hpp"

#include <glm\mat4x4.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <glm\gtx\string_cast.hpp>
#include <glm\ext\matrix_transform.hpp>

class CubeApp : public dgl::GlutApp
{
public:
    static const std::unique_ptr<GlutApp>& Make() {
        return GlutApp::Make<CubeApp>();
    }

private:    
    void Render() {
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0, GetAspectRatio(), 1.0, 100.0);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

        glMultMatrixf(glm::value_ptr(model));
        glutSolidCube(5.0f);
    }
    
    void KeyBoard(unsigned char key) {
        switch (tolower(key))
        {
            case 27: // ESC: Exit
                CloseWindow();
                return;

                // apply a dtheta radians rotation on the current model around each axis
            case 'q': model = glm::rotate(model, +angle, glm::vec3(1, 0, 0)); break; // +x
            case 'a': model = glm::rotate(model, -angle, glm::vec3(1, 0, 0)); break; // -x

            case 'w': model = glm::rotate(model, +angle, glm::vec3(0, 1, 0)); break; // +y
            case 's': model = glm::rotate(model, -angle, glm::vec3(0, 1, 0)); break; // -y

            case 'e': model = glm::rotate(model, +angle, glm::vec3(0, 0, 1)); break; // +z
            case 'd': model = glm::rotate(model, -angle, glm::vec3(0, 0, 1)); break; // -z
        }
        Redisplay();
    }
    
    void SpecialKey(int keyCode) {
        if (keyCode == GLUT_KEY_HOME) {
            model = glm::mat4(1.0f);
        }
        Redisplay();
    }

    void InitGL() {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_DEPTH_TEST);

        GLfloat lightColor[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat lightPosition[] = { 50.0, 50.0, 50.0, 1.0 };

        glLightfv(GL_LIGHT0, GL_AMBIENT, lightColor);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightColor);
        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    }

private:
    CubeApp() : angle(glm::radians(15.0f)), model(1.0f) {
        // ctor
    }

    const GLfloat angle;
    glm::mat4 model;

    friend class GlutApp;
};

int main(int argc, char** argv) {
    auto& app = CubeApp::Make();

    app->Init(&argc, argv);
    app->OpenWindow("Cube Test", 640, 480, 100, 100);
    app->Run();

    return 0;
}
