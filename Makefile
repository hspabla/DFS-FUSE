
CFLAGS = -Wall -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags`
LINKFLAGS = -Wall `pkg-config fuse --libs`

all: bin/dsfs

clean:
	rm -rf bin obj

bin: 
	mkdir -p bin

bin/dsfs: bin obj/dsfs.o obj/wrap.o obj/client.o obj/log.o
	g++ -o bin/dsfs obj/* -g $(LINKFLAGS)

obj:
	mkdir -p obj

obj/log.o: obj src/log.cc include/log.hh include/wrap.hh
	g++ -g -std=c++11 $(CFLAGS) -c src/log.cc -o obj/log.o

obj/dsfs.o: obj src/dsfs.cc include/dsfs.hh include/log.hh
	g++ -g -std=c++11 $(CFLAGS) -c src/dsfs.cc -o obj/dsfs.o

obj/client.o: obj src/client.c include/wrap.hh
	gcc -g $(CFLAGS) -c src/client.c -o obj/client.o

obj/wrap.o: obj src/wrap.cc include/wrap.hh include/dsfs.hh
	g++ -g -std=c++11 $(CFLAGS) -c src/wrap.cc -o obj/wrap.o

