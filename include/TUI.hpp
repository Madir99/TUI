#ifndef INCLUDE_TUI_HPP__COLOR
	#define INCLUDE_TUI_HPP__COLOR
	typedef enum _Color : unsigned char {
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
	/*
	Transform 3 color channels with range 0-5 to corespond color ID for ANSCI escape code.
	If color channel have invalid value, it will be set to 0. 
	*/
	Color rgb(unsigned char red, unsigned char green, unsigned char blue);
	/*
	Transform intensity channel with range 0-23 to corespond color ID for ANSCI escape code.
	If color channel have invalid value, it will be set to 0.
	If 0 is equal to black or 23 is equal to white depend on terminal color palet. 
	*/
	Color grayscale(unsigned char intensity);
#endif //INCLUDE_TUI_HPP__COLOR

#ifndef INCLUDE_TUI_HPP__SETUP
	#define INCLUDE_TUI_HPP__SETUP
	/*
	Initialize TUI
	If rows or colons are 0, it set that value to be same as current terminal dimenson.
	Legacy, will be rewritten later
	return true if error occured
	*/
	bool TUI_Init(int rows = 25, int colons = 80, Color background = BLACK, Color foreground = DARK_WHITE);

	//Deinitialize TUI
	//return true if error occured
	bool TUI_Deinit(bool clear = true);

	//render scene
	void render(unsigned char scene);

	/*
	return last error
	0 - OK
	1 - Invalid parameter
	2 - no bject left for allocation
	3 - Invalid position of object
	4 - Already initialized or deinitialized
	*/
	int getLastError();
#endif //INCLUDE_TUI_HPP__SETUP

#ifndef INCLUDE_TUI_HPP__OBJECT
	#define INCLUDE_TUI_HPP__OBJECT

	typedef enum _BoxType : unsigned char {
		SINGLE	= 0,
		DOUBLE	= 1
	} BoxType, *pBoxType;

	typedef enum _LineType : unsigned char {
		SINGLE_VERTICAL		= 0,
		DOUBLE_VERTICAL		= 1,
		SINGLE_HORIZONTAL	= 2,
		DOUBLE_HORIZONTAL	= 3
	} LineType, *pLineType;

	//add line to scene
	//return object ID and -1 if error
	int line(int X, int Y, int lenght, LineType type, unsigned char scene);

	//add box to scene
	//return object ID and -1 if error
	int box(int X1, int Y1, int X2, int Y2, BoxType type, unsigned char scene);

	//add progress bar to scene
	//return object ID and -1 if error
	int progressBar(int X, int Y, int lenght, unsigned char scene);

	//update specific progress bar
	//return true if error occured
	bool progBarUpd(unsigned short ID, unsigned char progress, unsigned char scene);
#endif //INCLUDE_TUI_HPP__OBJECT