#include "serverImpl.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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



