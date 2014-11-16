TARG=sobel
SRC=sobel.cpp
LIB=-L/usr/local/lib/
INC=-I/usr/local/include/opencv/ -I/usr/local/include/opencv2
CFLAGS=

$(TARG):$(SRC)
	g++ -g -o $@ ${CFLAGS} $(LIB) $(INC) \
		-lopencv_core -lopencv_highgui -lopencv_imgproc \
		$^

.PHONY:clean

clean:
	-rm $(TARG) tags -f 

