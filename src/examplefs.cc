#include "../include/examplefs.hh"

ExampleFS* ExampleFS::_instance = NULL;

#define RETURN_ERRNO(x) (x) == 0 ? 0 : -errno

ExampleFS* ExampleFS::Instance() {
	if(_instance == NULL) {
		_instance = new ExampleFS();
	}
	return _instance;
}

ExampleFS::ExampleFS() {

}

ExampleFS::~ExampleFS() {

}

int ExampleFS::Getattr(const char *path, struct stat *statbuf) {
	printf("Getting file attributes: %s\n", path);
	return RETURN_ERRNO(lstat(path, statbuf));
}

int ExampleFS::Mkdir(const char *path, mode_t mode) {
	printf("**mkdir(path=%s, mode=%d)\n", path, (int)mode);
	return RETURN_ERRNO(mkdir(path, mode));
}

int ExampleFS::Rmdir(const char *path) {
	printf("rmkdir(path=%s\n)", path);
	return RETURN_ERRNO(rmdir(path));
}

int ExampleFS::Rename(const char *path, const char *newpath) {
	printf("rename(path=%s, newPath=%s)\n", path, newpath);
	return RETURN_ERRNO(rename(path, newpath));
}

int ExampleFS::Open(const char *path, struct fuse_file_info *fileInfo) {
	printf("open(path=%s)\n", path);
	fileInfo->fh = open(path, fileInfo->flags);
	return 0;
}

int ExampleFS::Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
	printf("read(path=%s, size=%d, offset=%d)\n", path, (int)size, (int)offset);
	return RETURN_ERRNO(pread(fileInfo->fh, buf, size, offset));
}

int ExampleFS::Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo) {
	printf("write(path=%s, size=%d, offset=%d)\n", path, (int)size, (int)offset);
	return RETURN_ERRNO(pwrite(fileInfo->fh, buf, size, offset));
}

/*static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
             off_t offset, struct fuse_file_info *fi,
             enum fuse_readdir_flags flags)*/
int ExampleFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo)
{
	 DIR *dp;
	 struct dirent *de;

   	(void) offset;

   	dp = opendir(path);
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


/*int ExampleFS::Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo) {
	printf("readdir(path=%s, offset=%d)\n", path, (int)offset);
	//DIR *dir = (DIR*)fileInfo->fh;
	struct dirent *de = readdir(dir);
	if(NULL == de) {
		return -errno;
	} else {
		do {
			if(filler(buf, de->d_name, NULL, 0) != 0) {
				return -ENOMEM;
			}
		} while(NULL != (de = readdir(dir)));
	}
	return 0;
}*/


