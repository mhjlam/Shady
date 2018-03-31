all:
	g++ src/*.cpp include/glad/glad.c include/fmt/format.cc -o bin/shady -Iinclude -lglfw3 -lopengl32 -std=c++11 -lstdc++fs
