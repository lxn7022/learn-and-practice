CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I./
LIB = -L./ -lm -lstdc++ 

App1 = vector-and-iterator
App2 = ksum

Target = ${App1} ${App2}

build: ${Target}

${App1} : ${App1}.o                  
	${CC} ${App1}.o ${CFLAGS} ${INC} ${LIB} -o ${App1}

${App2} : ${App2}.o                  
	${CC} ${App2}.o ${CFLAGS} ${INC} ${LIB} -o ${App2}

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :                             
	@ rm -rf *.o
	@ rm ${Target} 

