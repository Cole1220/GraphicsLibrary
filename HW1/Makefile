OBJ1=main.cpp ppmIO.o graphicsSpace.o
OBJ2=hw1Main.cpp ppmIO.o graphicsSpace.o
CXX=g++

all: main hw1

main: $(OBJ1)
	$(CXX) -o runMain $(OBJ1) 
hw1: $(OBJ2)
	$(CXX) -o runHW1 $(OBJ2) 

clean: 
	rm -f *~ run* *.o 
