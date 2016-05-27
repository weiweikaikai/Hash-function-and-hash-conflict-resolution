CC=gcc
FLAGS=-g #-Wall
BIN=hash
SRC=Linear_detection_method.c main.c
INCLUDE=-I./
$(BIN):$(SRC)
	$(CC) -o $@ $^ $(FLAGS) $(INCLUDE)
.PHONY:clean
clean:
	rm -rf $(BIN)
