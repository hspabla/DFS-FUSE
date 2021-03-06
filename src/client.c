#include "../include/wrap.hh"

#include <fuse.h>
#include <stdio.h>

struct fuse_operations fuse_oper;

int main(int argc, char *argv[]) {
	int i=1; int fuse_stat;
	struct dsfs_state *data;

        fuse_oper.getattr = wrap_getattr;
        fuse_oper.getdir = NULL;
        fuse_oper.mknod = wrap_mknod;
        fuse_oper.mkdir = wrap_mkdir;
        fuse_oper.unlink = wrap_unlink;
        fuse_oper.rmdir = wrap_rmdir;
        fuse_oper.rename = wrap_rename;
        fuse_oper.chmod = wrap_chmod;
        fuse_oper.chown = wrap_chown;
        fuse_oper.truncate = wrap_truncate;
        fuse_oper.open = wrap_open;
        fuse_oper.read = wrap_read;
        fuse_oper.write = wrap_write;
        fuse_oper.release = wrap_release;
        fuse_oper.fsync = wrap_fsync;
        fuse_oper.setxattr = wrap_setxattr;
        fuse_oper.getxattr = wrap_getxattr;
        fuse_oper.listxattr = wrap_listxattr;
        fuse_oper.removexattr = wrap_removexattr;
        fuse_oper.readdir = wrap_readdir;
        fuse_oper.releasedir = wrap_releasedir;
        fuse_oper.init = wrap_init;
	fuse_oper.access = wrap_access;
        //fuse_oper.flush = wrap_flush;

	printf("mounting file system...: %s\n", argv[i+1]);

	set_rootdir(realpath(argv[i], NULL));

	data = malloc(sizeof(struct dsfs_state));
        data->rootdir = realpath(argv[i], NULL);
	data->mountdir = realpath(argv[i+1], NULL);
	data->logfile = log_open();

        for(; i < argc; i++) {
                argv[i] = argv[i+1];
        }
        argc--;

	fuse_stat = fuse_main(argc, argv, &fuse_oper, data);

	printf("fuse_main returned %d\n", fuse_stat);

	return fuse_stat;
}


