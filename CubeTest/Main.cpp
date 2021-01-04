#include "GlutApp.hpp"

class CubeApp : public dgl::GlutApp
{
public:
    static const std::unique_ptr<GlutApp>& Make() {
        return GlutApp::Make<CubeApp>();
    }

private:
    void InitGL() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    void Render() {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_POLYGON);
        glVertex2f(0.0, 0.0);
        glVertex2f(0.5, 0.0);
        glVertex2f(0.5, 0.5);
        glVertex2f(0.0, 0.5);
        glEnd();
        glFlush();
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
};

int main(int argc, char** argv) {
    auto& app = CubeApp::Make();

    app->Init(&argc, argv);
    app->OpenWindow("Cube Test", 300, 300, 100, 100);
    app->Run();

    return 0;
}