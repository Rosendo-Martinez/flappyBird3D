all : ./bin/main.exe

run : ./bin/main.exe
	./bin/main.exe

./bin/main.exe : ./src/main.cpp
	g++ ./src/main.cpp ./dep/glad/src/glad.c -o ./bin/main.exe -I./dep/glad/include -lglfw -ldl