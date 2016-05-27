CC=gcc
FLAGS=-g #-Wall
BIN=hash
SRC=two_detection_methods.c main.c
INCLUDE=-I./
$(BIN):$(SRC)
	$(CC) -o $@ $^ $(FLAGS) $(INCLUDE)
.PHONY:clean
clean:
	rm -rf $(BIN)
