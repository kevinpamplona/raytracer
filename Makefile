INCFLAGS = -I./glm-0.9.2.7 -I/usr/X11/include -I./include/

all: raytracer
raytracer: main.o readfile.o Objects.o Objects.h readfile.h sphere.h tri.h trinormal.h variables.h vertexnormal.h Film.h Film.o
	g++ $(INCFLAGS) -o raytracer main.o readfile.o Objects.o Film.o
main.o: main.cpp variables.h readfile.h Objects.h readfile.cpp
	g++ $(INCFLAGS) -c main.cpp  
readfile.o: readfile.cpp readfile.h
	g++ $(INCFLAGS) -c readfile.cpp 
Objects.o: Objects.cpp Objects.h
	g++ $(INCFLAGS) -c Objects.cpp
Film.o: Film.cpp Film.h
	g++ $(INCFLAGS) -c Film.cpp
clean: 
	rm -f *.o raytracer
