all : ./bin/main.exe

run : ./bin/main.exe
	./bin/main.exe

clean : 
	rm -f ./bin/*.o ./bin/main.exe

./bin/main.exe : ./src/main.cpp ./bin/Shader.o ./bin/SquareRender.o
	g++ ./src/main.cpp ./dep/glad/src/glad.c ./bin/Shader.o ./bin/SquareRender.o -o ./bin/main.exe -I./dep/glad/include -lglfw -ldl

./bin/Shader.o : ./src/Shader.cpp ./src/Shader.h
	g++ -c ./src/Shader.cpp -o ./bin/Shader.o -I./dep/glad/include

./bin/SquareRender.o : ./src/SquareRender.cpp ./src/SquareRender.h 
	g++ -c ./src/SquareRender.cpp -o ./bin/SquareRender.o -I./dep/glad/include