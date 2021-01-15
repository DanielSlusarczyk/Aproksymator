hermit: main.o hsplines.o points.o makespl.o backsubst.o gauss.o mat_io.o
	$(CC) -o hermit main.o hsplines.o points.o makespl.o backsubst.o gauss.o mat_io.o

main.o: main.c points.h hsplines.h makespl.h
	$(CC) -c main.c

hsplines.o: hsplines.c hsplines.h 
	$(CC) -c hsplines.c 

points.o: points.c points.h
	$(CC) -c points.c

backsubst.o: backsubst.c backsubst.h
	$(CC) -c backsubst.c

gauss.o: gauss.c gauss.h
	$(CC) -c gauss.c

mat_io.o: mat_io.c mat_io.h
	$(CC) -c mat_io.c

makespl.o: makespl.c makespl.h hsplines.h points.h backsubst.h gauss.h mat_io.h
	$(CC) -c makespl.c


.PHONY: clean

clean:
	-rm *.o 
