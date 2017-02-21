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
	int retstat = lstat(path.c_str(), &statbuf);

	//Populate the response
	Owner owner;
	owner.set_uid(statbuf.st_uid);
	owner.set_gid(statbuf.st_gid);

        FSstatus status;
	status.set_retcode(retstat);

        Attr attributes;
 	attributes.set_dev(statbuf.st_dev);
	attributes.set_ino(statbuf.st_ino);
	attributes.set_mode(statbuf.st_mode);
	attributes.set_st_nlink(statbuf.st_nlink);
	attributes.mutable_owner()->CopyFrom(owner);
	attributes.set_rdev(statbuf.st_rdev);
	attributes.set_size(statbuf.st_size);
	attributes.set_blksize(statbuf.st_blksize);
	attributes.set_blocks(statbuf.st_blocks);
	attributes.set_atime(statbuf.st_atime);
	attributes.set_mtime(statbuf.st_mtime);
	attributes.set_ctime(statbuf.st_ctime);

	reply->mutable_attr()->CopyFrom(attributes);
	reply->mutable_status()->CopyFrom(status);
	return Status::OK;
}

Status FileSystemImpl::Mkdir( ServerContext* context,
                              const MkdirRequest* request,
				              MkdirResponse* reply ) {

	// Mkdir implementation
	std::string path = request->name();
	int retstat = mkdir(path.c_str(), request->mode());

	//Populate the response
	FSstatus status;
        status.set_retcode(retstat);
	reply->mutable_status()->CopyFrom(status);
	return Status::OK; 
}

Status FileSystemImpl::Opendir( ServerContext* context,
                                const OpenDirRequest* request,
				                OpenDirResponse* reply ) {
	// openDir impementation
 	std::string path = request->name();
	DIR *dp;
        struct dirent *de;

        dp = opendir(path.c_str());

        FSstatus status;
	if (dp == NULL) 
		status.set_retcode(-1);

 	//while ((de = readdir(dp)) != NULL) {
			
		
 //	int retstat = mkdir(path.c_str(), request->mode());		
	return Status::OK;
}



