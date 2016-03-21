#include "Obj.h"

MyWindow::MyWindow(int x, int y, int w, int h, char* c):Fl_Gl_Window(x, y, w, h, c)
{}

void 
MyWindow::draw(){  // FLTK method
		if (!valid()){  // FLTK housekeeping
			valid(1);
			
			// glViewport specifies the affine transformation of x and y from normalized device coordinates to window coordinates.
			glViewport(0,0,w(),h());  // lower left coordinate and width and height

			//glOrtho describes a transformation that produces a parallel projection.
			glOrtho(-10,10,-10,10,-1,1);  // left, right, bottom, top, near, far
		}

		glClearColor(2, 3.0, 4.0, 5.0);				// Set the background color
		glClear(GL_COLOR_BUFFER_BIT);

		// Should be calling scene graph
		// Should be calling class that draws shapes

		// Green polygon
		glColor3f(0, 1, 0);
		glBegin(GL_POLYGON);
		glVertex2f(-2, -11);
		glVertex2f(3, 1);
		glVertex2f(-5, 14);
		glVertex2f(8, 2);
		glVertex2f(4, 11.5);
		glEnd();

		// Red rectangle
		glColor3f(1, 0, 0);  // drawing color, red, green, blue
		glBegin(GL_QUADS);   // draw a solid cube
			glVertex2f(-1, -1);
			glVertex2f(-1, 1);
			glVertex2f(1, 1);
			glVertex2f(1, -1);
		glEnd();

		// Blue polygon
		glColor3f(0,0,1);
		glBegin(GL_LINE_LOOP);
			glVertex2f(-12, -1);
			glVertex2f(-15, 4);
			glVertex2f(13, 1);
			glVertex2f(14, 1.5);
			glVertex2f(18, 2);
		glEnd();

		// Yellow triangle
		glColor3f(1,0.4,0);
		glBegin(GL_TRIANGLES);
			glVertex2f(-1, 0);
			glVertex2f(0, 1);
			glVertex2f(1, 0);
		glEnd();
	}

