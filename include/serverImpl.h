#include <iostream>
#include <memory>
#include <string>

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

class FileSystemImpl final : public FileSystem::Service {
 public:
  Status GetAttr( ServerContext* context, const struct GetAttrRequest* request,
                  struct GetAttrResponse* reply ) override;

  Status Mkdir( ServerContext* context, const struct MkdirRequest* request,
				struct MkdirResponse* reply ) override;

  Status Opendir( ServerContext* context, const struct OpenDirRequest* request,
				struct OpenDirResponse* reply ) override;

};
