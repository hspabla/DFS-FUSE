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
	status.set_retcode(retstat == 0 ? 0 : -errno);

    Attr attributes;
 	attributes.set_dev(statbuf.st_dev);
	attributes.set_ino(statbuf.st_ino);
	attributes.set_mode(statbuf.st_mode);
	attributes.set_nlink(statbuf.st_nlink);
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
	int mode = request->mode();
	int retstat = mkdir(path.c_str(), mode);
	printf("mkdir(path=%s, mode=%d, restat=%d)\n", path.c_str(), mode, retstat);

	//Populate the response
	FSstatus status;
        status.set_retcode(retstat == 0 ? 0 : -errno);
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
	int index = 1;

    dp = opendir(path.c_str());
    FSstatus status;

    if (dp == NULL) {
		status.set_retcode(-errno);
        reply->mutable_status()->CopyFrom(status);
        return Status::OK;
    }

 	while ( (de = readdir(dp) ) != NULL) {
	 	DirEntry *entry = reply->add_dirs();
        entry->set_name(de->d_name);
        entry->set_ino(de->d_ino);
        entry->set_mode(de->d_type << 12);
	}
	status.set_retcode(0);
    reply->mutable_status()->CopyFrom(status);
	return Status::OK;
}

Status FileSystemImpl::Mknod( ServerContext* context, const MknodRequest* request,
                                MknodResponse* reply ) {

    // Mknod implementation
    std::string path = request->name();
    int mode = request->mode();
    int dev = request->dev();
    int retstat = mknod(path.c_str(), mode, dev);

    // Populate response
    FSstatus status;
    status.set_retcode( retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Open( ServerContext* context,
                             const OpenRequest* request,
				             OpenResponse* reply ) {
    int fileHandle = open( request->name().c_str(), request->flags() );
    FSstatus status;
    status.set_retcode( fileHandle > 0 ? 0 : -errno);
    reply->set_filehandle( fileHandle );
	reply->mutable_status()->CopyFrom(status);
	return Status::OK;
}

Status FileSystemImpl::Read( ServerContext* context,
                             const ReadRequest* request,
				             ReadResponse* reply ) {

    char* buf = new char [ request->size() ];
    int byteRead = pread( request->filehandle(), buf,
                          request->size(), request->offset() );

	FSstatus status;
    if ( byteRead < 0 ){
	    status.set_retcode(-errno);
    } else {
	    status.set_retcode(0);
    	reply->set_data( buf, byteRead );
	    reply->set_dataread( byteRead );
    }
	reply->mutable_status()->CopyFrom(status);

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

    FSstatus status;
    if ( bytesWritten < 0 ) {
        status.set_retcode(-errno);
    } else {
        status.set_retcode(0);
        reply->set_datawritten( bytesWritten );
    }
    reply->mutable_status()->CopyFrom(status);

    delete buf;
    return Status::OK;
}

Status FileSystemImpl::Unlink( ServerContext* context,
                              const UnlinkRequest* request,
                                              UnlinkResponse* reply ) {

    // Unlink implementation
    std::string path = request->name();
    int retstat = unlink(path.c_str());

    //Populate the response
    FSstatus status;
    status.set_retcode(retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Rmdir( ServerContext* context,
                              const RmdirRequest* request,
                                              RmdirResponse* reply ) {

    // Rmdir implementation
    std::string path = request->name();
    int retstat = rmdir(path.c_str());

    //Populate the response
    FSstatus status;
    status.set_retcode(retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Rename( ServerContext* context,
                              const RenameRequest* request,
                                              RenameResponse* reply ) {

    // Rename implementation
    std::string oldPath = request->oldname();
	std::string newPath = request->newname();
    int retstat = rename(oldPath.c_str(), newPath.c_str());

    //Populate the response
    FSstatus status;
    status.set_retcode(retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Release( ServerContext* context,
                              const ReleaseRequest* request,
                                              ReleaseResponse* reply ) {

    // Release/Close implementation
    int retstat = close(request->filehandle());

    //Populate the response
    FSstatus status;
    status.set_retcode(retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Chmod( ServerContext* context, const ChmodRequest* request,
                              ChmodResponse* reply ) {

    // Chmod implementation
    std::string path = request->name();
    int mode = request->mode();
    int retstat = chmod( path.c_str(), mode );

    // Populate response
    FSstatus status;
    status.set_retcode( retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Chown( ServerContext* context, const ChownRequest* request,
                              ChownResponse* reply ) {

    // Chown implementation
    std::string path = request->name();
    int uid = request->uid();
    int gid = request->gid();
    int retstat = chown( path.c_str(), uid, gid );

    // Populate response
    FSstatus status;
    status.set_retcode( retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Releasedir( ServerContext* context,
                              const ReleasedirRequest* request,
                                              ReleasedirResponse* reply ) {

    // Release/Close directory implementation
    int retstat = closedir( (DIR *) (uintptr_t) request->filehandle());

    //Populate the response
    FSstatus status;
    status.set_retcode(retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Access( ServerContext* context, const AccessRequest* request,
                               AccessResponse* reply ) {

    // access implementation
    std::string path = request->name();
    int mode = request->mode();
    int retstat = access( path.c_str(), mode );

    // Populate response
    FSstatus status;
    status.set_retcode( retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}


Status FileSystemImpl::Truncate( ServerContext* context,
                                 const TruncateRequest* request,
                                 TruncateResponse* reply ) {

    // Truncate implementation
    std::string path = request->name();
    int size = request->size();
    int retstat = truncate( path.c_str(), size );

    // Populate response
    FSstatus status;
    status.set_retcode( retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}

Status FileSystemImpl::Fsync( ServerContext* context,
                                 const FsyncRequest* request,
                                 FsyncResponse* reply ) {

    // Fsync implementation
    int filehandle = request->filehandle();
    int retstat = fsync( filehandle );

    // Populate response
    FSstatus status;
    status.set_retcode( retstat == 0 ? 0 : -errno);
    reply->mutable_status()->CopyFrom(status);
    return Status::OK;
}
