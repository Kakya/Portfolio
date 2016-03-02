#include "Node.h"

Node::Node(shape *shape, int ID)
{
	//Initialize the geometry and ID
	geometry = shape;
	setID(ID);
	parent = NULL;
}
Node::Node(shape *shape, int ID, Node *node)
{
	//Initialize the geometry and ID
	geometry = shape;
	setID(ID);
	parent = node;
	//Add this Node as a child of the parent
	node->addChild(this);
}
//method to add to the children
void Node::addChild(Node *child)
{
	children.push_back(child);
}
//method to delete the node by removing it from its parent's list of children.
void Node::delNode()
{
	int delID = getID();
	parent->delChild(delID);
}
//Use the ID to find the child in the list of children, then delete it
void Node::delChild(int num)
{
	list<Node*>::iterator iter = getChildren();
	for (iter; *iter != *children.end(); ++iter)
	{
		if ((*(*iter)).getID() == num)
		{
			children.remove((*iter));
		}
	}
}
//set and get the ID.
void Node::setID(int num)
{
	ID = num;
}
int Node::getID()
{
	return ID;
}
//set and get the parent.
void Node::setParent(Node *node)
{
	parent = node;
}
Node* Node::getParent()
{
	return parent; 
}
//get the first child of the node 
list<Node*>::iterator Node::getChildren()
{
	return children.begin();
}
//get the last child 
list<Node*>::iterator Node::lastChild()
{
	return children.end();
}
//methods for transforming the scene graph.
void Node::scale(float x, float y)
{
	mat3 *m = new mat3();
	mat3 scale = m->scale2D(x, y);
	//Apply the transformation to every vertex in the underlying geometry
	list<vec3>::iterator vert = geometry->getVertices();
	for (vert; vert != geometry->lastVertex(); ++vert)
	{
		(*vert) = scale*(*vert);
	}
	//Loop through the children of this node and apply the transform.
	list<Node*>::iterator child = children.begin();
	for (child; child != children.end(); ++child)
	{
		(*child)->scale(x,y);
	}
}
void Node::translate(float x, float y)
{
	mat3 *m = new mat3();
	mat3 translate = m->translation2D(x, y);
	list<vec3>::iterator vert = geometry->getVertices();
	//Apply the transformation to every vertex in the underlying geometry
	for (vert; vert != geometry->lastVertex(); ++vert)
	{
		(*vert) = translate*(*vert);
	}
	//Loop through the children of this node and apply the transform.
	list<Node*>::iterator child = children.begin();
	for (child; child != children.end(); ++child)
	{
		(*child)->translate(x, y);
	}
}
void Node::rotate(float angle)
{
	mat3 *m = new mat3();
	mat3 rotate = m->rotation2D(angle);
	list<vec3>::iterator vert = geometry->getVertices();
	//Apply the transformation to every vertex in the underlying geometry
	for (vert; vert != geometry->lastVertex(); ++vert)
	{
		(*vert) = rotate*(*vert);
	}
	//Loop through the children of this node and apply the transform.
	list<Node*>::iterator child = children.begin();
	for (child; child != children.end(); ++child)
	{
		(*child)->rotate(angle);
	}
}
void Node::draw()
{
	geometry->draw();
	list<Node*>::iterator child = children.begin();
	for (child; child != children.end(); ++child)
	{
		(*child)->draw();
	}
}
bool operator==(Node v1, Node v2)
{
	if (v1.getID() == v2.getID())
	{
		return 1;
	}
	else
	{
		return 0;
	}
}