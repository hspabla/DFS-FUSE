
#ifndef dsfs_hh
#define dsfs_hh

#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fuse.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>
#include <unistd.h>
#include <vector>
#include <unordered_map>
#include "log.hh"
#include <map>

//using namespace std;

class DSFS {
private:
	const char *_root;
	static DSFS *_instance;

	std::unordered_map<std::string, std::string> mount_map;
    void AbsPath(char dest[PATH_MAX], const char *path);

    // temp buffer we keep for files which are written but not yet fsync'ed
    // Incase we have to retransmit the data
    std::map<int, std::string> dataBuffer;

public:
	static DSFS *Instance();

	DSFS();
	~DSFS();

        void setRootDir(const char *path);

        int Getattr(const char *path, struct stat *statbuf);
        int Mknod(const char *path, mode_t mode, dev_t dev);
        int Mkdir(const char *path, mode_t mode);
        int Unlink(const char *path);
        int Rmdir(const char *path);
        int Rename(const char *path, const char *newpath);
        int Chmod(const char *path, mode_t mode);
        int Chown(const char *path, uid_t uid, gid_t gid);
        int Truncate(const char *path, off_t newSize);
	int Access(const char *path, int mask);
        int Open(const char *path, struct fuse_file_info *fileInfo);
        int Read(const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo);
        int Write(const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *fileInfo);
        int Release(const char *path, struct fuse_file_info *fileInfo);
        int Fsync(const char *path, int datasync, struct fuse_file_info *fi);
        int Setxattr(const char *path, const char *name, const char *value, size_t size, int flags);
        int Getxattr(const char *path, const char *name, char *value, size_t size);
        int Listxattr(const char *path, char *list, size_t size);
        int Removexattr(const char *path, const char *name);
        int Readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fileInfo);
        int Releasedir(const char *path, struct fuse_file_info *fileInfo);
        int Init(struct fuse_conn_info *conn);
	//int Flush(const char *path, struct fuse_file_info *fileInfo);
};



#endif //dsfs_hh
