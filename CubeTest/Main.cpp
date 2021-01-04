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
    void InitGL() override;
    void Render() override;
    void KeyBoard(unsigned char key) override;
    void SpecialKey(int keyCode) override;

    static void DrawCube(GLfloat s);

private:
    CubeApp() : angle(glm::radians(15.0f)), model(1.0f), shading(GL_FLAT), showAxis(false) {
        // ctor
    }

    const GLfloat angle;    //< rotation angle
    glm::mat4 model;        //< current object matrix
    GLint shading;          //< current shading model
    bool showAxis;          //< flag to control axis drawing

    friend class GlutApp;
};

int main(int argc, char** argv) {
    auto& app = CubeApp::Make();

    app->Init(&argc, argv);
    app->OpenWindow("Cube Test", 640, 480, 100, 100);
    app->Run();

    return 0;
}

#pragma region "CubeApp Implementations"

void CubeApp::Render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, GetAspectRatio(), 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 15.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glMultMatrixf(glm::value_ptr(model));
    DrawCube(5.0f); // glutSolidCube(5.0f);

    if (showAxis) {
        glDisable(GL_LIGHTING);
        DrawAxis(10.0f);
        glEnable(GL_LIGHTING);
    }
}

void CubeApp::KeyBoard(unsigned char key) {
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

void CubeApp::SpecialKey(int keyCode) {
    switch (keyCode)
    {
    case GLUT_KEY_HOME:
        model = glm::mat4(1.0f);
        break;

    case GLUT_KEY_F1:
        showAxis = !showAxis;
        break;

    case GLUT_KEY_F2:
        // swap shading model
        shading = GL_FLAT + GL_SMOOTH - shading;
        glShadeModel(shading);
    }
    Redisplay();
}

void CubeApp::InitGL() {
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

    // set shading model to flat
    glShadeModel(shading);
    // increase default line width
    glLineWidth(2.0f);
}

void CubeApp::DrawCube(GLfloat s) {
    s = s * 0.5f;

    GLfloat cubeData[] = {
        // include the vertex and normals coordinate values
        #include "cube.dat"
    };

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);

    glVertexPointer(3, GL_FLOAT, 6 * sizeof(GLfloat), &cubeData[0]);
    glNormalPointer(GL_FLOAT, 6 * sizeof(GLfloat), &cubeData[3]);
    glDrawArrays(GL_TRIANGLES, 0, 6 * 2 * 3);

    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

#pragma endregion