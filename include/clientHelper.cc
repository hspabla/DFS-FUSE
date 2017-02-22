#include "clientHelper.h"

GetAttrResponse GetAttrClient::GetAttr(const GetAttrRequest & request ) {
  GetAttrResponse reply;
  ClientContext context;

  grpc::Status status = stub_->GetAttr( &context, request, &reply );

  if (status.ok()) {
    printf("status ok\n");
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

  try {
     grpc::Status status = stub_->Opendir( &context, request, &reply );

     if (status.ok()) {
        return reply;
     } else {
        std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
        throw status.error_code();
     }
  } catch (int errCode) {
  }
}

MknodResponse MknodClient::Mknod( const MknodRequest & request ) {
  MknodResponse reply;
  ClientContext context;

  try {
     grpc::Status status = stub_->Mknod( &context, request, &reply );

     if (status.ok()) {
        return reply;
     } else {
        std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
        throw status.error_code();
     }
  } catch (int errCode) {
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


ChownResponse ChownClient::Chown( const ChownRequest & request ) {
  ChownResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Chown( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}


ChmodResponse ChmodClient::Chmod( const ChmodRequest & request ) {
  ChmodResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Chmod( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}


AccessResponse AccessClient::Access( const AccessRequest & request ) {
  AccessResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Access( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}


TruncateResponse TruncateClient::Truncate( const TruncateRequest & request ) {
  TruncateResponse reply;
  ClientContext context;

  grpc::Status status = stub_->Truncate( &context, request, &reply );

  if (status.ok()) {
    return reply;
  } else {
    std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
    throw status.error_code();
  }
}

