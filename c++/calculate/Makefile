
CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I ./
LIB = -L ./   

calcu : calculatesqrt.o                  
	${CC} calculatesqrt.o ${CFLAGS} ${INC} ${LIB} -lm -o calcu

calculatesqrt.o : calculatesqrt.cpp                   
	${CC} calculatesqrt.cpp ${CFLAGS} ${INC} ${LIB}  -c  

clean :                             
	@ rm -rf *.o
	@ rm calcu

