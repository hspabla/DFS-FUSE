#include "../include/wrap.hh"
#include "../include/dsfs.hh"

void set_rootdir(const char *path) {
        DSFS::Instance()->setRootDir(path);
}

int wrap_getattr(const char *path, struct stat *statbuf) {
	return DSFS::Instance()->Getattr(path, statbuf);
}

int wrap_mknod(const char *path, mode_t mode, dev_t dev) {
        return DSFS::Instance()->Mknod(path, mode, dev);
}

int wrap_mkdir(const char *path, mode_t mode) {
	return DSFS::Instance()->Mkdir(path, mode);
}
int wrap_unlink(const char *path) {
        return DSFS::Instance()->Unlink(path);
}
int wrap_rmdir(const char *path) {
	return DSFS::Instance()->Rmdir(path);
}
int wrap_rename(const char *path, const char *newpath) {
	return DSFS::Instance()->Rename(path, newpath);
}
int wrap_chmod(const char *path, mode_t mode) {
        return DSFS::Instance()->Chmod(path, mode);
}
int wrap_chown(const char *path, uid_t uid, gid_t gid) {
        return DSFS::Instance()->Chown(path, uid, gid);
}
int wrap_truncate(const char *path, off_t newSize) {
        return DSFS::Instance()->Truncate(path, newSize);
}
int wrap_access(const char *path, int mask) {
        return DSFS::Instance()->Access(path, mask);
}
int wrap_open(const char *path, struct fuse_file_info *fileInfo) {
	return DSFS::Instance()->Open(path, fileInfo);
}
int wrap_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
	return DSFS::Instance()->Read(path, buf, size, offset, fileInfo);
}
int wrap_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
	return DSFS::Instance()->Write(path, buf, size, offset, fileInfo);
}
int wrap_release(const char *path, struct fuse_file_info *fileInfo) {
        return DSFS::Instance()->Release(path, fileInfo);
}
int wrap_fsync(const char *path, int datasync, struct fuse_file_info *fi) {
        return DSFS::Instance()->Fsync(path, datasync, fi);
}
int wrap_setxattr(const char *path, const char *name, const char *value, size_t size, int flags) {
        return DSFS::Instance()->Setxattr(path, name, value, size, flags);
}
int wrap_getxattr(const char *path, const char *name, char *value, size_t size) {
        return DSFS::Instance()->Getxattr(path, name, value, size);
}
int wrap_listxattr(const char *path, char *list, size_t size) {
        return DSFS::Instance()->Listxattr(path, list, size);
}
int wrap_removexattr(const char *path, const char *name) {
        return DSFS::Instance()->Removexattr(path, name);
}
int wrap_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) {
	return DSFS::Instance()->Readdir(path, buf, filler, offset, fileInfo);
}
int wrap_releasedir(const char *path, struct fuse_file_info *fileInfo) {
        return DSFS::Instance()->Releasedir(path, fileInfo);
}
int wrap_init(struct fuse_conn_info *conn) {
        return DSFS::Instance()->Init(conn);
}
/*int wrap_flush(const char *path, struct fuse_file_info *fileInfo) {
        return DSFS::Instance()->Flush(path, fileInfo);
}*/
