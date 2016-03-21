#include "FullWindow.h"
FullWindow::FullWindow(int x, int y, int w, int h, char* c) :Fl_Window(x,y,w,h,c)
{
	gWin = new ThisWindow(5, 5, 500, 500, "GL Window");
	exitB = new Fl_Button(560, 570, 50, 20, "Exit");	// button for exiting the app
	exitB->callback(this->exitCB, 0);

	addB = new Fl_Button(515, 400, 100, 20, "Add Node");
	addB->callback(this->addCB, this->gWin);
	//Scale slider
	scaleB = new Fl_Slider(515, 450, 25, 50, "scale");
	gWin->setScale(scaleB);
	scaleB->bounds(0.1, 10.0);
	scaleB->value(5.0);
	scaleB->callback(this->scaleCB, this->gWin);
	//Rotation Dial
	rotateB = new Fl_Dial(480, 530, 50, 50, "rotation angle");
	gWin->setRotate(rotateB);
	rotateB->bounds(0.0, 1800.0);
	rotateB->callback(this->rotateCB, this->gWin);
	//Translate by x
	translateXB = new Fl_Slider(300, 540, 150, 25, "X Translate" );
	gWin->setxTrans(translateXB);
	translateXB->bounds(100.0, -100.0);
	translateXB->type(FL_HORIZONTAL);
	translateXB->callback(this->translateXCB, this->gWin);
	//Translate by y
	translateYB = new Fl_Slider(550, 250, 25, 100, "Y Translate");
	gWin->setyTrans(translateYB);
	translateYB->bounds(-100.0, 100.0);
	translateYB->value(0.0);
	translateYB->callback(this->translateYCB, this->gWin);
	//Delete Button
	deleteB = new Fl_Button(200, 560, 80, 20, "Delete");
	deleteB->callback(this->deleteCB, this->gWin);
	//Color Button
	colorB = new Fl_Button(50, 560, 120, 20, "Change Color");
	colorB->callback(this->colorCB, this->gWin);
}
FullWindow::~FullWindow()
{
	delete(gWin);
	delete(exitB);
	delete(colorB);
	delete(addB);
	gWin = NULL;
	exitB = NULL;
	colorB = NULL;
	addB = NULL;
}
//Exit the program.
void FullWindow::exitCB(Fl_Widget *w, void *data)
{
	cout << "exit" << endl;
	exit(0);
}
//Add a polygon-Square. Either as a child of a polygon or as an independent.
void FullWindow::addCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* toBeAddedTo = (Node*)Wind->getClicked()->user_data();
	cout << "Please give the Node a name: " ;
	char* name= new char[100];
	cin >> name;
	cout << endl;
	cout << "Please give the Node an ID: ";
	int ID;
	cin >> ID;
	cout << endl;
	if (toBeAddedTo != NULL && toBeAddedTo->getName() != "Build Tree")
	{
		toBeAddedTo->addNewChild(name, ID);
	}
	else
	{
		Shape2D* kind = new Shape2D(0);
		kind->addVertex(vec3(-1, -1, 1));
		kind->addVertex(vec3(-1, 1, 1));
		kind->addVertex(vec3(1, 1, 1));
		kind->addVertex(vec3(1, -1, 1));
		kind->setColor(0, 1, 0);
		Node* neuKind = new Node(kind, ID);
		neuKind->setName(name);
		Fl_Tree_Item* item = Wind->getTree()->add(neuKind->getName());
		item->user_data(neuKind);
		neuKind->setTree(Wind->getTree());
	}
	Wind->redraw();
}
//This is for the scaling slider to resize the polygons.
void FullWindow::scaleCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* cChange = (Node*)Wind->getClicked()->user_data();
	if (cChange != NULL)
	{
		if (!Wind->getScaleCtr())
		{
			float scaleVal = Wind->getScale()->value() / 5;
			cChange->scale(scaleVal, scaleVal, 0);
			Wind->setScaleVal(Wind->getScale()->value() / 5);
			Wind->incSCtr();
			Wind->redraw();
		}
		else
		{
			float scaleval = (Wind->getScaleVal() - (Wind->getScale()->value() / 5));
			if (scaleval > 0)
			{
				scaleval -= 1;
			}
			else
			{
				if (scaleval < 0)
				{
					scaleval = abs(scaleval);
					scaleval += 1.008;
				}
			}
			cChange->scale(abs(scaleval), abs(scaleval), 0);
			Wind->setScaleVal(Wind->getScale()->value() / 5);
			Wind->redraw();
		}
	}
}
//Callback for rotating the polygon.
void FullWindow::rotateCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* cChange = (Node*)Wind->getClicked()->user_data();
	if (cChange != NULL)
	{
		if (!Wind->getRotateCtr())
		{
			float rotateVal = Wind->getRotate()->value() / 5;
			cout << "Angle " << rotateVal << endl;
			cChange->rotate(rotateVal, 0);
			Wind->setAngleVal(rotateVal);
			Wind->incRCtr();
			Wind->redraw();
		}
		else
		{
			float rotateVal = (Wind->getAngleVal() - (Wind->getRotate()->value() / 5));
			cChange->rotate(rotateVal, 0);
			Wind->setAngleVal((Wind->getRotate()->value() / 5));
			Wind->redraw();
		}
	}
}
ThisWindow* FullWindow::getWindow()
{
	return gWin;
}
//Methods to translate by the x and y
void FullWindow::translateXCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* cChange = (Node*)Wind->getClicked()->user_data();
	if (cChange != NULL)
	{
		if (!Wind->getxTransCtr())
		{
			cChange->translate(Wind->getxTrans()->value(),0 , 0);
			Wind->setxTransVal(Wind->getxTrans()->value());
			Wind->incxTransCtr();
			Wind->redraw();
		}
		else
		{
			float xTrans = Wind->getxTransVal() - Wind->getxTrans()->value();
			cChange->translate(xTrans ,0 , 0);
			Wind->setxTransVal(Wind->getxTrans()->value());
			Wind->redraw();
		}
	}
}
void FullWindow::translateYCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* cChange = (Node*)Wind->getClicked()->user_data();
	if (cChange != NULL)
	{
		if (!Wind->getyTransCtr())
		{
			cout << "Amount in y-direction moved: " << Wind->getyTrans()->value() << endl;
			cChange->translate(0, Wind->getyTrans()->value() , 0);
			Wind->setYTransVal(Wind->getyTrans()->value());
			Wind->incyTransCtr();
			Wind->redraw();
		}
		else
		{
			float yTrans = Wind->getYTransVal() - Wind->getyTrans()->value();
			cChange->translate(0, yTrans, 0);
			Wind->setYTransVal(Wind->getyTrans()->value());
			Wind->redraw();
		}
	}
}
//Method to delete a polygon
void FullWindow::deleteCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* toBeDel = (Node*)Wind->getClicked()->user_data();
	if (toBeDel != NULL)
	{
		if (toBeDel->getParent() != NULL)
		{
			toBeDel->delNode();
		}
		Wind->getTree()->remove(Wind->getClicked());
		Wind->redraw();
	}
}
//Method to change color 
void FullWindow::colorCB(Fl_Widget *w, void *data)
{
	ThisWindow* Wind = (ThisWindow*)data;
	Node* colorChange = (Node*)Wind->getClicked()->user_data();
	if (colorChange != NULL)
	{
		int r, g, b;
		cout << "Please input the rgb value of the new color: ";
		cin >> r >> g >> b;
		cout << endl;
		colorChange->getGeometry()->setColor(r, g, b);
		Wind->redraw();
	}
}