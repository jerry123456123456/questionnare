cmake_minimum_required(VERSION 3.10)
project(GreeterClient)

#判断编译器类型,如果是gcc编译器,则在编译选项中加入c++14支持
if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
    message(STATUS "optional:-std=c++14")   
endif(CMAKE_COMPILER_IS_GNUCXX)

add_compile_options(-w)

ADD_DEFINITIONS(-g -Wno-deprecated -Wno-unused-parameter -Bsymbolic -D_REENTRANT -D_FILE_OFFSET_BITS=64
-DAC_HAS_INFO -DAC_HAS_WARNING -DAC_HAS_ERROR -DAC_HAS_CRITICAL -DTIXML_USE_STL
-DAC_HAS_DEBUG -DLINUX_DAEMON)

# 添加库文件路径，部分Linux版本不自动加载/usr/local/lib
LINK_DIRECTORIES(/usr/local/lib)
include_directories(/usr/local/include)  # 根据你的安装路径调整

# 找到gRPC和Protobuf的安装位置
find_package(Protobuf REQUIRED)
find_package(gRPC CONFIG REQUIRED)

#sudo apt-get install -y protobuf-compiler libprotobuf-dev

# 添加源文件
add_executable(greeter_client greeter_client.cc greeter.pb.cc greeter.grpc.pb.cc)
add_executable(greeter_server greeter_server.cc greeter.pb.cc greeter.grpc.pb.cc)

# 链接gRPC和Protobuf库
target_link_libraries(greeter_client
    gRPC::grpc++
    protobuf::libprotobuf
    pthread
    dl
    ssl
    crypto
)

target_link_libraries(greeter_server
    gRPC::grpc++
    protobuf::libprotobuf
    pthread
    dl
    ssl
    crypto
)
