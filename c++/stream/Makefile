CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I./
LIB = -L./ -lm -lstdc++ 

App1 = use-fstream
App2 = use-sstream
App3 = use-iostream

Target = ${App1} ${App2} ${App3} 

build: ${Target}

${App1} : ${App1}.o                  
	${CC} ${App1}.o ${CFLAGS} ${INC} ${LIB} -o ${App1}

${App2} : ${App2}.o                  
	${CC} ${App2}.o ${CFLAGS} ${INC} ${LIB} -o ${App2}

${App3} : ${App3}.o                  
	${CC} ${App3}.o ${CFLAGS} ${INC} ${LIB} -o ${App3}		 

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :                             
	@ rm -rf *.o
	@ rm ${Target} 
	@ rm *.output

