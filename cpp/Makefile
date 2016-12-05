CXXFLAG=g++ -g
test:main.o test.o basic_algo.o
	$(CXXFLAG) -o test main.o test.o basic_algo.o -lpthread

main.o:main.cpp
	$(CXXFLAG) -c main.cpp

test.o:test.cpp
	$(CXXFLAG) -c test.cpp -lm

basic_algo.o:basic_algo.cpp
	$(CXXFLAG) -c basic_algo.cpp

clean:
	rm -rf *.o test
