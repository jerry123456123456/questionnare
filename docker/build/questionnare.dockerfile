#root@iZ2zeedb5cjeupm8akol1cZ:/home/jerry/Desktop/questionnare/docker/build# docker build --network host -t question:questionnare -f questionnare.dockerfile .

# 使用基于 Ubuntu 的基础镜像（你可以根据实际需求更换合适的基础镜像，比如 CentOS 等）
FROM ubuntu:latest

# 设置环境变量，确保apt-get操作以非交互方式执行，避免构建过程中的交互提示
ENV DEBIAN_FRONTEND=noninteractive

#清理软件包缓存   和清理已经过时的，针对那些过期的文件
RUN apt-get clean && \
    apt-get autoclean

# 更新软件包列表并安装常用工具以及编译、调试等相关软件包
RUN apt update && \
    apt install -y \
    vim \
    htop \
    apt-utils \
    curl \
    cmake \
    net-tools \
    gdb gcc g++ \
    libgoogle-glog-dev

# 安装项目所需的其他依赖库（例如 hiredis、mysql 相关等，这里假设通过 apt 包管理工具能获取到对应的安装包，如果不行，可能需要额外添加软件源或者手动安装等操作）
RUN apt install -y \
    libhiredis-dev \
    libmysqlclient-dev \
    libprotobuf-dev \
    protobuf-compiler \
    libfmt-dev \
    libspdlog-dev

# 设置工作目录为容器内的 /questionnare 目录，后续命令将基于此目录执行
WORKDIR /questionnare-src
