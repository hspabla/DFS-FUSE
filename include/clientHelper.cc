#include "clientHelper.h"

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


OpenResponse OpenClient::Open( const OpenRequest & request ) {
  OpenResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Open( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}


ReadResponse ReadClient::Read( const ReadRequest & request ) {
  ReadResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Read( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}


WriteResponse WriteClient::Write( const WriteRequest & request ) {
  WriteResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Write( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}
