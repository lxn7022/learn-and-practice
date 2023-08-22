
CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I./
LIB = -L./ -lm -lstdc++ 

App1 = cplus11
App2 = lambda
App3 = smartpointer
App4 = default-delete

Target = ${App1} ${App2} ${App3} ${App4}

build: ${Target}

${App1} : ${App1}.o                  
	${CC} ${App1}.o ${CFLAGS} ${INC} ${LIB} -o ${App1}

${App2} : ${App2}.o                  
	${CC} ${App2}.o ${CFLAGS} ${INC} ${LIB} -o ${App2}

${App3} : ${App3}.o                  
	${CC} ${App3}.o ${CFLAGS} ${INC} ${LIB} -o ${App3}		

${App4} : ${App4}.o                  
	${CC} ${App4}.o ${CFLAGS} ${INC} ${LIB} -o ${App4}	

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :                             
	@ rm -rf *.o
	@ rm ${Target} 

