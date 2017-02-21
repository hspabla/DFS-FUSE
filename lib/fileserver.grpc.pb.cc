// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: fileserver.proto

#include "fileserver.pb.h"
#include "fileserver.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace dfsFuse {

static const char* FileSystem_method_names[] = {
  "/dfsFuse.FileSystem/GetAttr",
  "/dfsFuse.FileSystem/Mkdir",
  "/dfsFuse.FileSystem/Opendir",
  "/dfsFuse.FileSystem/Open",
  "/dfsFuse.FileSystem/Create",
};

std::unique_ptr< FileSystem::Stub> FileSystem::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< FileSystem::Stub> stub(new FileSystem::Stub(channel));
  return stub;
}

FileSystem::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_GetAttr_(FileSystem_method_names[0], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Mkdir_(FileSystem_method_names[1], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Opendir_(FileSystem_method_names[2], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Open_(FileSystem_method_names[3], ::grpc::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Create_(FileSystem_method_names[4], ::grpc::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status FileSystem::Stub::GetAttr(::grpc::ClientContext* context, const ::dfsFuse::GetAttrRequest& request, ::dfsFuse::GetAttrResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_GetAttr_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::dfsFuse::GetAttrResponse>* FileSystem::Stub::AsyncGetAttrRaw(::grpc::ClientContext* context, const ::dfsFuse::GetAttrRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::dfsFuse::GetAttrResponse>(channel_.get(), cq, rpcmethod_GetAttr_, context, request);
}

::grpc::Status FileSystem::Stub::Mkdir(::grpc::ClientContext* context, const ::dfsFuse::MkdirRequest& request, ::dfsFuse::MkdirResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Mkdir_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::dfsFuse::MkdirResponse>* FileSystem::Stub::AsyncMkdirRaw(::grpc::ClientContext* context, const ::dfsFuse::MkdirRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::dfsFuse::MkdirResponse>(channel_.get(), cq, rpcmethod_Mkdir_, context, request);
}

::grpc::Status FileSystem::Stub::Opendir(::grpc::ClientContext* context, const ::dfsFuse::OpenDirRequest& request, ::dfsFuse::OpenDirResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Opendir_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::dfsFuse::OpenDirResponse>* FileSystem::Stub::AsyncOpendirRaw(::grpc::ClientContext* context, const ::dfsFuse::OpenDirRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::dfsFuse::OpenDirResponse>(channel_.get(), cq, rpcmethod_Opendir_, context, request);
}

::grpc::Status FileSystem::Stub::Open(::grpc::ClientContext* context, const ::dfsFuse::OpenRequest& request, ::dfsFuse::OpenResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Open_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::dfsFuse::OpenResponse>* FileSystem::Stub::AsyncOpenRaw(::grpc::ClientContext* context, const ::dfsFuse::OpenRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::dfsFuse::OpenResponse>(channel_.get(), cq, rpcmethod_Open_, context, request);
}

::grpc::Status FileSystem::Stub::Create(::grpc::ClientContext* context, const ::dfsFuse::CreateRequest& request, ::dfsFuse::CreateResponse* response) {
  return ::grpc::BlockingUnaryCall(channel_.get(), rpcmethod_Create_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::dfsFuse::CreateResponse>* FileSystem::Stub::AsyncCreateRaw(::grpc::ClientContext* context, const ::dfsFuse::CreateRequest& request, ::grpc::CompletionQueue* cq) {
  return new ::grpc::ClientAsyncResponseReader< ::dfsFuse::CreateResponse>(channel_.get(), cq, rpcmethod_Create_, context, request);
}

FileSystem::Service::Service() {
  (void)FileSystem_method_names;
  AddMethod(new ::grpc::RpcServiceMethod(
      FileSystem_method_names[0],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< FileSystem::Service, ::dfsFuse::GetAttrRequest, ::dfsFuse::GetAttrResponse>(
          std::mem_fn(&FileSystem::Service::GetAttr), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      FileSystem_method_names[1],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< FileSystem::Service, ::dfsFuse::MkdirRequest, ::dfsFuse::MkdirResponse>(
          std::mem_fn(&FileSystem::Service::Mkdir), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      FileSystem_method_names[2],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< FileSystem::Service, ::dfsFuse::OpenDirRequest, ::dfsFuse::OpenDirResponse>(
          std::mem_fn(&FileSystem::Service::Opendir), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      FileSystem_method_names[3],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< FileSystem::Service, ::dfsFuse::OpenRequest, ::dfsFuse::OpenResponse>(
          std::mem_fn(&FileSystem::Service::Open), this)));
  AddMethod(new ::grpc::RpcServiceMethod(
      FileSystem_method_names[4],
      ::grpc::RpcMethod::NORMAL_RPC,
      new ::grpc::RpcMethodHandler< FileSystem::Service, ::dfsFuse::CreateRequest, ::dfsFuse::CreateResponse>(
          std::mem_fn(&FileSystem::Service::Create), this)));
}

FileSystem::Service::~Service() {
}

::grpc::Status FileSystem::Service::GetAttr(::grpc::ServerContext* context, const ::dfsFuse::GetAttrRequest* request, ::dfsFuse::GetAttrResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileSystem::Service::Mkdir(::grpc::ServerContext* context, const ::dfsFuse::MkdirRequest* request, ::dfsFuse::MkdirResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileSystem::Service::Opendir(::grpc::ServerContext* context, const ::dfsFuse::OpenDirRequest* request, ::dfsFuse::OpenDirResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileSystem::Service::Open(::grpc::ServerContext* context, const ::dfsFuse::OpenRequest* request, ::dfsFuse::OpenResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status FileSystem::Service::Create(::grpc::ServerContext* context, const ::dfsFuse::CreateRequest* request, ::dfsFuse::CreateResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace dfsFuse

