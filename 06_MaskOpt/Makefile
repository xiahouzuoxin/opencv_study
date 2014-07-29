TARG=mask_opt
SRC=Sharpen.cpp mask_opt.cpp
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/opencv/
CFLAGS=

$(TARG):$(SRC)
	g++ -o $@ ${CFLAGS} $(LIB) $(INC) -lopencv_core -lopencv_highgui $^

.PHONY:clean

clean:
	-rm $(TARG) tags -f 

