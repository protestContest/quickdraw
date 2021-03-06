#include "graphics.h"

Rect box;
Rect oldBox;
Rect redrawRect;
short goingRight = 1;
short goingDown = 1;
short left, right, top, bottom;
short speed = 1;

void setup(long ticks) {
	SetRect(&box, 0, 150, 100, 250);
	PenSize(4, 4);
	PenMode(patXor);
}

void update(long ticks) {
	if (goingRight) {
		left =  box.left + speed;
		right = box.right + speed;
		if (right > kWidth)
			goingRight = 0;
	} else {
		left = box.left - speed;
		right = box.right - speed;
		if (left < 0)
			goingRight = 1;
	}

	if (goingDown) {
		top =  box.top + speed;
		bottom = box.bottom + speed;
		if (bottom > kHeight)
			goingDown = 0;
	} else {
		top = box.top - speed;
		bottom = box.bottom - speed;
		if (top < 0)
			goingDown = 1;
	}
}

void draw(long ticks) {
	SetRect(&oldBox, box.left, box.top, box.right, box.bottom);
	SetRect(&box, left, top, right, bottom);
	UnionRect(&oldBox, &box, &redrawRect);
	FrameRect(&box);
	SetRedrawRect(&redrawRect);
}





















