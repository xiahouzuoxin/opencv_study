SRC=MatObj.cpp
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/opencv/
CFLAGS=

MatObj:$(SRC)
	g++ -o $@ ${CFLAGS} $(LIB) $(INC) -lopencv_core -lopencv_highgui $^

.PHONY:clean

clean:
	-rm MatObj -f 

