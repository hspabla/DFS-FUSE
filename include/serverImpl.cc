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
                                 const struct GetAttrRequest* request,
                                 struct GetAttrResponse* reply ) {
	// implement get Attr based on request
	//std::string prefix("Hello ");
    //reply->set_message(prefix + request->name());
    return Status::OK;
}

Status FileSystemImpl::Mkdir( ServerContext* context,
                              const struct MkdirRequest* request,
				              struct MkdirResponse* reply ) {

	// Mkdir implementation
	return Status::OK;
}

Status FileSystemImpl::Opendir( ServerContext* context,
                                const struct OpenDirRequest* request,
				                struct OpenDirResponse* reply ) {
	// openDir impementation
	return Status::OK;
}



