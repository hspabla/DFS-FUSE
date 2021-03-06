#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "../lib/fileserver.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using namespace dfsFuse;

class GetAttrClient {
 public:
  GetAttrClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  GetAttrResponse GetAttr( const GetAttrRequest& request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};


class MkdirClient {
 public:
  MkdirClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  MkdirResponse Mkdir( const MkdirRequest& request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class OpenDirClient {
 public:
  OpenDirClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  OpenDirResponse Opendir( const OpenDirRequest& request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class MknodClient{
 public:
  MknodClient( std::shared_ptr<Channel> channel )
                                                                : stub_( FileSystem::NewStub( channel ) ) { }
  MknodResponse Mknod( const MknodRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};


class OpenClient {
 public:
  OpenClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  OpenResponse Open( const OpenRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};


class ReadClient {
 public:
  ReadClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  ReadResponse Read( const ReadRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};



class WriteClient {
 public:
  WriteClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  WriteResponse Write( const WriteRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class UnlinkClient {
 public:
  UnlinkClient( std::shared_ptr<Channel> channel )
                                                                : stub_( FileSystem::NewStub( channel ) ) { }
  UnlinkResponse Unlink( const UnlinkRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class RmdirClient {
 public:
  RmdirClient( std::shared_ptr<Channel> channel )
                                                                : stub_( FileSystem::NewStub( channel ) ) { }
  RmdirResponse Rmdir( const RmdirRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};


class ChmodClient {
 public:
  ChmodClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  ChmodResponse Chmod( const ChmodRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class RenameClient {
 public:
  RenameClient( std::shared_ptr<Channel> channel )
                                                                : stub_( FileSystem::NewStub( channel ) ) { }
  RenameResponse Rename( const RenameRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class ReleaseClient {
 public:
  ReleaseClient( std::shared_ptr<Channel> channel )
                                                                : stub_( FileSystem::NewStub( channel ) ) { }
  ReleaseResponse Release( const ReleaseRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class ChownClient {
 public:
  ChownClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  ChownResponse Chown( const ChownRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class ReleasedirClient {
 public:
  ReleasedirClient( std::shared_ptr<Channel> channel )
                                                                : stub_( FileSystem::NewStub( channel ) ) { }
  ReleasedirResponse Releasedir( const ReleasedirRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class TruncateClient {
 public:
  TruncateClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  TruncateResponse Truncate( const TruncateRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class AccessClient {
 public:
  AccessClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  AccessResponse Access( const AccessRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class FsyncClient {
 public:
  FsyncClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  FsyncResponse Fsync( const FsyncRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};


