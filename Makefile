
CFLAGS = -Wall -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags`
LINKFLAGS = -Wall `pkg-config fuse --libs`

all: bin/examplefs

clean:
	rm -rf bin obj

bin: 
	mkdir -p bin

bin/examplefs: bin obj/examplefs.o obj/wrap.o obj/main.o
	g++ -g $(LINKFLAGS) -o bin/examplefs obj/*

obj:
	mkdir -p obj

obj/examplefs.o: obj src/examplefs.cc include/examplefs.hh
	g++ -g $(CFLAGS) -c src/examplefs.cc -o obj/examplefs.o

obj/main.o: obj src/main.c include/wrap.hh
	gcc -g $(CFLAGS) -c src/main.c -o obj/main.o

obj/wrap.o: obj src/wrap.cc include/wrap.hh include/examplefs.hh
	g++ -g $(CFLAGS) -c src/wrap.cc -o obj/wrap.o

