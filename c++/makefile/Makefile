CC = gcc
DIR_BIN = ./bin
DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_INC = ./Include

Targit = Tutorial 
BIN_Targit =$(DIR_BIN)/$(Targit)
SRC = $(wildcard $(DIR_SRC)/*.c)
Objects = $(patsubst %.c,$(DIR_OBJ)/%.o,$(notdir ${SRC})) 
CFLAGS += -g -Wall -w
INCLUDE += -I./$(DIR_INC) -I./$(DIR_SRC)
LDLIBS += -L./usrLib -lm

build:$(Targit)

$(Targit):$(Objects)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(BIN_Targit) $(Objects) $(LDLIBS)

$(DIR_OBJ)/%.o:$(DIR_SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

.PHONY = clean
clean :
	-rm -rf $(Objects) $(BIN_Targit) 
