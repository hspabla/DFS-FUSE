
CFLAGS = -Wall -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags`
LINKFLAGS = -Wall `pkg-config fuse --libs`

all: bin/dsfs

clean:
	rm -rf bin obj

bin: 
	mkdir -p bin

bin/dsfs: bin obj/dsfs.o obj/wrap.o obj/main.o
	g++ -g $(LINKFLAGS) -o bin/dsfs obj/*

obj:
	mkdir -p obj

obj/dsfs.o: obj src/dsfs.cc include/dsfs.hh
	g++ -g $(CFLAGS) -c src/dsfs.cc -o obj/dsfs.o

obj/main.o: obj src/main.c include/wrap.hh
	gcc -g $(CFLAGS) -c src/main.c -o obj/main.o

obj/wrap.o: obj src/wrap.cc include/wrap.hh include/dsfs.hh
	g++ -g $(CFLAGS) -c src/wrap.cc -o obj/wrap.o

