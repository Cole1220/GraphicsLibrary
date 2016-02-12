OBJ1=main.cpp ppmIO.o graphicsSpace.o
OBJ2=example.cpp ppmIO.o graphicsSpace.o
OBJ3=hw2main.cpp ppmIO.o graphicsSpace.o
CXX=g++

all: main test hw2main

main: $(OBJ1)
	$(CXX) -o runMain $(OBJ1)

test: $(OBJ2)
	$(CXX) -o runExample $(OBJ2) 

hw2main: $(OBJ3)
	$(CXX) -o runHw2 $(OBJ3)

clean: 
	rm -f *~ run* *.o 
