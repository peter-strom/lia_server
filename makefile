CC=g++
CFLAGS=-Wall
OBJS= \
main.cpp \
server/server.cpp \
server/callbacks.cpp \
server/client.cpp \
server/clients.cpp
OUTPUT=-o main
LIBRARY=

all: make run

make:
	$(CC) $(OBJS) $(OUTPUT) $(CFLAGS) $(LIBRARY)  
run :
	sudo ./main 555
