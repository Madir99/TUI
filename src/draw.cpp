//#include <iostream>
#include <stdio.h>

//using namespace std;

//--------------CONSTANTS--------------

constexpr const unsigned char SHL[4] = {0xE2, 0x94, 0x80, 0x00};//"─"
constexpr const unsigned char DHL[4] = {0xE2, 0x95, 0x90, 0x00};//"═"
constexpr const unsigned char SVL[4] = {0xE2, 0x94, 0x82, 0x00};//"│"
constexpr const unsigned char DVL[4] = {0xE2, 0x95, 0x91, 0x00};//"║"
constexpr const unsigned char SLU[4] = {0xE2, 0x94, 0x8C, 0x00};//"┌"
constexpr const unsigned char DLU[4] = {0xE2, 0x95, 0x94, 0x00};//"╔"
constexpr const unsigned char SRU[4] = {0xE2, 0x94, 0x90, 0x00};//"┐"
constexpr const unsigned char DRU[4] = {0xE2, 0x95, 0x97, 0x00};//"╗"
constexpr const unsigned char SLD[4] = {0xE2, 0x94, 0x94, 0x00};//"└"
constexpr const unsigned char DLD[4] = {0xE2, 0x95, 0x9a, 0x00};//"╚"
constexpr const unsigned char SRD[4] = {0xE2, 0x94, 0x98, 0x00};//"┘"
constexpr const unsigned char DRD[4] = {0xE2, 0x95, 0x9d, 0x00};//"╝"

//----------------LINES----------------

//draw vertical line template
//always print in down direction
//Legacy, will be rewritten later
template<const unsigned char* P>
void LineV(int X, int Y, int lenght) {
  printf("\x1B[%d;%dH", Y, X);
  for (int i = 0; i < lenght; i++) {
    printf("%s\x1B[%d;%dH", P, Y + i + 1, X);
  }
}
//draw horizontal line template
//always print in right direction
//Legacy, will be rewritten later
template<const unsigned char* P>
void LineH(int X, int Y, int lenght) {
  printf("\x1B[%d;%dH", Y, X);
  for (int i = 0; i < lenght; i++) {
    printf("%s", P);
  }
}

//draw horizontal single line line
void LineHS(int X, int Y, int lenght) {
  LineH<SHL>(X, Y, lenght);
}

//draw horizontal double line line
void LineHD(int X, int Y, int lenght) {
  LineH<DHL>(X, Y, lenght);
}

//draw vertical single line line
void LineVS(int X, int Y, int lenght) {
  LineV<SVL>(X, Y, lenght);
}

//draw vertical double line line
void LineVD(int X, int Y, int lenght) {
  LineV<DVL>(X, Y, lenght);
}

//-------------------BOXES-------------------

//draw box
//second vector must be bigger than fist one
template<const unsigned char* LU, const unsigned char* RU, const unsigned char* LD, const unsigned char* RD, const unsigned char* VL, const unsigned char* HL>
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

//draw single line box
void BoxS(int X1, int Y1, int X2, int Y2) {
  Box<SLU, SRU, SLD, SRD, SVL, SHL>(X1, Y1, X2, Y2);
}

//draw double line box
void BoxD(int X1, int Y1, int X2, int Y2) {
  Box<DLU, DRU, DLD, DRD, DVL, DHL>(X1, Y1, X2, Y2);
}