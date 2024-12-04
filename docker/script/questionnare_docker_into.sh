#!/usr/bin/env bash

# 获取当前脚本所在目录的上一级目录的绝对路径（假设脚本放置在合适的位置，可根据实际调整路径获取逻辑）
MONITOR_HOME_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/../../" && pwd)"

# 获取当前主机名
local_host="$(hostname)"
# 获取当前登录用户名
user="${USER}"
# 获取当前用户的用户 ID
uid="$(id -u)"
# 获取当前用户所属主组的组名
group="$(id -g -n)"
# 获取当前用户所属主组的组 ID
gid="$(id -g)"

# 执行 docker exec 命令进入名为 questionnare 的运行中的容器（确保容器已启动且名称正确）
# 以 root 用户身份、交互式且带有伪终端的方式进入容器，并设置语言环境为 C.UTF-8，然后启动 bash 命令行解释器
docker exec \
    -u root \
    -it questionnare \
    env LANG=C.UTF-8 \
    /bin/bash