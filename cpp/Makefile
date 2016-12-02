CXXFLAG=g++ -g
pprq:main.o test.o basic_algo.o
	$(CXXFLAG) -o pprq main.o test.o basic_algo.o -lpthread

main.o:main.c
	$(CXXFLAG) -c main.c

test.o:test.cpp test.h
	$(CXXFLAG) -c test.cpp -lm

basic_algo.o:basic_algo.cpp basic_algo.h
	$(CXXFLAG) -c basic_algo.cpp

clean:
	rm -rf *.o pprq
