#include "Window.h"

Window::Window(int x, int y, int w, int h, char* c) :Fl_Gl_Window(x, y, w, h, c)
{}
void Window::draw()
{
	if (!valid()){						// Some housekeeping
		valid(1);
		glLoadIdentity();				// Prepare the OpenGL stack
		glViewport(0, 0, w(), h());		// Create a viewport 
		glOrtho(-50, 50, -50, 50, -1, 1);		// Create a projection
	}
	glClearColor(2, 3.0, 4.0, 5.0);
	glClear(GL_COLOR_BUFFER_BIT);
	//Make drawings starting with the root node.
	root->draw();
}
void Window::setRoot(Node *node)
{
	root = node;
}