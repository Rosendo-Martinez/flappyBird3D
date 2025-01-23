all : ./bin/main.exe

run : ./bin/main.exe
	./bin/main.exe

./bin/main.exe : ./src/main.cpp ./bin/Shader.o
	g++ ./src/main.cpp ./dep/glad/src/glad.c ./bin/Shader.o -o ./bin/main.exe -I./dep/glad/include -lglfw -ldl

./bin/Shader.o : ./src/Shader.cpp ./src/Shader.h
	g++ -c ./src/Shader.cpp -o ./bin/Shader.o -I./dep/glad/include