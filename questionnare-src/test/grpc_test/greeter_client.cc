//g++ -std=c++11 -o greeter_client greeter_client.cc greeter.pb.cc greeter.grpc.pb.cc -lgrpc++ -lprotobuf -lpthread


#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"

int main(){
    std::string server_address("localhost:50051");


    //创建与服务器的连接
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(server_address,grpc::InsecureChannelCredentials());
    std::unique_ptr<greeter::Greeter::Stub> stub = greeter::Greeter::NewStub(channel);

    //创建请求对象
    greeter::HelloRequest request;
    request.set_name("World");

    //创建响应对象
    greeter::HelloReply reply;

    //创建客户端上下文
    grpc::ClientContext context;

    //调用SayHello方法
    grpc::Status status = stub->SayHello(&context,request,&reply);

    if (status.ok()) {
        std::cout << "Server responded: " << reply.message() << std::endl;
    } else {
        std::cout << "RPC failed: " << status.error_message() << std::endl;
    }

    return 0;
}