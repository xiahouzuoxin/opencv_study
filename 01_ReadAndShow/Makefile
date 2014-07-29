SRC=read.cpp
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/opencv/

read:$(SRC)
	g++ -o $@ $(LIB) $(INC) -lopencv_core -lopencv_highgui -lopencv_ml $^
