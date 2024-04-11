typedef unsigned char	BYTE;
typedef unsigned short	WORD;
typedef const BYTE		CBYTE, *pCBYTE;

typedef void (*pFunction)();

typedef enum _ErrorLevel {
	OK					= 0,
	INVALID_PARAMETER	= 1,
	NO_FREE_OBJECT		= 2,
	INVALID_POSITION	= 3,
	TYPE_MISSMATCH		= 4,
	ALREADY_IN_STATE	= 5
} ErrorLevel;

typedef enum _Color : BYTE {
	BLACK			=  0,
	DARK_RED		=  1,
	DARK_GREEN		=  2,
	DARK_YELLOW		=  3,
	DARK_BLUE		=  4,
	DARK_MAGENTA	=  5,
	DARK_CYAN		=  6,
	DARK_WHITE		=  7,
	BRIGHT_BLACK	=  8,
	BRIGHT_RED		=  9,
	BRIGHT_GREEN	= 10,
	BRIGHT_YELLOW	= 11,
	BRIGHT_BLUE		= 12,
	BRIGHT_MAGENTA	= 13,
	BRIGHT_CYAN		= 14,
	WHITE			= 15
} Color;

typedef enum _BoxType : BYTE {
	SINGLE	= 0,
	DOUBLE	= 1
} BoxType, *pBoxType;

typedef enum _LineType : BYTE {
	SINGLE_VERTICAL		= 0,
	DOUBLE_VERTICAL		= 1,
	SINGLE_HORIZONTAL	= 2,
	DOUBLE_HORIZONTAL	= 3
} LineType, *pLineType;

typedef enum _DataType : BYTE {
	EMPTY			= 0,
	LINE			= 1,
	BOX				= 2,
	PROGRESS_BAR	= 3,
//	BUTTON			= 4
} DataType, *pDataType;

#pragma pack(push, 1)
typedef struct _Terminal {
	int rows;
	int colons;
	bool overflow;
	Color background;
	Color foreground;
} Terminal, *pTerminal;

typedef struct _Object {
	int X;
	int Y;
	DataType type;
	union _data {
		struct _line {
			int lenght;
			LineType type;
		} line;
		struct _box {
			int X;
			int Y;
			BoxType type;
		} box;
		struct _progressBar {
			int lenght;
			BYTE progress;
		} progressBar;
/*		struct _button {
			pFunction action;
			char label[8];
		} button;*/
	} data;
} Object, *pObject;

typedef struct _Scene {
	WORD objc = 0;
	Object objv[65535];
} Scene, *pScene;

#pragma pack(pop)