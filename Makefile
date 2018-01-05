all:
	g++ *.cpp include/glad/glad.c include/fmt/format.cc -o bin/shady -Iinclude -lglfw3 -lopengl32
