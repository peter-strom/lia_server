CC=g++
CFLAGS=-Wall
OBJS= \
main.cpp \
server/server.cpp \
callbacks/callbacks.cpp 
OUTPUT=-o main
LIBRARY=

all: make run

make:
	$(CC) $(OBJS) $(OUTPUT) $(CFLAGS) $(LIBRARY)  
run :
	sudo ./main 555
