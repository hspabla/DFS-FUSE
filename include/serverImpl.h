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
using dfsFuse::OpenRequest;
using dfsFuse::OpenResponse;
using dfsFuse::ReadRequest;
using dfsFuse::ReadResponse;
using dfsFuse::WriteRequest;
using dfsFuse::WriteResponse;



class FileSystemImpl final : public FileSystem::Service {
 public:
  Status GetAttr( ServerContext* context, const GetAttrRequest* request,
                  GetAttrResponse* reply ) override;

  Status Mkdir( ServerContext* context, const MkdirRequest* request,
				MkdirResponse* reply ) override;

  Status Opendir( ServerContext* context, const OpenDirRequest* request,
				  OpenDirResponse* reply ) override;

  Status Open( ServerContext* context, const OpenRequest* request,
               OpenResponse* reply ) override;

  Status Read( ServerContext* context, const ReadRequest* request,
               ReadResponse* reply ) override;

  Status Write( ServerContext* context, const WriteRequest* request,
                WriteResponse* reply ) override;

};
