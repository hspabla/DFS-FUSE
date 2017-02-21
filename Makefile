CXX = g++
CPPFLAGS += -I/usr/local/include -pthread
CXXFLAGS += -std=c++11
LDFLAGS += -L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
           -lprotobuf -lpthread -ldl
CFLAGS = -Wall -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags`
LINKFLAGS = -Wall `pkg-config fuse --libs`
//LINKFLAGS += -L/usr/local/lib `pkg-config --libs grpc++ grpc`       \
//           -Wl,--no-as-needed -lgrpc++_reflection -Wl,--as-needed \
//           -lprotobuf -lpthread -ldl -Wall `pkg-config fuse`

all: client server 

client: bin/client

server: bin/server

clean:
	rm -rf bin obj dsfs.log

bin:
	mkdir -p bin

bin/client: bin obj/fileserver.grpc.pb.o obj/fileserver.pb.o obj/dsfs.o obj/wrap.o obj/client.o obj/log.o obj/client_helper.o
	$(CXX) -o bin/client obj/fileserver.grpc.pb.o obj/fileserver.pb.o obj/dsfs.o obj/wrap.o obj/client.o obj/log.o obj/client_helper.o -g $(LINKFLAGS) $(LDFLAGS)

obj:
	mkdir -p obj

obj/log.o: obj src/log.cc include/log.hh include/wrap.hh
	$(CXX) -g -std=c++11 $(CFLAGS) -c src/log.cc -o obj/log.o

obj/dsfs.o: obj src/dsfs.cc include/dsfs.hh include/log.hh include/clientHelper.h
	$(CXX) -g -std=c++11 $(CFLAGS) $(LDFLAGS) -c src/dsfs.cc -o obj/dsfs.o

obj/client.o: obj src/client.c include/wrap.hh
	gcc -g $(CFLAGS) -c src/client.c -o obj/client.o

obj/wrap.o: obj src/wrap.cc include/wrap.hh include/dsfs.hh
	$(CXX) -g -std=c++11 $(CFLAGS) -c src/wrap.cc -o obj/wrap.o

obj/client_helper.o: obj include/clientHelper.cc include/clientHelper.h lib/fileserver.grpc.pb.h 
	$(CXX) -g $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -c include/clientHelper.cc -o obj/client_helper.o

bin/server: bin obj/fileserver.grpc.pb.o obj/fileserver.pb.o obj/server.o obj/serverImpl.o
	$(CXX) -o bin/server obj/fileserver.grpc.pb.o obj/fileserver.pb.o obj/server.o obj/serverImpl.o -g $(LDFLAGS)

obj/server.o: obj src/server.cc include/serverImpl.h
	$(CXX) -g $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -c src/server.cc -o obj/server.o 

obj/serverImpl.o: obj include/serverImpl.cc include/serverImpl.h lib/fileserver.grpc.pb.h
	$(CXX) -g $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -c include/serverImpl.cc -o obj/serverImpl.o

obj/fileserver.grpc.pb.o: obj lib/fileserver.grpc.pb.cc lib/fileserver.grpc.pb.h lib/fileserver.pb.h
	$(CXX) -g $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) -c lib/fileserver.grpc.pb.cc -o obj/fileserver.grpc.pb.o 

obj/fileserver.pb.o: obj lib/fileserver.pb.cc lib/fileserver.pb.h
	$(CXX) -g $(CXXFLAGS) $(CPPFLAGS) -c lib/fileserver.pb.cc -o obj/fileserver.pb.o
