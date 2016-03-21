#include "ThisWindow.h"

ThisWindow::ThisWindow(int x, int y, int w, int h, char* c) :Fl_Gl_Window(x, y, w, h, c)
{
	scaleCtr = 0;
	rotateCtr = 0;
	xTransCtr = 0;
	yTransCtr = 0;
}
void ThisWindow::draw()
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
void ThisWindow::setRoot(Node *node)
{
	root = node;
}
Node* ThisWindow::getRoot()
{
	return root;
}
Fl_Button* ThisWindow::getRedraw()
{
	return drawAgain;
}
Fl_Slider* ThisWindow::getScale()
{
	return scale;
}
Fl_Dial* ThisWindow::getRotate()
{
	return rotate;
}
Fl_Slider* ThisWindow::getxTrans()
{
	return xTrans;
}
Fl_Slider* ThisWindow::getyTrans()
{
	return yTrans;
}
void ThisWindow::setRedraw(Fl_Button* button)
{
	drawAgain = button;
}
void ThisWindow::setScale(Fl_Slider* slider)
{
	scale = slider;
}
void ThisWindow::setRotate(Fl_Dial* dial)
{
	rotate = dial;
}
void ThisWindow::setxTrans(Fl_Slider* slider)
{
	xTrans = slider;
}
void ThisWindow::setyTrans(Fl_Slider* slider)
{
	yTrans = slider;
}
float ThisWindow::getScaleVal()
{
	return scaleVal;
}
float ThisWindow::getAngleVal()
{
	return angleVal;
}
void ThisWindow::setScaleVal(float num)
{
	scaleVal = num;
}
void ThisWindow::setAngleVal(float num)
{
	
	angleVal = num;
}
int ThisWindow::getScaleCtr()
{
	return scaleCtr;
}
int ThisWindow::getRotateCtr()
{
	return rotateCtr;
}
void ThisWindow::incSCtr()
{
	scaleCtr++;
}
void ThisWindow::incRCtr()
{
	rotateCtr++;
}
float ThisWindow::getYTransVal()
{
	return yTransVal;
}
float ThisWindow::getxTransVal()
{
	return xTransVal;
}
void ThisWindow::setYTransVal(float num)
{
	yTransVal = num;
}
void ThisWindow::setxTransVal(float num)
{
	xTransVal = num;
}
int ThisWindow::getyTransCtr()
{
	return yTransCtr;
}
void ThisWindow::incyTransCtr()
{
	yTransCtr++;
}
int ThisWindow::getxTransCtr()
{
	return xTransCtr;
}
void ThisWindow::incxTransCtr()
{
	xTransCtr++;
}
void ThisWindow::setClicked(Fl_Tree_Item* node)
{
	itemClicked = node;
}
Fl_Tree_Item* ThisWindow::getClicked()
{
	return itemClicked;
}
void ThisWindow::setTree(Fl_Tree* ntree)
{
	tree = ntree;
}
Fl_Tree* ThisWindow::getTree()
{
	return tree;
}