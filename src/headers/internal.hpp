#include "typedefs.hpp"

extern Terminal term;
extern Terminal virt;

void invertColors();

void enableRaw();
void disableRaw();

void Line_draw(Object &obj);
void Box_draw(Object &obj);
void ProgressBar_draw(Object &obj);