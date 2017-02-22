#include "clientHelper.h"

GetAttrResponse GetAttrClient::GetAttr(const GetAttrRequest & request ) {
    GetAttrResponse reply;
    ClientContext context;
    Status status = stub_->GetAttr( &context, request, &reply );
    if ( status.ok() ) {
        printf("status ok\n");
        return reply;
    } else {
        std::cout << status.error_code() << ": " << status.error_message()
                  << std::endl;
        throw status.error_message();
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
        throw status.error_message();
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
        throw status.error_message();
     }
}

MknodResponse MknodClient::Mknod( const MknodRequest & request ) {
    MknodResponse reply;
    ClientContext context;

     grpc::Status status = stub_->Mknod( &context, request, &reply );

     if (status.ok()) {
        return reply;
     } else {
        std::cout << status.error_code() << ": " << status.error_message()
              << std::endl;
        throw status.error_message();
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
        throw status.error_message();
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
       throw status.error_message();
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
       throw status.error_message();
    }
}

UnlinkResponse UnlinkClient::Unlink( const UnlinkRequest & request ) {
    UnlinkResponse reply;
    ClientContext context;

    grpc::Status status = stub_->Unlink( &context, request, &reply );

    if (status.ok()) {
       return reply;
    } else {
       std::cout << status.error_code() << ": " << status.error_message()
             << std::endl;
       throw status.error_message();
    }
}

RenameResponse RenameClient::Rename( const RenameRequest & request ) {
    RenameResponse reply;
    ClientContext context;

    grpc::Status status = stub_->Rename( &context, request, &reply );

    if (status.ok()) {
       return reply;
    } else {
       std::cout << status.error_code() << ": " << status.error_message()
             << std::endl;
       throw status.error_message();
    }
}

RmdirResponse RmdirClient::Rmdir( const RmdirRequest & request ) {
    RmdirResponse reply;
    ClientContext context;

    grpc::Status status = stub_->Rmdir( &context, request, &reply );

    if (status.ok()) {
       return reply;
    } else {
       std::cout << status.error_code() << ": " << status.error_message()
             << std::endl;
       throw status.error_message();
    }
}

ReleaseResponse ReleaseClient::Release( const ReleaseRequest & request ) {
    ReleaseResponse reply;
    ClientContext context;

    grpc::Status status = stub_->Release( &context, request, &reply );

    if (status.ok()) {
       return reply;
    } else {
       std::cout << status.error_code() << ": " << status.error_message()
             << std::endl;
       throw status.error_message();
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
       throw status.error_message();
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
       throw status.error_message();
    }
}

ReleasedirResponse ReleasedirClient::Releasedir( const ReleasedirRequest & request ) {
    ReleasedirResponse reply;
    ClientContext context;
    grpc::Status status = stub_->Releasedir( &context, request, &reply );

    if (status.ok()) {
       return reply;
    } else {
       std::cout << status.error_code() << ": " << status.error_message()
             << std::endl;
       throw status.error_message();
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
       throw status.error_message();
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
       throw status.error_message();
    }
}

FsyncResponse FsyncClient::Fsync( const FsyncRequest & request ) {
    FsyncResponse reply;
    ClientContext context;
    grpc::Status status = stub_->Fsync( &context, request, &reply );

    if (status.ok()) {
       return reply;
    } else {
       std::cout << status.error_code() << ": " << status.error_message()
             << std::endl;
       throw status.error_message();
    }
}
