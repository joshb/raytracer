CXX=c++
CXXFLAGS=-Wall -ansi -pedantic `sdl-config --cflags`
OBJS=main.o my_math.o objects.o raytracer.o

main:	$(OBJS)
	$(CXX) $(OBJS) `sdl-config --libs` -o main

clean:
	rm -f main
	rm -f $(OBJS)

main.o: main.cpp
my_math.o: my_math.cpp
objects.o: objects.cpp
raytracer.o: raytracer.cpp
