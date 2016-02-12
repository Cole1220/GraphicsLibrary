OBJ0=main.cpp ppmIO.o graphicsSpace.o
OBJ1=example.cpp ppmIO.o graphicsSpace.o
OBJ2=hw2main.cpp ppmIO.o graphicsSpace.o
OBJ3=hw3main.cpp ppmIO.o graphicsSpace.o
OBJ4=hw4main.cpp ppmIO.o graphicsSpace.o
OBJ5=hw5main.cpp ppmIO.o graphicsSpace.o
OBJ6=hw6main.cpp ppmIO.o graphicsSpace.o
OBJ7=hw7main.cpp ppmIO.o graphicsSpace.o
CXX=g++

all: hw7main

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
	
hw5main: $(OBJ5)
	$(CXX) -o runHW5 $(OBJ5)

hw6main: $(OBJ6)
	$(CXX) -o runHW6 $(OBJ6)
	
hw7main: $(OBJ7)
	$(CXX) -o runHW7 $(OBJ7)

clean: 
	rm -f *~ run* *.o 
