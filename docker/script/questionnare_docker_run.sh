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

# 输出提示信息，表示开始启动 Docker 容器
echo "start docker"

# 启动 Docker 容器，以下是各选项的详细解释
docker run -it -d \
    --privileged=true \
    --name questionnare \
    -e DOCKER_USER="${user}" \
    -e USER="${user}" \
    -e DOCKER_USER_ID="${uid}" \
    -e DOCKER_GRP="${group}" \
    -e DOCKER_GRP_ID="${gid}" \
    -v ${MONITOR_HOME_DIR}:/questionnare \
    -v ${XDG_RUNTIME_DIR}:${XDG_RUNTIME_DIR} \
    -v /tmp:/tmp \
    --network host \
    questionnare:latest