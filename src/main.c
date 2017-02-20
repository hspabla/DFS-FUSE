#include "../include/wrap.hh"

#include <fuse.h>
#include <stdio.h>

struct fuse_operations fuse_oper;

int main(int argc, char *argv[]) {
	int i=1; int fuse_stat;

        fuse_oper.getattr = wrap_getattr;
        fuse_oper.readlink = wrap_readlink;
        fuse_oper.getdir = NULL;
        fuse_oper.mknod = wrap_mknod;
        fuse_oper.mkdir = wrap_mkdir;
        fuse_oper.unlink = wrap_unlink;
        fuse_oper.rmdir = wrap_rmdir;
        fuse_oper.symlink = wrap_symlink;
        fuse_oper.rename = wrap_rename;
        fuse_oper.link = wrap_link;
        fuse_oper.chmod = wrap_chmod;
        fuse_oper.chown = wrap_chown;
        fuse_oper.truncate = wrap_truncate;
        fuse_oper.utime = wrap_utime;
        fuse_oper.open = wrap_open;
        fuse_oper.read = wrap_read;
        fuse_oper.write = wrap_write;
        fuse_oper.statfs = wrap_statfs;
        fuse_oper.flush = wrap_flush;
        fuse_oper.release = wrap_release;
        fuse_oper.fsync = wrap_fsync;
        fuse_oper.setxattr = wrap_setxattr;
        fuse_oper.getxattr = wrap_getxattr;
        fuse_oper.listxattr = wrap_listxattr;
        fuse_oper.removexattr = wrap_removexattr;
        fuse_oper.opendir = wrap_opendir;
        fuse_oper.readdir = wrap_readdir;
        fuse_oper.releasedir = wrap_releasedir;
        fuse_oper.fsyncdir = wrap_fsyncdir;
        fuse_oper.init = wrap_init;
	fuse_oper.access = wrap_access;

	printf("mounting file system...\n");

        set_rootdir(realpath(argv[i], NULL));
        for(; i < argc; i++) {
                argv[i] = argv[i+1];
        }
        argc--;

	fuse_stat = fuse_main(argc, argv, &fuse_oper, NULL);

	printf("fuse_main returned %d\n", fuse_stat);

	return fuse_stat;
}


