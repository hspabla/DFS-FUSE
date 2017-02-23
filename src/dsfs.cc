#include "../include/dsfs.hh"
#include "../include/clientHelper.h"

DSFS* DSFS::_instance = NULL;

DSFS* DSFS::Instance() {
	if(_instance == NULL) {
		_instance = new DSFS();
	}
	return _instance;
}

DSFS::DSFS() {

}

DSFS::~DSFS() {

}

void DSFS::AbsPath(char dest[PATH_MAX], const char *path) {
	log_msg("dsfs_AbsPath:  rootdir = \"%s\", path = \"%s\", destination = \"%s\"\n", _root, path, dest);
        strcpy(dest, _root);
        strncat(dest, path, PATH_MAX);
}

void DSFS::setRootDir(const char *path) {
        _root = path;
}

int DSFS::Getattr(const char *path, struct stat *statbuf) {
    char fullPath[ PATH_MAX ];
    AbsPath( fullPath, path );
    log_msg("\ndsfs_Getattr(path=\"%s\", statbuf=%s)\n", path, *statbuf);

 	GetAttrClient client( grpc::CreateChannel(
                  		  "localhost:50051", grpc::InsecureChannelCredentials() ) );
	GetAttrRequest request;
	GetAttrResponse response;
	request.set_name(fullPath);
	try {
        response = client.GetAttr(request);
	    Attr attributes = response.attr();
	    FSstatus status = response.status();
        statbuf->st_dev = attributes.dev();
	    statbuf->st_ino = attributes.ino();
	    statbuf->st_mode = attributes.mode();
	    statbuf->st_nlink = attributes.nlink();
	    Owner owner = attributes.owner();
	    statbuf->st_uid = owner.uid();
        statbuf->st_gid = owner.gid();
        statbuf->st_rdev = attributes.rdev();
	    statbuf->st_size = attributes.size();
	    statbuf->st_blksize = attributes.blksize();
	    statbuf->st_blocks = attributes.blocks();
	    statbuf->st_atime = attributes.atime();
	    statbuf->st_mtime = attributes.mtime();
	    statbuf->st_ctime = attributes.ctime();

	    if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
	    } else {
            log_msg("Return Code: %d\n", status.retcode());
		    errno = status.retcode();
            return errno;
	   }
	} catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
	    return -1;
	}
}

int DSFS::Mknod(const char *path, mode_t mode, dev_t dev) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Mknod(path=%s, mode=%d, dev=%d)\n", path, mode, dev);
	MknodClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    MknodRequest request;
    request.set_name(fullPath);
    request.set_mode(mode);
	request.set_dev(dev);
    try {
       MknodResponse response = client.Mknod(request);
       FSstatus status = response.status();
       if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
	   } else {
	       errno = status.retcode();
           log_msg("Return Code: %d\n", status.retcode());
           return errno;
	   }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Mkdir(const char *path, mode_t mode) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Mkdir(path=%s, mode=%d)\n", path, mode);

    MkdirClient client( grpc::CreateChannel(
                        "localhost:50051", grpc::InsecureChannelCredentials() ) );
    MkdirRequest request;
    MkdirResponse response;
    request.set_name(fullPath);
    request.set_mode(mode);
    try {
        response = client.Mkdir(request);
	    FSstatus status = response.status();
	    if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
	        return 0;
	    } else {
	        errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Unlink(const char *path) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Unlink(path=%s)\n", path);

    UnlinkClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    UnlinkRequest request;
    request.set_name(fullPath);
    try {
        UnlinkResponse response = client.Unlink(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
	    } else {
	        errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Rmdir(const char *path) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Rmdir(path=%s)\n", path);

    RmdirClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    RmdirRequest request;
    request.set_name(fullPath);
    try {
        RmdirResponse response = client.Rmdir(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
	    } else {
	        errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Rename(const char *path, const char *newpath) {
    char fullPath[PATH_MAX], newFullPath[PATH_MAX];
    AbsPath(fullPath, path);
	AbsPath(newFullPath, newpath);
	log_msg("dsfs_Rename(path=\"%s\", newpath=\"%s\")\n", path, newpath);

    RenameClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    RenameRequest request;
    request.set_oldname(fullPath);
	request.set_newname(newFullPath);
    try {
        RenameResponse response = client.Rename(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
	    } else {
	        errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Chmod(const char *path, mode_t mode) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Chmod(path=%s, mode=%d)\n", path, mode);

	ChmodClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ChmodRequest request;
    request.set_name( fullPath );
    request.set_mode( mode );
    try {
        ChmodResponse response = client.Chmod( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
           log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Chown(const char *path, uid_t uid, gid_t gid) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Chown(path=%s, uid=%d, gid=%d)\n", path, (int)uid, (int)gid);

	ChownClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ChownRequest request;
    request.set_name( fullPath );
    request.set_uid( uid );
    request.set_gid( gid );
    try {
        ChownResponse response = client.Chown( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Truncate(const char *path, off_t newSize) {
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Truncate(path=%s, newSize=%d)\n", path, (int)newSize);

    TruncateClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    TruncateRequest request;
    request.set_name( fullPath );
    request.set_size( newSize );
    try {
        TruncateResponse response = client.Truncate( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Access(const char *path, int mask)
{
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Access(path=%s, mask=%d)\n", path, mask);

    AccessClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    AccessRequest request;
    request.set_name( fullPath );
    request.set_mode( mask );
    try {
        AccessResponse response = client.Access( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Open(const char *path, struct fuse_file_info *fileInfo) {
	char fullPath[ PATH_MAX ];
	AbsPath( fullPath, path );
    log_msg("dsfs_Open(path=%s, fileHandle=%d, flags=%d)\n", path, (int)fileInfo->fh, (int)fileInfo->flags);

	// RPC request prep
	OpenClient client( grpc::CreateChannel(
			   "localhost:50051", grpc::InsecureChannelCredentials() ) );
	OpenRequest request;
	request.set_name( fullPath );
	request.set_flags( fileInfo->flags );

    try {
        OpenResponse response = client.Open( request );
        fileInfo->fh = response.filehandle();

        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {

    log_msg("dsfs_Read(path=%s, size=%d, offset=%d, fileHandle=%d, flags=%d)\n",
        path, (int)size, (int)offset, (int)fileInfo->fh, (int)fileInfo->flags);


	// RPC request prep
	ReadClient client( grpc::CreateChannel(
			   "localhost:50051", grpc::InsecureChannelCredentials() ) );
	ReadRequest request;

	request.set_filehandle( fileInfo->fh );
	request.set_size( size );
	request.set_offset( offset );

    try {
        // RPC call
	    ReadResponse response = client.Read( request );
        FSstatus status = response.status();

        if ( status.retcode() == 0 ) {
	        int byteRead = response.dataread();
	        if ( byteRead > 0 )
		        memcpy( buf, response.data().c_str(), byteRead );
            log_msg("Return Code: %d\n", status.retcode());
            return byteRead;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {

    log_msg("dsfs_Write(path=%s, size=%d, offset=%d, fileHandle=%d, flags=%d)\n",
        path, (int)size, (int)offset, (int)fileInfo->fh, (int)fileInfo->flags);

	std::string data( buf, size );

	// RPC request prep
	WriteClient client( grpc::CreateChannel(
			   "localhost:50051", grpc::InsecureChannelCredentials() ) );
	WriteRequest request;

	request.set_filehandle( fileInfo->fh );
	request.set_data( data );
	request.set_size( size );
	request.set_offset( offset );

    try {
        // RPC call
	    WriteResponse response = client.Write( request );
        FSstatus status = response.status();

        if ( status.retcode() == 0 ) {
            // update local buffer, if fh is not in map, it will be added this way
            dataBuffer[ fileInfo->fh ].append( buf, size );
            log_msg("Return Code: %d\n", status.retcode());
            return size;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Release(const char *path, struct fuse_file_info *fileInfo) {
    log_msg("dsfs_Release(path=%s)\n", path);

    ReleaseClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ReleaseRequest request;
    request.set_filehandle(fileInfo->fh);
    try {
        ReleaseResponse response = client.Release(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    log_msg("dsfs_Fsync(path=%s, fileHandle=%d, datasync=%d\n", path, (int) fi->fh, datasync);

    FsyncClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    FsyncRequest request;
    request.set_filehandle( fi->fh );
    try {
        FsyncResponse response = client.Fsync( request );
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            // Data successfully on disk, we can remove stuff from local buffer
            log_msg("Return Code: %d\n", status.retcode());
            dataBuffer.erase( fi->fh );
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

//Extended attributes not implemented for RPC calls.

int DSFS::Setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
    log_msg("dsfs_Setxattr(path=%s, name=%s, value=%s, size=%d, flags=%d\n",
        path, name, value, (int)size, flags);
	return 0;
}

int DSFS::Getxattr(const char *path, const char *name, char *value, size_t size) {
    log_msg("dsfs_Getxattr(path=%s, name=%s, size=%d)\n", path, name, (int)size);
	return 0;
}

int DSFS::Listxattr(const char *path, char *list, size_t size) {
    log_msg("dsfs_Listxattr(path=%s, list=%s, size=%d)\n", path, list, (int)size);
	return 0;
}

int DSFS::Removexattr(const char *path, const char *name) {
    log_msg("dsfs_Removexattr(path=%s, name=%s)\n", path, name);
	return 0;
}

int DSFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo)
{
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
    log_msg("dsfs_Readdir(path=%s, offset=%d)\n", path, (int)offset);

	std::shared_ptr<Channel> channel = grpc::CreateChannel(
                                  "localhost:50051", grpc::InsecureChannelCredentials() );
    OpenDirClient client( channel);
    OpenDirRequest request;
    OpenDirResponse response;
    request.set_name(fullPath);
    try {
        response = client.Opendir(request);
	    FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            for(int i=0; i< response.dirs_size(); i++) {
                struct stat st;
                memset(&st, 0, sizeof(st));
                DirEntry dir = response.dirs(i);
                st.st_ino = dir.ino();
                st.st_mode = dir.mode() << 12;
                if (filler(buf, (dir.name()).c_str(), &st, 0) != 0)
                    break;
            }
            log_msg("Return Code: %d\n", status.retcode());
            return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Releasedir(const char *path, struct fuse_file_info *fileInfo) {
    log_msg("dsfs_Releasedir(path=%s)\n", path);

    ReleasedirClient client( grpc::CreateChannel(
                               "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ReleasedirRequest request;
    request.set_filehandle(fileInfo->fh);
    try {
        ReleasedirResponse response = client.Releasedir(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            log_msg("Return Code: %d\n", status.retcode());
             return 0;
        } else {
            errno = status.retcode();
            log_msg("Return Code: %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Init(struct fuse_conn_info *conn) {
	log_msg("\ndsfs_init()\n");
	log_conn(conn);
	log_fuse_context(fuse_get_context());
    return 0;
}

/*int DSFS::Flush(const char *path, struct fuse_file_info *fileInfo) {
        printf("flush(path=%s)\n", path);
        //noop because we don't maintain our own buffers
        return 0;
}*/
