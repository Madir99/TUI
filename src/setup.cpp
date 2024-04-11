#include <stdio.h>
#include "headers/internal.hpp"

Terminal term;
Terminal virt;
Scene Scenes[256];
bool initialized = false;
WORD lastScene = 65535;
ErrorLevel err = OK;

//initialize TUI
//If rows or colons are 0, it set that value to be same as current terminal dimenson.
//Legacy, will be rewritten later
//return:
//0 - OK
//1 - too small terminal
//2 - already initialized
bool TUI_Init(int rows = 25, int colons = 80, Color background = BLACK, Color foreground = DARK_WHITE) {
	if (initialized) {
		err = ALREADY_IN_STATE;
		return true;
	}
	//Vitrual setup
	virt.rows = rows;
	virt.colons = colons;
	virt.background = background;
	virt.foreground = foreground;

	//Resolution
	enableRaw();
	printf("\x1B[18t"); //current resolution request
	scanf("\x1B[8;%d;%dt", &term.rows, &term.colons);
	disableRaw();
	if (!virt.rows) virt.rows = term.rows;
	if (!virt.colons) virt.colons = term.colons;
	if (term.rows < virt.rows || term.colons < virt.colons) {
		err = INVALID_PARAMETER;
		return true;
	}
	virt.overflow = !(term.colons > virt.colons);// && ((__SIZE_MAX__/term.colons) >= term.rows);

	//Color
	printf("\x1B[2J\x1B[38;5;%dm\x1B[48;5;%dm", virt.foreground, virt.background); //clear screen & set colors
	if (virt.overflow) {
		for (int pos = 0; pos < (virt.rows * virt.colons); pos++) printf(" ");
	} else {
		for (int row = 1; row <= virt.rows; row++) {
			printf("\x1B[%d;%dH", row , 1); //set cursor position
			for (int colon = 0; colon <= virt.colons; colon++) printf(" ");
		}
		printf("\x1B[H");
	}

	initialized = true;
	err = OK;
	return false;
}

//0 - OK
//1 - Not initialized
bool TUI_Deinit(bool clear = true) {
	if (!initialized) {
		err = ALREADY_IN_STATE;
		return true;
	}
	initialized = false;
	//Color
	printf("\x1B[38;5;%dm\x1B[48;5;%dm", term.foreground, term.background); //set colors that was before init
	if (clear) printf("\x1B[2J");
	err = OK;
	return false;
}

int getLastError() {
	return static_cast<int>(err);
}

void removeLastObject(BYTE scene) {
	Scenes[scene].objc--;
	Scenes[scene].objv[Scenes[scene].objc].type = EMPTY;
	err = OK;
}

void render(BYTE scene) {
	bool sta = (scene != lastScene);
	if (sta) printf("\x1B[2J");
	for (WORD obj = 0; obj < Scenes[scene].objc; obj++) {
		switch (Scenes[scene].objv[obj].type) {
			case LINE:
				if (sta) Line_draw(Scenes[scene].objv[obj]);
				break;
			case BOX:
				if (sta) Box_draw(Scenes[scene].objv[obj]);
				break;
			case PROGRESS_BAR:
				ProgressBar_draw(Scenes[scene].objv[obj]);
//			case BUTTON:
			case EMPTY:
				break;
		}
	}
	err = OK;
}

int box(int X1, int Y1, int X2, int Y2, BoxType type, BYTE scene) {
	if (scene > 256) {
		err = INVALID_PARAMETER;
		return -1;
	}
	if (Scenes[scene].objc >= 65535) {
		err = NO_FREE_OBJECT;
		return -1;
	}
	if (X1 >= virt.colons || Y1 >= virt.rows) {
		err = INVALID_POSITION;
		return -1;
	}
	if (X2 > virt.colons) X2 = virt.colons;
	if (Y2 > virt.rows) Y2 = virt.rows;
	Scenes[scene].objv[Scenes[scene].objc].X = X1;
	Scenes[scene].objv[Scenes[scene].objc].Y = Y1;
	Scenes[scene].objv[Scenes[scene].objc].type = BOX;
	Scenes[scene].objv[Scenes[scene].objc].data.box.X = X2;
	Scenes[scene].objv[Scenes[scene].objc].data.box.Y = Y2;
	Scenes[scene].objv[Scenes[scene].objc].data.box.type = type;
	Scenes[scene].objc++;
	err = OK;
	return Scenes[scene].objc-1;
}

int line(int X, int Y, int lenght, LineType type, BYTE scene) {
	if (scene > 256) {
		err = INVALID_PARAMETER;
		return -1;
	}
	if (Scenes[scene].objc >= 65535) {
		err = NO_FREE_OBJECT;
		return -1;
	}
	if (X >= virt.colons || Y >= virt.rows) {
		err = INVALID_POSITION;
		return -1;
	}
	if ((X+lenght) > virt.colons) lenght = virt.colons - X;
	Scenes[scene].objv[Scenes[scene].objc].X = X;
	Scenes[scene].objv[Scenes[scene].objc].Y = Y;
	Scenes[scene].objv[Scenes[scene].objc].type = LINE;
	Scenes[scene].objv[Scenes[scene].objc].data.line.lenght = lenght;
	Scenes[scene].objv[Scenes[scene].objc].data.line.type = type;
	Scenes[scene].objc++;
	err = OK;
	return Scenes[scene].objc-1;
}

int progressBar(int X, int Y, int lenght, BYTE scene) {
	if (scene > 256) {
		err = INVALID_PARAMETER;
		return -1;
	}
	if (Scenes[scene].objc >= 65535) {
		err = NO_FREE_OBJECT;
		return -1;
	}
	if (X >= virt.colons || Y >= virt.rows) {
		err = INVALID_POSITION;
		return -1;
	}
	if ((X+lenght) > virt.colons) lenght = virt.colons - X;
	if (lenght < 6) {
		err = INVALID_PARAMETER;
		return -1;
	}
	Scenes[scene].objv[Scenes[scene].objc].X = X;
	Scenes[scene].objv[Scenes[scene].objc].Y = Y;
	Scenes[scene].objv[Scenes[scene].objc].type = PROGRESS_BAR;
	Scenes[scene].objv[Scenes[scene].objc].data.progressBar.lenght = lenght;
	Scenes[scene].objv[Scenes[scene].objc].data.progressBar.progress = 0;
	Scenes[scene].objc++;
	err = OK;
	return Scenes[scene].objc-1;
}

bool progBarUpd(WORD ID, BYTE progress, BYTE scene) {
	if (scene > 256 || progress > 100) {
		err = INVALID_PARAMETER;
		return true;
	}
	if (Scenes[scene].objc <= ID) {
		err = INVALID_PARAMETER;
		return true;
	}
	if (Scenes[scene].objv[ID].type != PROGRESS_BAR) {
		err = TYPE_MISSMATCH;
		return true;
	}
	Scenes[scene].objv[ID].data.progressBar.progress = progress;
	err = OK;
	return false;
}