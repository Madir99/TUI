//#include <iostream>
#include <stdio.h>

//using namespace std;

//----------------LINES----------------

//draw vertical line template
//always print in down direction
//Legacy, will be rewritten later
template<char P>
void LineV(int X, int Y, int lenght) {
  printf("\x1B[%d;%dH", Y, X);
  for (int i = 0; i < lenght; i++) {
    printf("%c\x1B[%dA", P, Y + i + 1);
  }
}
//draw horizontal line template
//always print in right direction
//Legacy, will be rewritten later
template<char P>
void LineH(int X, int Y, int lenght) {
  printf("\x1B[%d;%dH", Y, X);
  for (int i = 0; i < lenght; i++) {
    printf("%c", P);
  }
}

//draw horizontal single line line
void LineHS(int X, int Y, int lenght) {
  LineH<'─'>(X, Y, lenght);
}

//draw horizontal double line line
void LineHD(int X, int Y, int lenght) {
  LineH<'═'>(X, Y, lenght);
}

//draw vertical single line line
void LineVS(int X, int Y, int lenght) {
  LineV<'│'>(X, Y, lenght);
}

//draw vertical double line line
void LineVS(int X, int Y, int lenght) {
  LineV<'║'>(X, Y, lenght);
}

//-------------------BOXES-------------------

//draw box
//second vector must be bigger than fist one
template<char LU, char RU, char LD, char RD, char VL, char HL>
void Box(int X1, int Y1, int X2, int Y2) {
  printf("\x1B[%d;%dH%c", Y1, X1, LU);
  for (int i = 0; i < (X2-X1-2); i++) {
    printf("%c", HL);
  }
  printf("%c\x1B[%d;%dH%c", RU, Y2, X1, LD);
  for (int i = 0; i < (X2-X1-2); i++) {
    printf("%c", HL);
  }
  printf("%c", RD);
  LineV<VL>(X1, Y1+1, Y2-Y1-2);
  LineV<VL>(X2, Y1+1, Y2-Y1-2);
}

//draw single line box
vodi BoxS(int X1, int Y1, int X2, int Y2) {
  Box<'┌', '┐', '└', '┘', '─', '│'>(X1, Y1, X2, Y2)
}

//draw double line box
vodi BoxD(int X1, int Y1, int X2, int Y2) {
  Box<'╔', '╗', '╚', '╝', '═', '║'>(X1, Y1, X2, Y2)
}
