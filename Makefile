INCFLAGS = -I./glm-0.9.2.7 -I/usr/X11/include -I./include/
LDFLAGS = -framework GLUT -framework OpenGL -L./osxlib/ \
		-L"/System/Library/Frameworks/OpenGL.framework/Libraries" \
		-lGL -lGLU -lm -lstdc++ -lfreeimage
HEADERS = Objects.h ReadScene.h variables.h Film.h Intersect.h Transform.h Camera.h Sphere.h structs.h Paint.h
OBJFILES = main.o ReadScene.o Objects.o Film.o Intersect.o Transform.o Camera.o Triangle.o Sphere.o Paint.o

all: raytracer
raytracer: $(OBJFILES) $(HEADERS)
	g++ -O2 -o raytracer $(OBJFILES) $(INCFLAGS) $(LDFLAGS)
main.o: main.cpp variables.h ReadScene.h Objects.h ReadScene.cpp
	g++ $(INCFLAGS) -c main.cpp  
ReadScene.o: ReadScene.cpp ReadScene.h variables.h
	g++ $(INCFLAGS) -c ReadScene.cpp 
Objects.o: Objects.cpp Objects.h variables.h
	g++ $(INCFLAGS) -c Objects.cpp
Film.o: Film.cpp Film.h variables.h
	g++ $(INCFLAGS) -c Film.cpp
Camera.o: Camera.cpp Camera.h variables.h
	g++ $(INCFLAGS) -c Camera.cpp
Triangle.o: Triangle.cpp Triangle.h variables.h
	g++ $(INCFLAGS) -c Triangle.cpp
Sphere.o: Sphere.cpp Sphere.h variables.h
	g++ $(INCFLAGS) -c Sphere.cpp
Intersect.o: Intersect.cpp Intersect.h variables.h
	g++ $(INCFLAGS) -c Intersect.cpp
Paint.o: Paint.cpp Paint.h variables.h Objects.cpp Objects.h
	g++ $(INCFLAGS) -c Paint.cpp
Transform.o: Transform.cpp  Transform.h variables.h
	g++ $(INCFLAGS) -c Transform.cpp
clean: 
	rm -f *.o raytracer *.png
touch:
	touch *.cpp