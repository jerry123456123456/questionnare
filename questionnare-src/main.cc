#include<iostream>
#include"config_file_reader.h"
#include"db_pool.h"
#include"dlog.h"

int main(int argc,char *argv[]){
    // 默认情况下，往一个读端关闭的管道或socket连接中写数据将引发SIGPIPE信号。我们需要在代码中捕获并处理该信号，
    // 或者至少忽略它，因为程序接收到SIGPIPE信号的默认行为是结束进程，而我们绝对不希望因为错误的写操作而导致程序退出。
    // SIG_IGN 忽略信号的处理程序
    signal(SIGPIPE,SIG_IGN);

    //获取配置文件路径
    char *str_qs_http_server_conf = NULL;
    if(argc > 1){
        str_qs_http_server_conf = argv[1];
    }else{
        str_qs_http_server_conf = (char *)"qs_http_server.conf";
    }
    printf("conf file path: %s\n", str_qs_http_server_conf);

    //解析配置文件,修改源文件中类中不存在的默认构造函数
    CConfigFileReader config_file(str_qs_http_server_conf);
    if(config_file.ParseConf(str_tc_http_server_conf) != 0) {
        std::cout << str_tc_http_server_conf << " no exist, please check conf file\n";
        return -1;
    }

    //读取配置文件中的字段
    char *log_level = config_file.GetConfigName("log_level");
    if (!log_level) {
        LogError("config item missing, exit... log_level:{}", log_level);
        return -1;
    }
    DLog::SetLevel(log_level);   //设置日志打印级别

    //设置线程数量
    char *str_thread_num = config_file.GetConfigName("ThreadNum");  //线程池数量，目前是epoll + 线程池方式
    uint32_t thread_num = atoi(str_thread_num);

    //http监听的地址和端口
    char *http_listen_ip = config_file.GetConfigName("HttpListenIp");
    char *str_http_port = config_file.GetConfigName("HttpPort");
    if (!http_listen_ip || !str_http_port) {
        LogError("config item missing, exit... ip:{}, port:{}", http_listen_ip, str_http_port);
        return -1;
    }
    uint16_t http_port = atoi(str_http_port);
    LogInfo("main into"); //单例模式 日志库 spdlog

    //初始化mysql连接池
    CDBManager::SetConfPath(str_qs_http_server_conf);   //设置配置文件路径
    //里面调用了Init()
    CDBManager *db_manager = CDBManager::getInstance();
    if (!db_manager) {
        LogError("DBManager init failed");
        return -1;
    }
    
    //将配置文件的参数传递给对应的模块


    //检测监听ip端口

    

    return 0;
}
