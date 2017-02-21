#include "../include/dsfs.hh"

DSFS* DSFS::_instance = NULL;

#define RETURN_ERRNO(x) (x) == 0 ? 0 : -errno

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
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        printf("getattr(%s)\n", fullPath);
        return RETURN_ERRNO(lstat(fullPath, statbuf));
}

int DSFS::Readlink(const char *path, char *link, size_t size) {
        printf("readlink(path=%s, link=%s, size=%d)\n", path, link, (int)size);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(readlink(fullPath, link, size));
}

int DSFS::Mknod(const char *path, mode_t mode, dev_t dev) {
        char fullPath[PATH_MAX];int retstat;
        AbsPath(fullPath, path);
        printf("mknod(path=%s, mode=%d)\n", fullPath, mode);

    	if (S_ISREG(mode)) {
   		retstat = open(fullPath, O_CREAT | O_EXCL | O_WRONLY, mode);
		printf("file created %d\n", retstat);
   		if (retstat >= 0)
       			return RETURN_ERRNO(close(retstat));
    	} else
   		if (S_ISFIFO(mode))
       			return RETURN_ERRNO(mkfifo(fullPath, mode));
   		else
       			return RETURN_ERRNO(mknod(fullPath, mode, dev));
}

/*
int DSFS::Mknod(const char *path, mode_t mode, dev_t dev) {
        printf("mknod(path=%s, mode=%d)\n", path, mode);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);

        //handles creating FIFOs, regular files, etc...
        return RETURN_ERRNO(mknod(fullPath, mode, dev));
}*/

int DSFS::Mkdir(const char *path, mode_t mode) {
        printf("**mkdir(path=%s, mode=%d)\n", path, (int)mode);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(mkdir(fullPath, mode));
}

int DSFS::Unlink(const char *path) {
        printf("unlink(path=%s\n)", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(unlink(fullPath));
}

int DSFS::Rmdir(const char *path) {
        printf("rmdir(path=%s\n)", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(rmdir(fullPath));
}

int DSFS::Symlink(const char *path, const char *link) {
        printf("symlink(path=%s, link=%s)\n", path, link);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(symlink(fullPath, link));
}


int DSFS::Rename(const char *path, const char *newpath) {
        printf("rename(path=%s, newPath=%s)\n", path, newpath);
        char fullPath[PATH_MAX], newFullPath[PATH_MAX];
        AbsPath(fullPath, path);
	AbsPath(newFullPath, newpath);
        return RETURN_ERRNO(rename(fullPath, newFullPath));
}

int DSFS::Link(const char *path, const char *newpath) {
        printf("link(path=%s, newPath=%s)\n", path, newpath);
        char fullPath[PATH_MAX];
        char fullNewPath[PATH_MAX];
        AbsPath(fullPath, path);
        AbsPath(fullNewPath, newpath);
        return RETURN_ERRNO(link(fullPath, fullNewPath));
}

int DSFS::Chmod(const char *path, mode_t mode) {
        printf("chmod(path=%s, mode=%d)\n", path, mode);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(chmod(fullPath, mode));
}

int DSFS::Chown(const char *path, uid_t uid, gid_t gid) {
        printf("chown(path=%s, uid=%d, gid=%d)\n", path, (int)uid, (int)gid);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(chown(fullPath, uid, gid));
}

int DSFS::Truncate(const char *path, off_t newSize) {
        printf("truncate(path=%s, newSize=%d\n", path, (int)newSize);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(truncate(fullPath, newSize));
}

int DSFS::Utime(const char *path, struct utimbuf *ubuf) {
        printf("utime(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(utime(fullPath, ubuf));
}

int DSFS::Access(const char *path, int mask)
{
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        
        printf("access(path=%s)\n", fullPath);
	return RETURN_ERRNO(access(fullPath, mask));
}

int DSFS::Open(const char *path, struct fuse_file_info *fileInfo) {
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        fileInfo->fh = open(fullPath, fileInfo->flags);
        printf("open(path=%s, fileHandle=%d, flags=%d)\n", fullPath, (int)fileInfo->fh, (int)fileInfo->flags);
        return 0;
}

int DSFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
        printf("read(path=%s, size=%d, offset=%d, fileHandle=%d, flags=%d)\n", path, (int)size, (int)offset, (int)fileInfo->fh, (int)fileInfo->flags);
	int bytesRead = pread(fileInfo->fh, buf, size, offset);
	if (bytesRead < 0)
		return -errno;
        return bytesRead; 
}

int DSFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
        printf("write(path=%s, size=%d, offset=%d, fileHandle=%d, flags=%d)\n", path, (int)size, (int)offset, (int)fileInfo->fh, (int)fileInfo->flags);
	int bytesWritten= pwrite(fileInfo->fh, buf, size, offset);
        if (bytesWritten < 0)
                return -errno;
        return bytesWritten;
}

int DSFS::Statfs(const char *path, struct statvfs *statInfo) {
        printf("statfs(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(statvfs(fullPath, statInfo));
}

int DSFS::Flush(const char *path, struct fuse_file_info *fileInfo) {
        printf("flush(path=%s)\n", path);
        //noop because we don't maintain our own buffers
        return 0;
}

int DSFS::Release(const char *path, struct fuse_file_info *fileInfo) {
        printf("release(path=%s)\n", path);
        return 0;
}

int DSFS::Fsync(const char *path, int datasync, struct fuse_file_info *fi) {
        printf("fsync(path=%s, datasync=%d\n", path, datasync);
        //sync data + file metadata
        return RETURN_ERRNO(fsync(fi->fh));
}

int DSFS::Setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
        printf("setxattr(path=%s, name=%s, value=%s, size=%d, flags=%d\n",
                path, name, value, (int)size, flags);
        /*char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(lsetxattr(fullPath, name, value, size, flags));*/
	return 0;
}

int DSFS::Getxattr(const char *path, const char *name, char *value, size_t size) {
        printf("getxattr(path=%s, name=%s, size=%d\n", path, name, (int)size);
	/*
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(getxattr(fullPath, name, value, size));
	*/
	return 0;
}

int DSFS::Listxattr(const char *path, char *list, size_t size) {
        printf("listxattr(path=%s, size=%d)\n", path, (int)size);
	/*
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(llistxattr(fullPath, list, size));
	*/
	return 0;
}

int DSFS::Removexattr(const char *path, const char *name) {
        printf("removexattry(path=%s, name=%s)\n", path, name);
	/*
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(lremovexattr(fullPath, name));
	*/
	return 0;
}

int DSFS::Opendir(const char *path, struct fuse_file_info *fileInfo) {
        printf("opendir(path=%s)\n", path);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        DIR *dir = opendir(fullPath);
        fileInfo->fh = (uint64_t)dir;
        return NULL == dir ? -errno : 0;
}

int DSFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo)
{
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
	printf("readdir(path=%s, offset=%d)\n", fullPath, (int)offset);

	DIR *dp;
	struct dirent *de;

   	(void) offset;

   	dp = opendir(fullPath);
   	if (dp == NULL)
      		return -errno;

   	while ((de = readdir(dp)) != NULL) {
      		struct stat st;
      		memset(&st, 0, sizeof(st));
      		st.st_ino = de->d_ino;
      		st.st_mode = de->d_type << 12;
      		if (filler(buf, de->d_name, &st, 0) != 0)
         		break;
   	}

   	closedir(dp);
   	return 0;
}

int DSFS::Releasedir(const char *path, struct fuse_file_info *fileInfo) {
        printf("releasedir(path=%s)\n", path);
        closedir((DIR*)fileInfo->fh);
        return 0;
}

int DSFS::Fsyncdir(const char *path, int datasync, struct fuse_file_info *fileInfo) {
        return 0;
}

int DSFS::Init(struct fuse_conn_info *conn) {
	log_msg("\ndsfs_init()\n");

	log_conn(conn);
	log_fuse_context(fuse_get_context());
        return 0;
}

int DSFS::Truncate(const char *path, off_t offset, struct fuse_file_info *fileInfo) {
        printf("truncate(path=%s, offset=%d)\n", path, (int)offset);
        char fullPath[PATH_MAX];
        AbsPath(fullPath, path);
        return RETURN_ERRNO(ftruncate(fileInfo->fh, offset));
}
