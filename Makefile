all: main.cpp shady.cpp shader.cpp ./glad/glad.c ./fmt/format.cc
	g++ main.cpp shady.cpp shader.cpp ./glad/glad.c ./fmt/format.cc -o ./bin/shady -Iglad -lglfw3 -lopengl32
