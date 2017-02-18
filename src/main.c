#include "../include/wrap.hh"

#include <fuse.h>
#include <stdio.h>

struct fuse_operations examplefs_oper;

int main(int argc, char *argv[]) {
	int i=1; int fuse_stat;

        examplefs_oper.getattr = wrap_getattr;
        examplefs_oper.mkdir = wrap_mkdir;
        examplefs_oper.rmdir = wrap_rmdir;
        examplefs_oper.rename = wrap_rename;
        examplefs_oper.open = wrap_open;
        examplefs_oper.read = wrap_read;
        examplefs_oper.write = wrap_write;
        examplefs_oper.readdir = wrap_readdir;

	printf("mounting file system...\n");
	

	//realpath(...) returns the canonicalized absolute pathname
	printf("%s\n", argv[i]);

	fuse_stat = fuse_main(argc, argv, &examplefs_oper, NULL);

	printf("fuse_main returned %d\n", fuse_stat);

	return fuse_stat;
}


