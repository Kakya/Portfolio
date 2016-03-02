#include <iostream>
#include "Window.h"
int main (int argc, char * const argv[]) {
   
	Window *g = new Window(10, 10, 620, 600, "GL Window"); // create a window

	shape *square = new shape(0);
	//This will be the body
	square->addVertex(vec3(-1, -1, 1));
	square->addVertex(vec3(-1, 1, 1));
	square->addVertex(vec3(1, 1, 1));
	square->addVertex(vec3(1, -1, 1));
	square->setColor(0, 1, 0);
	Node *body = new Node(square, 0);
	//The triangle will be the body.
	shape *triangle = new shape(0);
	triangle->addVertex(vec3(-2, -11, 1));
	triangle->addVertex(vec3(3, 1, 1));
	triangle->addVertex(vec3(-5, 14, 1));
	triangle->setColor(0, 0, 1);
	//Make body bigger
	body->scale(9, 7);
	Node *head = new Node(triangle, 1, body);
	//Transformations on the body
	head->translate(15, 0);
	head->rotate(-8);
	head->scale(0.7, 0.5);
	//These are the limbs, four lower limbs and four upper limbs
	shape *ll_0 = new shape(0);
	ll_0->addVertex(vec3(-1, -1, 1));
	ll_0->addVertex(vec3(-1, 1, 1));
	ll_0->addVertex(vec3(1, 1, 1));
	ll_0->addVertex(vec3(1, -1, 1));
	shape *ul_0 = new shape(0);
	ll_0->setColor(0, 1, 1);
	ul_0->addVertex(vec3(-1, -1, 1));
	ul_0->addVertex(vec3(-1, 1, 1));
	ul_0->addVertex(vec3(1, 1, 1));
	ul_0->addVertex(vec3(1, -1, 1));
	ul_0->setColor(1, 0, 0);
	//Create the nodes with the upper limb tied to the body and the lower limb to the upper limb
	Node *upper_0 = new Node(ul_0, 2, body);
	Node *lower_0 = new Node(ll_0, 3, upper_0);
	//These transformations are required to allow the limbs to be at the base of the dog
	upper_0->scale(1, 2);
	lower_0->translate(0, -4);
	upper_0->translate(-7, -9);
	//The remaining limbs are done the same way as the above limbs
	shape *ll_1 = new shape(0);
	
	ll_1->addVertex(vec3(-1, -1, 1));
	ll_1->addVertex(vec3(-1, 1, 1));
	ll_1->addVertex(vec3(1, 1, 1));
	ll_1->addVertex(vec3(1, -1, 1));
	ll_1->setColor(1, 0, 0);
	shape *ul_1 = new shape(0);
	
	ul_1->addVertex(vec3(-1, -1, 1));
	ul_1->addVertex(vec3(-1, 1, 1));
	ul_1->addVertex(vec3(1, 1, 1));
	ul_1->addVertex(vec3(1, -1, 1));
	ul_1->setColor(0, 1, 1);
	Node *upper_1 = new Node(ul_1, 4, body);
	Node *lower_1 = new Node(ll_1, 5, upper_1);
	upper_1->scale(1, 2);
	lower_1->translate(0, -4);
	upper_1->translate(-3, -9);
	shape *ll_2 = new shape(0);
	
	ll_2->addVertex(vec3(-1, -1, 1));
	ll_2->addVertex(vec3(-1, 1, 1));
	ll_2->addVertex(vec3(1, 1, 1));
	ll_2->addVertex(vec3(1, -1, 1));
	shape *ul_2 = new shape(0);
	ll_2->setColor(1, 0, 1);
	ul_2->addVertex(vec3(-1, -1, 1));
	ul_2->addVertex(vec3(-1, 1, 1));
	ul_2->addVertex(vec3(1, 1, 1));
	ul_2->addVertex(vec3(1, -1, 1));
	ul_2->setColor(1, 1, 0);
	Node *upper_2 = new Node(ul_2, 6, body);
	Node *lower_2 = new Node(ll_2, 7, upper_2);
	upper_2->scale(1, 2);
	lower_2->translate(0, -4);
	upper_2->translate(2, -9);
	
	shape *ll_3 = new shape(0);
	
	ll_3->addVertex(vec3(-1, -1, 1));
	ll_3->addVertex(vec3(-1, 1, 1));
	ll_3->addVertex(vec3(1, 1, 1));
	ll_3->addVertex(vec3(1, -1, 1));
	ll_3->setColor(1, 1, 0);
	shape *ul_3 = new shape(0);
	
	ul_3->addVertex(vec3(-1, -1, 1));
	ul_3->addVertex(vec3(-1, 1, 1));
	ul_3->addVertex(vec3(1, 1, 1));
	ul_3->addVertex(vec3(1, -1, 1));
	ul_3->setColor(1, 0, 1);
	Node *upper_3 = new Node(ul_3, 8, body);
	Node *lower_3 = new Node(ll_3, 9, upper_3);
	upper_3->scale(1, 2);
	lower_3->translate(0, -4);
	upper_3->translate(6, -9);
	//End the limbs and get the tail, the final piece of the puzzle.
	shape *line = new shape(1);
	line->addVertex(vec3(-1, -1, 1));
	line->addVertex(vec3(-1, 1, 1));
	line->addVertex(vec3(1, 1, 1));
	line->addVertex(vec3(1, -1, 1));
	Node *tail = new Node(line, 10, body);
	//Scale and move the tail to the back of the dog and then rotate the tail
	tail->scale(5, 1);
	tail->translate(-13, 2);
	tail->rotate(20);
	//Unused translations on the body itself, this should affect every other component now as they are all connected to the body.
	body->translate(0, 0);
	body->rotate(0);
	g->setRoot(body);
	//Draw everything. Woo!
	g->show();  // show the window
	return Fl::run(); // tell FLTK to go
	system("PAUSE");

}