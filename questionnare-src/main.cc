#include"api_common.h"
#include"api_deal_table.h"
#include"api_login.h"
#include"api_register.h"
#include"api_mytables.h"
#include "config_file_reader.h"
#include "http_conn.h"
#include "netlib.h"
#include "util.h"
#include "dlog.h"

void http_callback(void *callback_data, uint8_t msg, uint32_t handle,
                   void *pParam) {
    UNUSED(callback_data);
    UNUSED(pParam);
    if (msg == NETLIB_MSG_CONNECT) {
        // 这里是不是觉得很奇怪,为什么new了对象却没有释放?
        // 实际上对象在被Close时使用delete this的方式释放自己
        CHttpConn *pConn = new CHttpConn();
        pConn->OnConnect(handle);
    } else {
        LogError("!!!error msg:{}", msg);
    }
}

void http_loop_callback(void *callback_data, uint8_t msg, uint32_t handle,
                        void *pParam) {
    UNUSED(callback_data);
    UNUSED(msg);
    UNUSED(handle);
    UNUSED(pParam);
    CHttpConn::SendResponseDataList(); // 静态函数, 将要发送的数据循环发给客户端
}

int initHttpConn(uint32_t thread_num) {
    g_thread_pool.Init(thread_num); // 初始化线程数量
    g_thread_pool.Start();          // 启动多线程
    netlib_add_loop(http_loop_callback,NULL); // http_loop_callback被epoll所在线程循环调用
    return 0;
}

int main(int argc,char *argv[]){
    // 默认情况下，往一个读端关闭的管道或socket连接中写数据将引发SIGPIPE信号。我们需要在代码中捕获并处理该信号，
    // 或者至少忽略它，因为程序接收到SIGPIPE信号的默认行为是结束进程，而我们绝对不希望因为错误的写操作而导致程序退出。
    // SIG_IGN 忽略信号的处理程序
    signal(SIGPIPE,SIG_IGN);
    int ret = 0;
    //获取配置文件路径
    char *str_qs_http_server_conf = NULL;
    if(argc > 1){
        str_qs_http_server_conf = argv[1];
    }else{
        str_qs_http_server_conf = (char *)"/home/jerry/Desktop/questionnare/questionnare-src/qs_http_server.conf";
    }
    printf("conf file path: %s\n", str_qs_http_server_conf);

    //解析配置文件,修改源文件中类中不存在的默认构造函数
    CConfigFileReader config_file(str_qs_http_server_conf);
    char *log_level = config_file.GetConfigName("log_level");   //读取日志设置级别
    DLog::SetLevel(log_level);   //设置日志打印级别

    char *http_listen_ip = config_file.GetConfigName("HttpListenIP");
    printf("%s\n",http_listen_ip);
    char *str_http_port = config_file.GetConfigName("HttpPort");        //8081 -- nginx.conf,当前服务的端口

    char *str_thread_num = config_file.GetConfigName("ThreadNum");  //线程池数量，目前是epoll + 线程池方式
    uint32_t thread_num = atoi(str_thread_num);

    LogInfo("main into"); //单例模式 日志库 spdlog

    // 初始化mysql、redis连接池，内部也会读取读取配置文件tc_http_server.conf
    CacheManager::SetConfPath(str_qs_http_server_conf); //设置配置文件路径
    CacheManager *cache_manager = CacheManager::getInstance();
    if (!cache_manager) {
        LogError("CacheManager init failed");
        return -1;
    }

    CDBManager::SetConfPath(str_qs_http_server_conf);   //设置配置文件路径
    CDBManager *db_manager = CDBManager::getInstance();
    if (!db_manager) {
        LogError("DBManager init failed");
        return -1;
    }
    
    // 检测监听ip和端口
    if (!http_listen_ip || !str_http_port) {
        LogError("config item missing, exit... ip:{}, port:{}", http_listen_ip,
               str_http_port);
        return -1;
    }
    //reactor网络模型 1epoll+ 线程池
    ret = netlib_init();
    if (ret == NETLIB_ERROR) {
        LogError("netlib_init failed");
        return ret;
    }

    uint16_t http_port = atoi(str_http_port);
    CStrExplode http_listen_ip_list(http_listen_ip, ';');
    for (uint32_t i = 0; i < http_listen_ip_list.GetItemCnt(); i++) {
        ret = netlib_listen(http_listen_ip_list.GetItem(i), http_port,
                            http_callback, NULL);
        if (ret == NETLIB_ERROR)
            return ret;
    }
    initHttpConn(thread_num);

    LogInfo("server start listen on:For http://{}:{}", http_listen_ip, http_port);

    LogInfo("now enter the event loop...");

    WritePid();
    
    // 超时参数影响回发客户端的时间
    netlib_eventloop(1);

    return 0;
}
