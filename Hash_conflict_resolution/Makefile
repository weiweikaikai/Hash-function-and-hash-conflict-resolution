CC=gcc
FLAGS=-g #-Wall
BIN=hash
SRC=Hash_conflict_resolution.c main.c
INCLUDE=-I./
$(BIN):$(SRC)
	$(CC) -o $@ $^ $(FLAGS) $(INCLUDE)
.PHONY:clean
clean:
	rm -rf $(BIN)
