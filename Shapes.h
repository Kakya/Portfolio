#include "vec3.h"
#include "mat3.h"
#include <list>
#include <iostream>
#include <FL/Fl.H>
#include <FL/Gl.H>
#include <Fl/Fl_Gl_Window.H>
using namespace std;
class shape
{
	
private:
	//The list will store how many vertices we have
	list<vec3> Vertices;
	//Get the color we want
	int color[3];
	//Check if a line or polygon
	int Line;

public:
	//Constructor requires specification whether polygon or polyline
	shape(int isLine);
	//Set the color of the shape
	void setColor(int red, int green, int blue);
	//Add a vertex, used to determine what OpenGL will draw.
	void addVertex(vec3 vertex);
	list<vec3>::iterator getVertices();
	list<vec3>::iterator lastVertex();
	//Draw method for OpenGL stuff
	void draw();
};