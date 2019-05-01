#include "sketch.h"

Rect gLines[ kNumLines ];
short gDeltaTop = 3, gDeltaBottom = 3;
short gDeltaLeft = 2, gDeltaRight = 6;

void setup() {
	short i;
	HideCursor();
	GetDateTime((unsigned long*)(&randSeed));
	RandomRect(&(gLines[0]));
	DrawLine(0);

	for (i = 1; i < kNumLines; i++) {
		gLines[i] = gLines[i - 1];
		RecalcLine(i);
		DrawLine(i);
	}
}

void draw() {
	short i;

	while (!Button()) {
		DrawLine(kNumLines - 1);
		for (i = kNumLines - 1; i > 0; i--) {
			gLines[i] = gLines[i - 1];
		}
		RecalcLine(0);
		DrawLine(0);
	}
}

void RandomRect(Rect *rectPtr) {
	WindowPtr window;
	window = FrontWindow();
	rectPtr->left = Randomize(window->portRect.right - window->portRect.left);
	rectPtr->right = Randomize(window->portRect.right - window->portRect.left);
	rectPtr->top = Randomize(window->portRect.bottom - window->portRect.top);
	rectPtr->bottom = Randomize(window->portRect.bottom - window->portRect.top);
}

short Randomize(short range) {
	long randomNumber;
	randomNumber = Random();
	if (randomNumber < 0)
		randomNumber *= -1;

	return ((randomNumber * range) / kRandomUpperLimit);
}

void RecalcLine(short i) {

	WindowPtr window;
	window = FrontWindow();

	gLines[i].top += gDeltaTop;
	if ((gLines[i].top < window->portRect.top) ||
		(gLines[i].top > window->portRect.bottom)) {

		gDeltaTop *= -1;
		gLines[i].top += 2*gDeltaTop;
	}

	gLines[i].bottom += gDeltaBottom;
	if ((gLines[i].bottom < window->portRect.top) ||
		(gLines[i].bottom > window->portRect.bottom)) {

		gDeltaBottom *= -1;
		gLines[i].bottom += 2*gDeltaBottom;
	}

	gLines[i].left += gDeltaLeft;
	if ((gLines[i].left < window->portRect.left) ||
		(gLines[i].left > window->portRect.right)) {

		gDeltaLeft *= -1;
		gLines[i].left += 2*gDeltaLeft;
	}

	gLines[i].right += gDeltaRight;
	if ((gLines[i].right < window->portRect.left) ||
		(gLines[i].right > window->portRect.right)) {

		gDeltaRight *= -1;
		gLines[i].right += 2*gDeltaRight;
	}
}

void DrawLine(short i) {
	MoveTo(gLines[i].left, gLines[i].top);
	LineTo(gLines[i].right, gLines[i].bottom);
}















