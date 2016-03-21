#include "Node.h"
#include <FL/Fl_Button.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Dial.H>
#include <Fl/Fl_Slider.H>
class ThisWindow :public Fl_Gl_Window
{
private:
	Node *root;
	Fl_Button* drawAgain;
	Fl_Slider* scale;
	Fl_Dial* rotate;
	Fl_Slider* xTrans;
	Fl_Slider* yTrans;
	float scaleVal;
	float angleVal;
	float yTransVal;
	float xTransVal;
	int scaleCtr;
	int rotateCtr;
	int xTransCtr;
	int yTransCtr;
	Fl_Tree_Item* itemClicked;
	Fl_Tree* tree;
public:
	void draw();
	void setRoot(Node *node);
	Node* getRoot();
	ThisWindow(int x, int y, int w, int h, char* c);
	//Get four buttons and sliders
	Fl_Button* getRedraw();
	Fl_Slider* getScale();
	Fl_Dial* getRotate();
	Fl_Slider* getxTrans();
	Fl_Slider* getyTrans();
	//set the sliders
	void setRedraw(Fl_Button* button);
	void setScale(Fl_Slider* slider);
	void setRotate(Fl_Dial* dial);
	void setxTrans(Fl_Slider* slider);
	void setyTrans(Fl_Slider* slider);
	//Methods for setting and getting values
	float getScaleVal();
	float getAngleVal();
	void setScaleVal(float num);
	void setAngleVal(float num);
	int getScaleCtr();
	void incSCtr();
	int getRotateCtr();
	void incRCtr();
	//Methods for x and y translation
	float getYTransVal();
	float getxTransVal();
	void setYTransVal(float num);
	void setxTransVal(float num);
	int getyTransCtr();
	void incyTransCtr();
	int getxTransCtr();
	void incxTransCtr();
	//Methods for interfacing with the Fl_Tree
	void setClicked(Fl_Tree_Item* node);
	Fl_Tree_Item* getClicked();
	void setTree(Fl_Tree* ntree);
	Fl_Tree* getTree();
};