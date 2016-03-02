#include "Shapes.h"

class Node
{
private:
	//geometry will be a pointer to the shape associated with the node
	shape *geometry;
	//This will be the list of children of this node
	list<Node*> children;
	//ID of the node
	int ID;
	//The parent of the node
	Node *parent;
public:
	//Nodes need to be initialized with a shape attached to them and an ID
	Node(shape *shape, int ID);
	Node(shape *shape, int ID, Node *node);
	//method to add to the children
	void addChild(Node *child);
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
	//method for transforming nodes.
	void scale(float x, float y);
	void translate(float x, float y);
	void rotate(float angle);
	//calls the draw method of the geometry associated with the node
	void draw();
	friend bool operator==(Node v1, Node v2);
};