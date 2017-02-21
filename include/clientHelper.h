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

class GetAttrClient {
 public:
  GetAttrClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  struct GetAttrResponse GetAttr( const struct GetAttrRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};


class MkdirClient {
 public:
  MkdirClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  struct MkdirResponse Mkdir( const struct MkdirRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};

class OpendirClient {
 public:
  OpendirClient( std::shared_ptr<Channel> channel )
      								: stub_( FileSystem::NewStub( channel ) ) { }
  struct OpendirResponse Opendir( const struct OpendirRequest & request );

 private:
  std::unique_ptr<FileSystem::Stub> stub_;
};



