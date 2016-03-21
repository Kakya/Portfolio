#include "Shapes.h"
#include <FL/Fl_Tree.H>
class Node
{
private:
	//geometry will be a pointer to the shape associated with the node
	Shape2D *geometry;
	//This will be the list of children of this node
	list<Node*> children;
	//ID of the node
	int ID;
	//The parent of the node
	Node *parent;
	char* name;
	Fl_Tree* tree;
public:
	//Nodes need to be initialized with a shape attached to them and an ID
	Node(Shape2D *shape, int ID);
	Node(Shape2D *shape, int ID, Node *node);
	//method to add to the children
	void addChild(Node *child);
	void addNewChild(char* name, int ID);
	//method to delete the node.
	void delNode();
	//delete children from the node.
	void delChild(int num);
	//set and get the ID.
	void setID(int num);
	int getID();
	//set and get the parent node.
	void setParent(Node *node);
	Node* getParent();
	//get a pointer to the first child
	list<Node*>::iterator getChildren();
	list<Node*>::iterator lastChild();
	list<Node*> getAllChilds();
	//method for transforming nodes.
	void scale(float x, float y, int toChild);
	void translate(float x, float y, int toChild);
	void rotate(float angle, int toChild);
	//calls the draw method of the geometry associated with the node
	void draw();
	Shape2D* getGeometry();
	friend bool operator==(Node v1, Node v2);
	void setName(char* string);
	char* getName();
	void setTree(Fl_Tree* ntree);
};