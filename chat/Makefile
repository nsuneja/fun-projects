PWD = $(shell pwd)
CFLAGS =-std=c++11 -g3 -I./ 
LDFLAGS=-lzmq -lprotobuf -Wl,-rpath,/usr/local/lib
CC=g++
DEPS = client.h datatype.pb.h SimpleRedisClient.h zmq.hpp
OBJ = client.o datatype.pb.o SimpleRedisClient.o 
EXEC= groupchat

%.o: %.cc $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o $(EXEC)
