So, welcome to my little great, terrible OpenGL code. The main players here are the Shapes and Node classes. 
Shapes includes all the OpenGL legwork regarding rendering the polygons you want. 
To use it, you should call a new shape, like so: shape *shape = new shape(0). Now that number is not optional.
The integer (either 0 or 1) is used to decide whether to render a filled in polygon or a polyline outline.
After the declaration, add as many vertices as you like using the addVertex method. addVertex will anticipate an incoming Vec3.
Remember to put your coordinates in the first two slots and 1 in the final one for a homogeneous coordinate.
Finally, setColor lets you input an RGB combo to get the color you want and the vertices have a getter.
Now Node is a little more interesting, here is where you will take your geometric primitive and put it into a scene graph.
Node has two constructors, the difference being that one expects a parent and one doesn't. The second should only be used for what you wish to be the root node.
The constructor itself deals with connecting nodes and using it in the case of adding a child will save time on calling addChild and setParent manually. Although that is still an option, of course.
Node will be where you perform your transformations, as the scale, translate, and rotate methods are all in this class. 
Scale and translate take two arguments, for x and y, giving you the ability of changing only one value, by leaving the other in the default (1 for scale, 0 for translate).
Rotate takes an angle in degrees and rotates by that much. Aside from that, the draw method here calls the draw method of Shapes, but you don't need to manually call draw.
Finally, the Window class. While the easiest to use class, it's crucial to get everything working. This is where the FLTK code is called and run from.
To use this, just create a new window class using the default constructo and then call setRoot on the node you wish to be the root of your scene graph. And ta-da, you're done!
