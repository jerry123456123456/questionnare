//g++ -std=c++11 -o greeter_server greeter_server.cc greeter.pb.cc greeter.grpc.pb.cc -lgrpc++ -lprotobuf -lpthread


#include <grpcpp/grpcpp.h>
#include "greeter.grpc.pb.h"

class GreeterServiceImpl final : public greeter::Greeter::Service {
public:
    grpc::Status SayHello(grpc::ServerContext* context,const greeter::HelloRequest* request,greeter::HelloReply* reply)override{
        //根据表中的名字生成问候消息
        std::string name = request->name();
        reply->set_message("Hello," + name);
        return grpc::Status::OK;
    }
};

int main(){
    std::string server_address("0.0.0.0:50051");

    GreeterServiceImpl service;

    grpc::ServerBuilder builder;
    builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;

    server->Wait();
    return 0;
}