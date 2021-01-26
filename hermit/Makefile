hermit: main.o hsplines.o points.o makespl.o backsubst.o gauss.o mat_io.o
	$(CC) -o hermit main.o hsplines.o points.o makespl.o backsubst.o gauss.o mat_io.o -DTEST=0
	rm *.o
test: main.o hsplines.o points.o makespl1.o backsubst.o gauss.o mat_io.o
	$(CC) -o testhermit main.o hsplines.o points.o makespl.o backsubst.o gauss.o mat_io.o -DTEST=1

main.o: main.c points.h hsplines.h makespl.h
	$(CC) -c main.c

hsplines.o: hsplines.c hsplines.h 
	$(CC) -c hsplines.c 

points.o: points.c points.h
	$(CC) -c points.c

backsubst.o: gauss/backsubst.c gauss/backsubst.h
	$(CC) -c gauss/backsubst.c

gauss.o: gauss/gauss.c gauss/gauss.h
	$(CC) -c gauss/gauss.c

mat_io.o: gauss/mat_io.c gauss/mat_io.h
	$(CC) -c gauss/mat_io.c

makespl.o: makespl.c makespl.h hsplines.h points.h gauss/backsubst.h gauss/gauss.h gauss/mat_io.h
	$(CC) -c makespl.c -DTEST=0


makespl1.o: makespl.c makespl.h hsplines.h points.h gauss/backsubst.h gauss/gauss.h gauss/mat_io.h
	$(CC) -c makespl.c -DTEST=1

.PHONY: clean

clean:
	-rm *.o 
