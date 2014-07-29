TARG=lookup_table
SRC=lookup_table.cpp
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/opencv/
CFLAGS=

$(TARG):$(SRC)
	g++ -o $@ ${CFLAGS} $(LIB) $(INC) -lopencv_core -lopencv_highgui $^

.PHONY:clean

clean:
	-rm $(TARG) -f 

