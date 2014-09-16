TARG=drawing
SRC=drawing.cpp
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/opencv/
CFLAGS=

$(TARG):$(SRC)
	g++ -g -o $@ ${CFLAGS} $(LIB) $(INC) -lopencv_core -lopencv_highgui $^

.PHONY:clean

clean:
	-rm $(TARG) tags -f 

