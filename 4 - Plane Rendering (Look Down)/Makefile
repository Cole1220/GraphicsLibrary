OBJ0=main.cpp ppmIO.o graphicsSpace.o
OBJ1=example.cpp ppmIO.o graphicsSpace.o
OBJ2=hw2main.cpp ppmIO.o graphicsSpace.o
OBJ3=hw3main.cpp ppmIO.o graphicsSpace.o
OBJ4=hw4main.cpp ppmIO.o graphicsSpace.o
CXX=g++

all: main test hw4main

main: $(OBJ0)
	$(CXX) -o runMain $(OBJ0)

test: $(OBJ1)
	$(CXX) -o runExample $(OBJ1) 

hw2main: $(OBJ2)
	$(CXX) -o runHW2 $(OBJ2)
	
hw3main: $(OBJ3)
	$(CXX) -o runHW3 $(OBJ3)
	
hw4main: $(OBJ4)
	$(CXX) -o runHW4 $(OBJ4)

clean: 
	rm -f *~ run* *.o 
