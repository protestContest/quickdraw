#ifndef VIDEO_H
#define VIDEO_H

#include <Retrace.h>

#define kWidth	512
#define kHeight	342


typedef void (*DrawPtr)(long);

struct VBLRec {
	VBLTask theVBLTask;
	long VBLA5;
	DrawPtr draw;
};
typedef struct VBLRec VBLRec, *VBLRecPtr;
#define kMoveToFront		(WindowPtr)-1L
#define kEmptyString		"\p"
#define kEmptyTitle			kEmptyString
#define kVisible			true
#define kNoGoAway			false
#define kNilRefCon			(long)nil

VBLRecPtr GetVBLRec() = 0x2008;
void InstallVBL(DrawPtr draw, DrawPtr update);
void WindowInit();
void RestoreMBar();
void SetRedrawRect(Rect *rect);

#endif


















