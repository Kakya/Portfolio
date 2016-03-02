#include "vec3.h"
#include "mat3.h"
#include <list>
#include <iostream>
#include "Shapes.h"
using namespace std;

//Constructor requires specification whether polygon or polyline
shape::shape(int isLine)
{
	if (isLine)
	{
		Line = 1;
	}
	else
	{
		Line = 0;
	}
}
	//Set the color of the shape
void shape::setColor(int red, int green, int blue)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}
//Add a vertex, used to determine what OpenGL will draw.
void shape::addVertex(vec3 vertex)
{
	Vertices.push_back(vertex);
}
//Draw method for OpenGL stuff
void shape::draw()
{
	if (!Line)
	{
		//Loop through and populate the OpenGL vertices using the Vertices list
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_POLYGON);
		list<vec3>::iterator i;
		for (i = Vertices.begin(); i != Vertices.end(); ++i)
		{
			glVertex2f((*i)[0], (*i)[1]);
		}
		glEnd();
	}
	else
	{
		glColor3f(color[0], color[1], color[2]);
		glBegin(GL_LINE_LOOP);
		list<vec3>::iterator i;
		for (i = Vertices.begin(); i != Vertices.end(); ++i)
		{
			glVertex2f((*i)[0], (*i)[1]);
		}
		glEnd();
	}
}
list<vec3>::iterator shape::getVertices()
{
	return Vertices.begin();
}
list<vec3>::iterator shape::lastVertex()
{
	return Vertices.end();
}