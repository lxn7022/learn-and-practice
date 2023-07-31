
CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I./
LIB = -L./ -lm -lstdc++ 

App1 = line

Target = ${App1}

build: ${Target}

${App1} : ${App1}.o                  
	${CC} ${App1}.o ${CFLAGS} ${INC} ${LIB} -o ${App1}

%.o:%.cpp
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean :                             
	@ rm -rf *.o
	@ rm ${Target} 