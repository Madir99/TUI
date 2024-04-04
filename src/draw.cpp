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

//draw horizontal single line
void LineHS(int X, int Y, int lenght) {
  LineH<'─'>(X, Y, lenght);
}

//draw horizontal double line
void LineHD(int X, int Y, int lenght) {
  LineH<'═'>(X, Y, lenght);
}

//draw vertical single line
void LineVS(int X, int Y, int lenght) {
  LineV<'│'>(X, Y, lenght);
}

//draw vertical double line
void LineVS(int X, int Y, int lenght) {
  LineV<'║'>(X, Y, lenght);
}

//-------------------BOXES-------------------

//Draw box
//second vector must be bigger than fist one
template<char LU, char RU, char LD, char RD, char VL, char HL>
void Box(int X1, int Y1, int X2, int Y2) {
  printf("\x1B[%d;%dH%c", Y1, X1, LU);
  
}
