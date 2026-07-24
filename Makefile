release:
	cmake -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build
	./build/Game
debug:
	cmake -B build -DCMAKE_BUILD_TYPE=Debug
	cmake --build build
	./build/Game
