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

#include <grpc++/grpc++.h>
#include "../lib/fileserver.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;

using dfsFuse::FileSystem;
using dfsFuse::FSstatus;
using dfsFuse::Owner;
using dfsFuse::ClientInfo;
using dfsFuse::Attr;
using dfsFuse::GetAttrRequest;
using dfsFuse::GetAttrResponse;
using dfsFuse::MkdirRequest;
using dfsFuse::MkdirResponse;
using dfsFuse::OpenDirRequest;
using dfsFuse::DirEntry;
using dfsFuse::OpenDirResponse;
using dfsFuse::MknodRequest;
using dfsFuse::MknodResponse;
using dfsFuse::OpenRequest;
using dfsFuse::OpenResponse;
using dfsFuse::ReadRequest;
using dfsFuse::ReadResponse;
using dfsFuse::WriteRequest;
using dfsFuse::WriteResponse;
using dfsFuse::UnlinkRequest;
using dfsFuse::UnlinkResponse;
using dfsFuse::RmdirRequest;
using dfsFuse::RmdirResponse;
using dfsFuse::RenameRequest;
using dfsFuse::RenameResponse;
using dfsFuse::ReleaseRequest;
using dfsFuse::ReleaseResponse;
using dfsFuse::ChmodRequest;
using dfsFuse::ChmodResponse;
using dfsFuse::ChownRequest;
using dfsFuse::ChownResponse;
using dfsFuse::ReleasedirRequest;
using dfsFuse::ReleasedirResponse;
using dfsFuse::AccessRequest;
using dfsFuse::AccessResponse;
using dfsFuse::TruncateRequest;
using dfsFuse::TruncateResponse;


class FileSystemImpl final : public FileSystem::Service {
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
};
