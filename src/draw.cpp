//#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include "headers/internal.hpp"

//using namespace std;

//--------------CONSTANTS--------------

constexpr CBYTE SHL[4] = {0xE2, 0x94, 0x80, 0x00};//"─"
constexpr CBYTE DHL[4] = {0xE2, 0x95, 0x90, 0x00};//"═"
constexpr CBYTE SVL[4] = {0xE2, 0x94, 0x82, 0x00};//"│"
constexpr CBYTE DVL[4] = {0xE2, 0x95, 0x91, 0x00};//"║"
constexpr CBYTE SLU[4] = {0xE2, 0x94, 0x8C, 0x00};//"┌"
constexpr CBYTE DLU[4] = {0xE2, 0x95, 0x94, 0x00};//"╔"
constexpr CBYTE SRU[4] = {0xE2, 0x94, 0x90, 0x00};//"┐"
constexpr CBYTE DRU[4] = {0xE2, 0x95, 0x97, 0x00};//"╗"
constexpr CBYTE SLD[4] = {0xE2, 0x94, 0x94, 0x00};//"└"
constexpr CBYTE DLD[4] = {0xE2, 0x95, 0x9a, 0x00};//"╚"
constexpr CBYTE SRD[4] = {0xE2, 0x94, 0x98, 0x00};//"┘"
constexpr CBYTE DRD[4] = {0xE2, 0x95, 0x9d, 0x00};//"╝"

//----------------LINES----------------

//draw vertical line template
//always print in down direction
//Legacy, will be rewritten later
template<pCBYTE VL>
void LineV(int X, int Y, size_t lenght) {
	printf("\x1B[%d;%dH", Y, X);
	for (size_t i = 0; i < lenght; i++) {
		printf("%s\x1B[%ld;%dH", VL, Y + i + 1, X);
	}
}
//draw horizontal line template
//always print in right direction
//Legacy, will be rewritten later
template<pCBYTE HL>
void LineH(int X, int Y, size_t lenght) {
	printf("\x1B[%d;%dH", Y, X);
	for (size_t i = 0; i < lenght; i++) {
		printf("%s", HL);
	}
}

void Line_draw(Object &obj) {
	switch(obj.data.line.type) {
		case SINGLE_VERTICAL:
			LineV<SVL>(obj.X, obj.Y, obj.data.line.lenght);
			break;
		case DOUBLE_VERTICAL:
			LineV<DVL>(obj.X, obj.Y, obj.data.line.lenght);
			break;
		case SINGLE_HORIZONTAL:
			LineH<SHL>(obj.X, obj.Y, obj.data.line.lenght);
			break;
		case DOUBLE_HORIZONTAL:
			LineH<DHL>(obj.X, obj.Y, obj.data.line.lenght);
			break;
	}
}

//----------------BOXES----------------

//draw box
//second vector must be bigger than fist one in both directions.
template<pCBYTE LU, pCBYTE RU, pCBYTE LD, pCBYTE RD, pCBYTE VL, pCBYTE HL>
void Box(int X1, int Y1, int X2, int Y2) {
	printf("\x1B[%d;%dH%s", Y1, X1, LU);
	for (int i = 0; i < (X2-X1-2); i++) {
		printf("%s", HL);
	}
	printf("%s\x1B[%d;%dH%s", RU, Y2, X1, LD);
	for (int i = 0; i < (X2-X1-2); i++) {
		printf("%s", HL);
	}
	printf("%s", RD);
	LineV<VL>(X1, Y1+1, Y2-Y1-1);
	LineV<VL>(X2-1, Y1+1, Y2-Y1-1);
}

void Box_draw(Object &obj) {
	switch (obj.data.box.type) {
		case SINGLE:
			Box<SLU, SRU, SLD, SRD, SVL, SHL>(obj.X, obj.Y, obj.data.box.X, obj.data.box.Y);
		break;
		case DOUBLE:
			Box<DLU, DRU, DLD, DRD, DVL, DHL>(obj.X, obj.Y, obj.data.box.X, obj.data.box.Y);
		break;
	}
}

//----------------BARS-----------------

//draw progress bar
void ProgressBar_draw(Object &obj) {
	printf("\x1B[%d;%dH", obj.Y, obj.X);

	int textstart = (obj.data.progressBar.lenght >> 1) - 2;
	int filled = obj.data.progressBar.lenght;
	int empty = 0;
	if (obj.data.progressBar.progress > 0) {
		filled = (obj.data.progressBar.lenght * obj.data.progressBar.progress) / 100;
		empty = obj.data.progressBar.lenght - filled;
	}

	char* bar = reinterpret_cast<char*>(malloc(obj.data.progressBar.lenght+1));
	memset(bar, ' ', obj.data.progressBar.lenght);
	sprintf(bar + textstart, "% 3d%%", obj.data.progressBar.progress);
	if (obj.data.progressBar.lenght != 4) bar[textstart + 4] = ' ';

	if (empty > 0) {
		bar[obj.data.progressBar.lenght] = bar[filled + 1];
		bar[filled + 1] = 0;
		invertColors();
	} else bar[obj.data.progressBar.lenght] = 0;
	printf("%s", bar);

	if (empty > 0) {
		invertColors();
		bar[filled + 1] = bar[obj.data.progressBar.lenght];
		bar[obj.data.progressBar.lenght] = 0;
		printf("%s", bar + filled + 1);
	}
	free(bar);
}