#include <iostream>

#include "FullWindow.h"
#include <FL/Fl_Tree.H>
#include <FL/Fl_Group.H>
//Necessary Global Variables to get around the amound of args allowed in the callback
ThisWindow* window;
Fl_Tree *initTree;
Fl_Tree_Item* item;
FullWindow* Full;
Node* root;
int ctr = 0;
//Function defs.
void reMakeScene();
void treePop(Node* root);
using namespace std;


ThisWindow* drawAnimal(ThisWindow* wind)
{
	 // create a window
	Shape2D *square = new Shape2D(0);
	//This will be the body
	square->addVertex(vec3(-1, -1, 1));
	square->addVertex(vec3(-1, 1, 1));
	square->addVertex(vec3(1, 1, 1));
	square->addVertex(vec3(1, -1, 1));
	square->setColor(0, 1, 0);
	Node *body = new Node(square, 0);
	body->setName("body");
	//The triangle will be the body.
	Shape2D *triangle = new Shape2D(0);
	triangle->addVertex(vec3(-2, -11, 1));
	triangle->addVertex(vec3(3, 1, 1));
	triangle->addVertex(vec3(-5, 14, 1));
	triangle->setColor(0, 0, 1);
	//Make body bigger
	body->scale(9, 7, 1);
	Node *head = new Node(triangle, 1, body);
	head->setName("head");
	//Transformations on the body
	head->translate(15, 0, 1);
	head->rotate(-8, 1);
	head->scale(0.7, 0.5, 1);
	//These are the limbs, four lower limbs and four upper limbs
	Shape2D *ll_0 = new Shape2D(0);
	ll_0->addVertex(vec3(-1, -1, 1));
	ll_0->addVertex(vec3(-1, 1, 1));
	ll_0->addVertex(vec3(1, 1, 1));
	ll_0->addVertex(vec3(1, -1, 1));
	Shape2D *ul_0 = new Shape2D(0);
	ll_0->setColor(0, 1, 1);
	ul_0->addVertex(vec3(-1, -1, 1));
	ul_0->addVertex(vec3(-1, 1, 1));
	ul_0->addVertex(vec3(1, 1, 1));
	ul_0->addVertex(vec3(1, -1, 1));
	ul_0->setColor(1, 0, 0);
	//Create the nodes with the upper limb tied to the body and the lower limb to the upper limb
	Node *upper_0 = new Node(ul_0, 2, body);
	upper_0->setName("upper_0");
	Node *lower_0 = new Node(ll_0, 3, upper_0);
	lower_0->setName("lower_0");
	//These transformations are required to allow the limbs to be at the base of the dog
	upper_0->scale(1, 2, 1);
	lower_0->translate(0, -4, 1);
	upper_0->translate(-7, -9, 1);
	//The remaining limbs are done the same way as the above limbs
	Shape2D *ll_1 = new Shape2D(0);

	ll_1->addVertex(vec3(-1, -1, 1));
	ll_1->addVertex(vec3(-1, 1, 1));
	ll_1->addVertex(vec3(1, 1, 1));
	ll_1->addVertex(vec3(1, -1, 1));
	ll_1->setColor(1, 0, 0);
	Shape2D *ul_1 = new Shape2D(0);

	ul_1->addVertex(vec3(-1, -1, 1));
	ul_1->addVertex(vec3(-1, 1, 1));
	ul_1->addVertex(vec3(1, 1, 1));
	ul_1->addVertex(vec3(1, -1, 1));
	ul_1->setColor(0, 1, 1);
	Node *upper_1 = new Node(ul_1, 4, body);
	upper_1->setName("upper_1");
	Node *lower_1 = new Node(ll_1, 5, upper_1);
	lower_1->setName("lower_1");
	upper_1->scale(1, 2, 1);
	lower_1->translate(0, -4, 1);
	upper_1->translate(-3, -9, 1);
	Shape2D *ll_2 = new Shape2D(0);

	ll_2->addVertex(vec3(-1, -1, 1));
	ll_2->addVertex(vec3(-1, 1, 1));
	ll_2->addVertex(vec3(1, 1, 1));
	ll_2->addVertex(vec3(1, -1, 1));
	Shape2D *ul_2 = new Shape2D(0);
	ll_2->setColor(1, 0, 1);
	ul_2->addVertex(vec3(-1, -1, 1));
	ul_2->addVertex(vec3(-1, 1, 1));
	ul_2->addVertex(vec3(1, 1, 1));
	ul_2->addVertex(vec3(1, -1, 1));
	ul_2->setColor(1, 1, 0);
	Node *upper_2 = new Node(ul_2, 6, body);
	upper_2->setName("upper_2");
	Node *lower_2 = new Node(ll_2, 7, upper_2);
	lower_2->setName("lower_2");
	upper_2->scale(1, 2, 1);
	lower_2->translate(0, -4, 1);
	upper_2->translate(2, -9, 1);

	Shape2D *ll_3 = new Shape2D(0);

	ll_3->addVertex(vec3(-1, -1, 1));
	ll_3->addVertex(vec3(-1, 1, 1));
	ll_3->addVertex(vec3(1, 1, 1));
	ll_3->addVertex(vec3(1, -1, 1));
	ll_3->setColor(1, 1, 0);
	Shape2D *ul_3 = new Shape2D(0);

	ul_3->addVertex(vec3(-1, -1, 1));
	ul_3->addVertex(vec3(-1, 1, 1));
	ul_3->addVertex(vec3(1, 1, 1));
	ul_3->addVertex(vec3(1, -1, 1));
	ul_3->setColor(1, 0, 1);
	Node *upper_3 = new Node(ul_3, 8, body);
	upper_3->setName("upper_3");
	Node *lower_3 = new Node(ll_3, 9, upper_3);
	lower_3->setName("lower_3");
	upper_3->scale(1, 2, 1);
	lower_3->translate(0, -4, 1);
	upper_3->translate(6, -9, 1);
	//End the limbs and get the tail, the final piece of the puzzle.
	Shape2D *line = new Shape2D(1);
	line->addVertex(vec3(-1, -1, 1));
	line->addVertex(vec3(-1, 1, 1));
	line->addVertex(vec3(1, 1, 1));
	line->addVertex(vec3(1, -1, 1));
	Node *tail = new Node(line, 10, body);
	tail->setName("tail");
	//Scale and move the tail to the back of the dog and then rotate the tail
	tail->scale(5, 1, 1);
	tail->translate(-13, 2, 1);
	tail->rotate(20, 1);
	//Unused translations on the body itself, this should affect every other component now as they are all connected to the body.
	body->translate(0, 0, 1);
	body->rotate(0, 1);
	
	wind->setRoot(body);
	//Draw everything. Woo!
	wind->show();  // show the window
	wind->redraw();
	return wind;
}

void TreeCallback(Fl_Widget *w, void *parm)
{
	Fl_Tree *tree = (Fl_Tree*)w;
	initTree = (Fl_Tree*)w;
	// Find item that was clicked
	Fl_Tree_Item *item = (Fl_Tree_Item*)tree->item_clicked();
	if (item)
	{
		Node* node = (Node*)item->user_data();
		if (node != NULL)
		{
			//If redraw button is pressed, remake the scene
			if (node->getName() == "Redraw Button")
			{
				reMakeScene();
			}
			//Connect the window with the scene graph to the Tree diagram
			window->setClicked(item);
			window->setTree(initTree);
			//Reset buttons to default states
			window->getRotate()->value(0);
			window->getScale()->value(5);
			window->getxTrans()->value(0);
			window->getyTrans()->value(0);
			//Call the recursive function to populate the tree.
			if (node->getName() == "Build Tree" && !ctr)
			{
				treePop(root);
				ctr++;
			}
		}
	}
	else
	{
		std::cout << "No item selected?" << std::endl;
	}

}
void treePop(Node* root)
{
	//Recursive method for populating the tree.
	item = initTree->add(root->getName());
	item->user_data(root);
	root->setTree(initTree);
	list<Node*>::iterator obj = root->getChildren();
	for (obj; obj != root->lastChild(); ++obj)
	{
		//Change names to properly add children as children of their parents
		char* name = new char[10000];
		strcpy_s(name, 10000, (*obj)->getParent()->getName());
		strcat_s(name, 10000, "/");
		strcat_s(name, 10000, (*obj)->getName());

		(*obj)->setName(name);
		treePop(*obj);
	}
}
int main (int argc, char * const argv[]) 
{
	Full = new FullWindow(100, 100, 620, 600, "Scene Graph");
	window = drawAnimal(Full->getWindow());
	
	Fl_Window* win = new Fl_Window(10, 10, 500, 500, "Tree Linker");
	Fl_Tree tree(10, 10, win->w() - 20, win->h() - 20);
	root = window->getRoot();
	item = tree.add("Build Tree");
	Node* temp = new Node(new Shape2D(1), 57);
	temp->setName("Build Tree");
	item->user_data(temp);
	item = tree.add("Redraw!");
	Node* redraw = new Node(new Shape2D(1), 56);
	redraw->setName("Redraw Button");
	item->user_data(redraw);
	tree.callback(TreeCallback, (void*)1234);
	win->end();
	win->resizable(win);
	win->show();
	Full->show();
	return Fl::run(); // tell FLTK to go
	system("PAUSE");
}

void reMakeScene()
{
	//Deletes the previous window and remakes a new one
	Full->hide();
	ctr = 0;
	main(0, {});
}
