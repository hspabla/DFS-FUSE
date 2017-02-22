#include <iostream>
#include <memory>
#include <string>

#include <grpc++/grpc++.h>
#include "../lib/fileserver.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using dfsFuse::FileSystem;
using dfsFuse::FSstatus;
using dfsFuse::Owner;
using dfsFuse::ClientInfo;
using dfsFuse::Attr;
using dfsFuse::GetAttrRequest;
using dfsFuse::GetAttrResponse;
using dfsFuse::MkdirRequest;
using dfsFuse::MkdirResponse;
using dfsFuse::OpenDirRequest;
using dfsFuse::DirEntry;
using dfsFuse::OpenDirResponse;
using dfsFuse::MknodRequest;
using dfsFuse::MknodResponse;
using dfsFuse::OpenRequest;
using dfsFuse::OpenResponse;
using dfsFuse::ReadRequest;
using dfsFuse::ReadResponse;
using dfsFuse::WriteRequest;
using dfsFuse::WriteResponse;

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
