#include "main.h"

void main() {
	ToolBoxInit();
	WindowInit();
	setup();
	draw();

	MBarHeight = gOldMBarHeight;
}

void ToolBoxInit() {
	InitGraf(&thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();
}

void WindowInit() {
	Rect totalRect, mBarRect;
	RgnHandle mBarRgn;
	WindowPtr window;

	gOldMBarHeight = MBarHeight;
	MBarHeight = 0;

	window = NewWindow(nil, &(screenBits.bounds), kEmptyTitle, kVisible,
			plainDBox, kMoveToFront,  kNoGoAway, kNilRefCon);
	SetRect(&mBarRect, screenBits.bounds.left, screenBits.bounds.top,
			screenBits.bounds.right, screenBits.bounds.top + gOldMBarHeight);
	mBarRgn = NewRgn();
	RectRgn (mBarRgn, &mBarRect);
	UnionRgn(window->visRgn, mBarRgn, window->visRgn);
	DisposeRgn(mBarRgn);
	SetPort(window);
	FillRect(&(window->portRect), black);
	PenMode(patXor);
}



























