
CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I./
LIB = -L./ -lm -lstdc++ 

App1 = containers
App2 = findmaxcnt
App3 = use-vector
App4 = use-unordered-map
App5 = use-map

Target = ${App1} ${App2} ${App3} ${App4} ${App5}

build: ${Target}

${App1} : ${App1}.o                  
	${CC} ${App1}.o ${CFLAGS} ${INC} ${LIB} -o ${App1}

${App2} : ${App2}.o                  
	${CC} ${App2}.o ${CFLAGS} ${INC} ${LIB} -o ${App2}

${App3} : ${App3}.o                  
	${CC} ${App3}.o ${CFLAGS} ${INC} ${LIB} -o ${App3}

${App4} : ${App4}.o                  
	${CC} ${App4}.o ${CFLAGS} ${INC} ${LIB} -o ${App4}

${App5} : ${App5}.o                  
	${CC} ${App5}.o ${CFLAGS} ${INC} ${LIB} -o ${App5}

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :                             
	@ rm -rf *.o
	@ rm ${Target} 

