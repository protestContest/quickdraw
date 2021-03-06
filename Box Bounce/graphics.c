#include "graphics.h"

short graphics__OldMBarHeight;
short graphics__FrameInterval = 1;
long graphics__FrameCount;
char graphics__Buffer[64][342];
BitMap graphics__BufferBits;
Rect graphics__RedrawRect;

void WindowInit() {
	Rect totalRect, mBarRect;
	RgnHandle mBarRgn;
	WindowPtr window;

	/* Save old menu bar height to restore later */
	graphics__OldMBarHeight = MBarHeight;

	/* Hide menu bar */
	MBarHeight = 0;

	/* Create fullscreen window */
	window = NewWindow(nil, &(screenBits.bounds), kEmptyTitle, kVisible,
			plainDBox, kMoveToFront, kNoGoAway, kNilRefCon);
	SetRect(&mBarRect, screenBits.bounds.left, screenBits.bounds.top,
			screenBits.bounds.right, screenBits.bounds.top + graphics__OldMBarHeight);

	/* Add the old menubar region to the window's region */
	mBarRgn = NewRgn();
	RectRgn (mBarRgn, &mBarRect);
	UnionRgn(window->visRgn, mBarRgn, window->visRgn);
	DisposeRgn(mBarRgn);

	/* Make window the drawing area */
	SetPort(window);

	/* Set up our double buffer */
	graphics__BufferBits.baseAddr = (Ptr)&graphics__Buffer;
	graphics__BufferBits.rowBytes = 64;
	graphics__BufferBits.bounds = screenBits.bounds;

	FillRect(&(window->portRect), black);
	SetPortBits(&graphics__BufferBits);

	/* Prepare the reset rect */
	SetRect(&graphics__RedrawRect, 0, 0, kWidth, kHeight);

	FillRect(&(window->portRect), black);
}

void RestoreMBar() {
	MBarHeight = graphics__OldMBarHeight;
}

void DoVBL(VBLRecPtr VRP) {
	graphics__FrameCount++;

	/* erase the part of the screen we set in the redraw rect */
	FillRect(&graphics__RedrawRect, black);

	/* call our draw function, which draws into the buffer */
	VRP->draw(TickCount());

	/* copy the buffer onto the screen */
	CopyBits(&graphics__BufferBits, &screenBits, &graphics__RedrawRect, &graphics__RedrawRect, srcCopy, nil);

	/* reset the vblCount so the VBLTask will be called again */
	VRP->theVBLTask.vblCount = graphics__FrameInterval;
}

void StartVBL() {
	long curA5;
	VBLRecPtr recPtr;

	/* get a reference to our VBL record, which contains a pointer to our draw function */
	recPtr =  GetVBLRec();

	/* save A5 */
	curA5 = SetA5(recPtr->VBLA5);

	/* this will do handle the drawing phase */
	DoVBL(recPtr);

	/* restore A5 */
	(void) SetA5(curA5);
}

/* This adds a VBL Record to the VBL queue. Every "tick" (1/60th of a sec) it
 * will call "StartVBL". Then it will keep calling "update" until a button is
 * pressed.
 */
void InstallVBL(DrawPtr draw, DrawPtr update) {
	VBLRec theVBLRec;
	OSErr theErr;

	graphics__FrameCount = 0;

	/* the A5 register is sacred and must be protected */
	theVBLRec.VBLA5 = SetCurrentA5();

	/* saving our draw function to call later */
	theVBLRec.draw = draw;

	/* this is the routine called by the VBL queue */
	theVBLRec.theVBLTask.vblAddr = (VBLProcPtr) StartVBL;

	/* number of ticks to wait before calling StartVBL - 1 means 60fps */
	theVBLRec.theVBLTask.vblCount = graphics__FrameInterval;

	/* required type */
	theVBLRec.theVBLTask.qType = vType;

	/* tick offset to call the function. meaningless when tickCount is 1 */
	theVBLRec.theVBLTask.vblPhase = 0;

	/* add it to the queue! */
	theErr = VInstall((QElemPtr)&theVBLRec.theVBLTask);
	if (!theErr) {
		/* here we just call update until a button is pressed */
		do {
			update(graphics__FrameCount);
		} while (!Button());

		/* remove the VBL record from the queue – we're done now */
		theErr = VRemove((QElemPtr)&theVBLRec.theVBLTask);
	}

	FlushEvents(mDownMask, 0);
}

void SetRedrawRect(Rect *rect) {
	SetRect(&graphics__RedrawRect, rect->left, rect->top, rect->right, rect->bottom);
}
















