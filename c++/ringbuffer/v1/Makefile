
CC = clang

CFLAGS =  -std=c++11 -stdlib=libstdc++ -Wc++11-extensions -fcolor-diagnostics -fansi-escape-codes
INC = -I./
LIB = -L./ -lm -lstdc++ 

App1 = use-ring-buffer

Target = ${App1}

build: ${Target}

${App1} : ${App1}.o ring_buffer_s.o              
	${CC} ${App1}.o ring_buffer_s.o ${CFLAGS} ${INC} ${LIB} -o ${App1}

%.o:%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean :                             
	@ rm -rf *.o
	@ rm ${Target} 

