#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>

class MyWindow:public Fl_Gl_Window  // subclass of Fl_Gl_Window
{
private:
	void draw();  // method in FL_GL_Window class
public:
	MyWindow(int x, int y, int w, int h, char* c);
};