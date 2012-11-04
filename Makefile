all: raytracer
raytracer: main.o readfile.o Objects.o Objects.h readfile.h sphere.h tri.h trinormal.h variables.h vertexnormal.h
	g++ -o raytracer main.o readfile.o Objects.o
main.o: main.cpp variables.h readfile.h Objects.h readfile.cpp
	g++ -c main.cpp  
readfile.o: readfile.cpp readfile.h
	g++ -c readfile.cpp 
Objects.o: Objects.cpp Objects.h
	g++ -c Objects.cpp
clean: rm -f *.o raytracer
