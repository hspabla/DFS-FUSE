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

	return Status::OK;
}

Status FileSystemImpl::Write( ServerContext* context,
                              const WriteRequest* request,
				              WriteResponse* reply ) {

	return Status::OK;
}

