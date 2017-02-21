#include "clientHelper.h"

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


GetAttrResponse GetAttrClient::GetAttr(const GetAttrRequest & request ) {
  GetAttrResponse reply;
  ClientContext context;

  grpc::Status status = stub_->GetAttr( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}

MkdirResponse MkdirClient::Mkdir( const MkdirRequest & request ) {
  MkdirResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Mkdir( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}

OpenDirResponse OpenDirClient::Opendir( const OpenDirRequest & request ) {
  OpenDirResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Opendir( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}


