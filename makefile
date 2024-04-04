make: bin
	g++ src/*.cpp -Wall -pedantic -shared -o bin/TUI.so #Linux
bin:
	mkdir bin
