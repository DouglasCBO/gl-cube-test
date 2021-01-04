#pragma once

#include <GL\glew.h>
#include <GL\freeglut.h>

#include <memory>
#include <string>
#include <tuple>

namespace dgl
{
	class GlutApp
	{
	public:
		// creates the application instance from a derived application class
		template <class TApp, typename... Args>
		static const std::unique_ptr<GlutApp>& Make(Args... args) {
			static_assert(std::is_base_of_v<GlutApp, TApp>, "TApp doesn't implement GlutApp interface");
			if (!pSelf) {
				pSelf.reset(new TApp(args...));
			}
			return pSelf;
		}

		// destructor
		virtual ~GlutApp() {
			CloseWindow();
		}

		// initialize GLUT
		void Init(int* argc, char* argv[]);
		// creates a window with a title and size [w x h] at position (x, y)
		void OpenWindow(const std::string& title, GLint w, GLint h, GLint x = 0, GLint y = 0);
		// destroys the current window
		void CloseWindow();

		// starts the application
		void Run();

		GLfloat GetAspectRatio() const { return GLfloat(this->width) / this->heigth; }
		std::tuple<int, int> GetWindowSize() const { return { this->width, this->heigth }; }
		std::tuple<int, int> GetMousePosition() const { return { this->mousex, this->mousey }; }

		// disable the copy and move constructors and operators
		GlutApp(const GlutApp&) = delete;
		GlutApp(GlutApp&&) = delete;
		GlutApp& operator = (const GlutApp&) = delete;
		GlutApp& operator = (GlutApp&&) = delete;

	protected:
		GlutApp() : winID(-1), width(0), heigth(0), mousex(0), mousey(0) {/* ctor */ }

		// user-defined opengl initializer (callable once after window context was created)
		virtual void InitGL() = 0;
		// user-defined renderer
		virtual void Render() = 0;
		// user-defined printable keyboard event handler
		virtual void KeyBoard(unsigned char key) = 0;
		// user-defined unprintable keyboard event handler
		virtual void SpecialKey(int keyCode) = 0;

		// redraw elements
		void Redisplay();
		// draw xyz-axis at a given scale
		void DrawAxis(GLfloat s);

	private:
		GLint winID;
		GLint width, heigth;
		GLint mousex, mousey;

		static std::unique_ptr<GlutApp> pSelf;

		// event callbacks declaration
		static void DisplayCallback();
		static void KeyBoardCallback(unsigned char, int, int);
		static void SpecialKeyCallback(int, int, int);
		static void ReshapeCallback(int, int);
	};
}