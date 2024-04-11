#include <termios.h>
#include <unistd.h>

termios originalTerminos;

void enableRaw() {
	tcgetattr(STDIN_FILENO, &originalTerminos);
	termios raw = originalTerminos;
	raw.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRaw() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &originalTerminos);
}