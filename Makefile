DIR_INC = ./include
DIR_SRC = ./
DIR_OBJ = ./
DIR_BIN = ./

SRC = $(wildcard ${DIR_SRC}/*.c)
OBJ = $(patsubst %.c,${DIR_OBJ}/%.o,$(notdir ${SRC})) 

TARGET = main

BIN_TARGET = ${DIR_BIN}/${TARGET}
 
CC = cc
CFLAGS = -I${DIR_INC}
LIB = 

${BIN_TARGET}:${OBJ}
	$(CC) $(OBJ) -o $@ $(LIB)
${DIR_OBJ}/%.o:${DIR_SRC}/%.c
	$(CC) $(CFLAGS) -c  $< -o $@
.PHONY:clean
clean:
	rm -rf *.o
	rm -rf ${TARGET}
