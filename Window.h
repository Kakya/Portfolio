#include "Node.h"
class Window :public Fl_Gl_Window
{
private:
	Node *root;
public:
	void draw();
	void setRoot(Node *node);
	Window(int x, int y, int w, int h, char* c);
};