So, welcome to my little great, terrible OpenGL code. 
Now it has a GUI! Fantastic. The way the GUI Works is that the Tree Linker window has the tree. When first started, it will have "ROOT", "Redraw", and "Build Tree". 
Build Tree must be pressed to fill out the remainder of the tree. This is the only way I found to be able to use recursion to fill out the tree.
Now that you've pressed Build Tree, you should have the components of the animal scene graph. To modify the elements of the scene graph, select them in the tree list first.
After they are selected, you can use any of the buttons in the Scene Graph window to modify the node. Unlike using the code, the buttons and sliders here do not propagate changes to children.
X Translate and Y Translate are the sliders for moving a polygon across either the x or y axes. Scale makes your polygon bigger or smaller. 
Delete removes your polygon and all its children from both the scene graph and the tree list. Rotation angle rotates your polygon. Exit leaves the program and shuts everything down.
Add Node adds in a new node, which you have to give a name and an ID using stdin. If you are currently selecting a node, the new polygon will be added as a child.
If not, the new polygon will be an independent polygon. Redraw in the Tree Linker deletes the old graph and redraws the original scene graph. A bug that I hadn't the time to fix
is that the old Tree List does not go away, it has to be closed manually. Aside from that, everything works as expected.
