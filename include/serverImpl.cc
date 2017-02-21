#include "serverImpl.h"

Status FileSystemImpl::GetAttr( ServerContext* context,
                                 const GetAttrRequest* request,
                                 GetAttrResponse* reply ) {
	struct stat statbuf;
  	std::string path = request->name();
	int retstat = stat(path.c_str(), &statbuf);
	Attr attributes;
	FSstatus status;
	status.set_retcode(retstat);
 	attributes.set_dev(statbuf.st_dev);
	//attributes
	reply->mutable_attr()->CopyFrom(attributes);
	reply->mutable_status()->CopyFrom(status);
    printf("GRPC call successful\n");
    return Status::OK;
}

Status FileSystemImpl::Mkdir( ServerContext* context,
                              const MkdirRequest* request,
				              MkdirResponse* reply ) {

	// Mkdir implementation
	return Status::OK;
}

Status FileSystemImpl::Opendir( ServerContext* context,
                                const OpenDirRequest* request,
				                OpenDirResponse* reply ) {
	// openDir impementation
	return Status::OK;
}

Status FileSystemImpl::Open( ServerContext* context,
                             const OpenRequest* request,
				             OpenResponse* reply ) {
    int fileHandle = open( request->name().c_str(), request->flags() );
    reply->set_filehandle( fileHandle );
	return Status::OK;
}

Status FileSystemImpl::Read( ServerContext* context,
                             const ReadRequest* request,
				             ReadResponse* reply ) {

    char* buf = new char [ request->size() ];
    int byteRead = pread( request->filehandle(), buf,
                          request->size(), request->offset() );
    if ( byteRead < 0 ){
        // set error
    } else {
        reply->data().copy( buf, 0, byteRead );
    }
    reply->set_dataread( byteRead );

    delete buf;
	return Status::OK;
}

Status FileSystemImpl::Write( ServerContext* context,
                              const WriteRequest* request,
				              WriteResponse* reply ) {

    char *buf = new char[ request->size() ];
    memcpy( buf, request->data().c_str(), request->size() );

    int bytesWritten = pwrite( request->filehandle(), buf,
                               request->size(),
                               request->offset() );

    if ( bytesWritten < 0 ) {
        // set error code
    } else {
       reply->set_datawritten( bytesWritten );
    }

    delete buf;
    return Status::OK;
}

