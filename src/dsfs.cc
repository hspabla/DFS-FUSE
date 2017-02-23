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
        strcpy(dest, _root);
        strncat(dest, path, PATH_MAX);
        printf("translated path: %s to %s\n", path, dest);
}

void DSFS::setRootDir(const char *mountPath, const char *path) {
        printf("setting FS root for %s to: %s\n", mountPath, path);
        _root = path;
}

int DSFS::Getattr(const char *path, struct stat *statbuf) {
    char fullPath[ PATH_MAX ];
    AbsPath( fullPath, path );
    printf( "getattr(%s)\n", fullPath );
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
            return 0;
	    } else {
		    printf("We threw the error code %d\n", status.retcode());
		    errno = status.retcode();
            return errno;
	   }
	} catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
	    return -1;
	}
}

int DSFS::Mknod(const char *path, mode_t mode, dev_t dev) {
    printf("mknod(path=%s, mode=%d)\n", path, mode);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
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
            return 0;
	   } else {
	       printf("error : %d\n", status.retcode());
	       errno = status.retcode();
           return errno;
	   }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Mkdir(const char *path, mode_t mode) {
    printf("**mkdir(path=%s, mode=%d)\n", path, (int)mode);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
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
	        return 0;
	    } else {
	        printf("error : %d\n", status.retcode());
	        errno = status.retcode();
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Unlink(const char *path) {
    printf("unlink(path=%s\n)", path);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);

    UnlinkClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    UnlinkRequest request;
    request.set_name(fullPath);
    try {
        UnlinkResponse response = client.Unlink(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            return 0;
	    } else {
	        printf("error : %d\n", status.retcode());
	        errno = status.retcode();
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Rmdir(const char *path) {
    printf("rmdir(path=%s\n)", path);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);

    RmdirClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    RmdirRequest request;
    request.set_name(fullPath);
    try {
        RmdirResponse response = client.Rmdir(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            return 0;
	    } else {
	        printf("error : %d\n", status.retcode());
	        errno = status.retcode();
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Rename(const char *path, const char *newpath) {
    printf("rename(path=%s, newPath=%s)\n", path, newpath);
    char fullPath[PATH_MAX], newFullPath[PATH_MAX];
    AbsPath(fullPath, path);
	AbsPath(newFullPath, newpath);

    RenameClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    RenameRequest request;
    request.set_oldname(fullPath);
	request.set_newname(newFullPath);
    try {
        RenameResponse response = client.Rename(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            return 0;
	    } else {
	        printf("error : %d\n", status.retcode());
	        errno = status.retcode();
            return errno;
	    }
    } catch ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Chmod(const char *path, mode_t mode) {
    printf("chmod(path=%s, mode=%d)\n", path, mode);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);

	ChmodClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ChmodRequest request;
    request.set_name( fullPath );
    request.set_mode( mode );
    try {
        ChmodResponse response = client.Chmod( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Chown(const char *path, uid_t uid, gid_t gid) {
    printf("chown(path=%s, uid=%d, gid=%d)\n", path, (int)uid, (int)gid);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);

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
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Truncate(const char *path, off_t newSize) {
    printf("truncate(path=%s, newSize=%d\n", path, (int)newSize);
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);

    TruncateClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    TruncateRequest request;
    request.set_name( fullPath );
    request.set_size( newSize );
    try {
        TruncateResponse response = client.Truncate( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
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

    printf("access(path=%s)\n", fullPath);

    AccessClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    AccessRequest request;
    request.set_name( fullPath );
    request.set_mode( mask );
    try {
        AccessResponse response = client.Access( request );
        FSstatus status = response.status();
        if ( status.retcode() == 0 ) {
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
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
	        printf( "open (path=%s, fileHandle=%d, flags=%d)\n",
	                fullPath, (int)fileInfo->fh, (int)fileInfo->flags);
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {

	printf( "read(path=%s, size=%d, offset=%d, fileHandle=%d, flags=%d)\n",
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
            return byteRead;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {

	printf( "write(path=%s, size=%d, offset=%d, fileHandle=%d, flags=%d)\n",
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
	        int bytesWritten = response.datawritten();
            return bytesWritten;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Release(const char *path, struct fuse_file_info *fileInfo) {
    printf("release(path=%s)\n", path);

    ReleaseClient client( grpc::CreateChannel(
                              "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ReleaseRequest request;
    request.set_filehandle(fileInfo->fh);
    try {
        ReleaseResponse response = client.Release(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Fsync(const char *path, int datasync, struct fuse_file_info *fi) {
    printf("fsync(path=%s, datasync=%d\n", path, datasync);
    FsyncClient client( grpc::CreateChannel(
                       "localhost:50051", grpc::InsecureChannelCredentials() ) );
    FsyncRequest request;
    request.set_filehandle( fi->fh );
    try {
        FsyncResponse response = client.Fsync( request );
        FSstatus status = response.status();
        if (status.retcode() == 0) {
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

//Extended attributes not implemented for RPC calls.

int DSFS::Setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
        printf("setxattr(path=%s, name=%s, value=%s, size=%d, flags=%d\n",
                path, name, value, (int)size, flags);
	return 0;
}

int DSFS::Getxattr(const char *path, const char *name, char *value, size_t size) {
        printf("getxattr(path=%s, name=%s, size=%d\n", path, name, (int)size);
	return 0;
}

int DSFS::Listxattr(const char *path, char *list, size_t size) {
        printf("listxattr(path=%s, size=%d)\n", path, (int)size);
	return 0;
}

int DSFS::Removexattr(const char *path, const char *name) {
        printf("removexattry(path=%s, name=%s)\n", path, name);
	return 0;
}

int DSFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo)
{
    char fullPath[PATH_MAX];
    AbsPath(fullPath, path);
	printf("readdir(path=%s, offset=%d)\n", fullPath, (int)offset);

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
            //DirEntry dirs = response.dirs();
            for(int i=0; i< response.dirs_size(); i++) {
                struct stat st;
                memset(&st, 0, sizeof(st));
                DirEntry dir = response.dirs(i);
                st.st_ino = dir.ino();
                st.st_mode = dir.mode() << 12;
                if (filler(buf, (dir.name()).c_str(), &st, 0) != 0)
                    break;
            }
            return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
            return errno;
        }
    } catch  ( std::string errorMsg ) {
        std::cout << errorMsg << std::endl;
        return -1;
    }
}

int DSFS::Releasedir(const char *path, struct fuse_file_info *fileInfo) {
    printf("releasedir(path=%s)\n", path);
    ReleasedirClient client( grpc::CreateChannel(
                               "localhost:50051", grpc::InsecureChannelCredentials() ) );
    ReleasedirRequest request;
    request.set_filehandle(fileInfo->fh);
    try {
        ReleasedirResponse response = client.Releasedir(request);
        FSstatus status = response.status();
        if (status.retcode() == 0) {
             return 0;
        } else {
            errno = status.retcode();
            printf("error : %d\n", status.retcode());
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
