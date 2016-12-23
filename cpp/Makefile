SRC = ./src
OBJ = ./obj
BIN = ./bin

CXXFLAG=g++ -g
${BIN}/test:${OBJ}/main.o ${OBJ}/test.o ${OBJ}/basic_algo.o
	$(CXXFLAG) -o ${BIN}/test ${OBJ}/main.o ${OBJ}/test.o ${OBJ}/basic_algo.o -lpthread -lm

${OBJ}/main.o:${SRC}/main.cpp
	$(CXXFLAG) -c ${SRC}/main.cpp -o ${OBJ}/main.o

${OBJ}/test.o:${SRC}/test.cpp
	$(CXXFLAG) -c ${SRC}/test.cpp -o ${OBJ}/test.o

${OBJ}/basic_algo.o:${SRC}/basic_algo.cpp
	$(CXXFLAG) -c ${SRC}/basic_algo.cpp -o ${OBJ}/basic_algo.o

clean:
	rm -rf ${OBJ}/*.o ${BIN}/test
