CC=gcc
FLAGS=-g #-Wall
BIN=hash
SRC=chain_address_method.c main.c
INCLUDE=-I./
$(BIN):$(SRC)
	$(CC) -o $@ $^ $(FLAGS) $(INCLUDE)
.PHONY:clean
clean:
	rm -rf $(BIN)
