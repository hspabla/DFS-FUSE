#include "serverImpl.h"

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
	int index = 0;

        dp = opendir(path.c_str());

        FSstatus status;
	if (dp == NULL) 
		status.set_retcode(-1);

 	while ((de = readdir(dp)) != NULL) {
		DirEntry entry;
		entry.set_name(de->d_name);
		entry.set_ino(de->d_ino);
		entry.set_mode(de->d_type << 12);
	 	reply->mutable_dirs(index++)->CopyFrom(entry);
	}
	status.set_retcode(0);
        reply->mutable_status()->CopyFrom(status);	
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

