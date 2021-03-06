#include "main.h"
#include "graphics.h"

void main() {
	/* Set up program */
	ToolBoxInit();
	WindowInit();
	HideCursor();

	/* Set up sketch */
	setup(TickCount());

	/* Add draw function to VBL queue */
	InstallVBL((DrawPtr) &draw, (DrawPtr) &update);

	/* Clean up */
	RestoreMBar();
}

/* Standard Macintosh Toolbox initialization */
void ToolBoxInit() {
	InitGraf(&thePort);
	InitFonts();
	InitWindows();
	InitMenus();
	TEInit();
	InitDialogs(nil);
	InitCursor();
}
























