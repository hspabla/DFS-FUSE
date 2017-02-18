#include "../include/wrap.hh"
#include "../include/examplefs.hh"

int wrap_getattr(const char *path, struct stat *statbuf) {
	return ExampleFS::Instance()->Getattr(path, statbuf);
}

int wrap_mkdir(const char *path, mode_t mode) {
	return ExampleFS::Instance()->Mkdir(path, mode);
}
int wrap_rmdir(const char *path) {
	return ExampleFS::Instance()->Rmdir(path);
}
int wrap_rename(const char *path, const char *newpath) {
	return ExampleFS::Instance()->Rename(path, newpath);
}
int wrap_open(const char *path, struct fuse_file_info *fileInfo) {
	return ExampleFS::Instance()->Open(path, fileInfo);
}
int wrap_read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
	return ExampleFS::Instance()->Read(path, buf, size, offset, fileInfo);
}
int wrap_write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
	return ExampleFS::Instance()->Write(path, buf, size, offset, fileInfo);
}
int wrap_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) {
	return ExampleFS::Instance()->Readdir(path, buf, filler, offset, fileInfo);
}

