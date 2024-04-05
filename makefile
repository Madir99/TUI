make: bin
	g++ src/*.cpp -Wall -pedantic -shared -o bin/libTUI.so #Linux
bin:
	mkdir bin
