#define kMoveToFront		(WindowPtr)-1L
#define kEmptyString		"\p"
#define kEmptyTitle 			kEmptyString
#define kVisible    			true
#define kNoGoAway   			false
#define kNilRefCon  			(long)nil

short gOldMBarHeight;

void ToolBoxInit(void);
void WindowInit(void);
void setup(void);
void draw(void);