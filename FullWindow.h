#include "ThisWindow.h"
#include <FL/Fl.H>
#include <FL/Fl_Window.H>

class FullWindow :public Fl_Window  // subclass of Fl_Window where the widgets and graphics will be displayed.
{
private:
	ThisWindow* gWin;			// a pointer to the graphics window
	Fl_Button* exitB;			// a pointer to the exit button
	Fl_Button* colorB;
	Fl_Button* addB;
	Fl_Slider* scaleB;
	Fl_Dial* rotateB;
	Fl_Slider* translateXB;
	Fl_Slider* translateYB;
	Fl_Button* deleteB;
	static void exitCB(Fl_Widget *w, void *data);
	static void addCB(Fl_Widget *w, void *data);
	static void colorCB(Fl_Widget *w, void *data);
	static void scaleCB(Fl_Widget *w, void *data);
	static void rotateCB(Fl_Widget *w, void *data);
	static void translateXCB(Fl_Widget *w, void *data);
	static void translateYCB(Fl_Widget *w, void *data);
	static void deleteCB(Fl_Widget* w, void *data);
public:
	FullWindow(int x, int y, int w, int h, char* c);
	virtual ~FullWindow();
	ThisWindow* getWindow();

};