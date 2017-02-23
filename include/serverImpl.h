#include <iostream>
#include <memory>
#include <string>
#include <ctype.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/xattr.h>
#include <unistd.h>
#include <map>

#include <grpc++/grpc++.h>
#include "../lib/fileserver.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using namespace dfsFuse;

class FileSystemImpl final : public FileSystem::Service {
private:
    std::map<int, std::string> serverDataBuf;
public:
    Status GetAttr( ServerContext* context, const GetAttrRequest* request,
                    GetAttrResponse* reply ) override;

    Status Mkdir( ServerContext* context, const MkdirRequest* request,
      			MkdirResponse* reply ) override;

    Status Opendir( ServerContext* context, const OpenDirRequest* request,
      			  OpenDirResponse* reply ) override;

    Status Mknod( ServerContext* context, const MknodRequest* request,
      			MknodResponse* reply ) override;

    Status Open( ServerContext* context, const OpenRequest* request,
                 OpenResponse* reply ) override;

    Status Read( ServerContext* context, const ReadRequest* request,
                 ReadResponse* reply ) override;

    Status Write( ServerContext* context, const WriteRequest* request,
                  WriteResponse* reply ) override;

    Status Unlink( ServerContext* context, const UnlinkRequest* request,
                  UnlinkResponse* reply ) override;

    Status Rmdir( ServerContext* context, const RmdirRequest* request,
                  RmdirResponse* reply ) override;

    Status Rename( ServerContext* context, const RenameRequest* request,
                  RenameResponse* reply ) override;

    Status Release( ServerContext* context, const ReleaseRequest* request,
                  ReleaseResponse* reply ) override;
    Status Chmod( ServerContext* context, const ChmodRequest* request,
                  ChmodResponse* reply ) override;

    Status Chown( ServerContext* context, const ChownRequest* request,
                  ChownResponse* reply ) override;

    Status Releasedir( ServerContext* context, const ReleasedirRequest* request,
                  ReleasedirResponse* reply ) override;

    Status Access( ServerContext* context, const AccessRequest* request,
                   AccessResponse* reply ) override;

    Status Truncate( ServerContext* context, const TruncateRequest* request,
                     TruncateResponse* reply ) override;

    Status Fsync( ServerContext* context, const FsyncRequest* request,
                     FsyncResponse* reply ) override;
};
