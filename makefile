make: bin
	g++ src/linux/*.cpp src/*.cpp -Wall -pedantic -shared -fPIC -o bin/libTUI.so #Linux
bin:
	mkdir bin
