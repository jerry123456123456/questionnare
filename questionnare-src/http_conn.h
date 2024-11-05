#ifndef __HTTP_CONN_H__
#define __HTTP_CONN_H__

//http_conn.h文件是一个 C++ 头文件，它定义了一个名为CHttpConn的类，用于处理 HTTP 连接相关的功能，以及一些相关的常量、结构体和函数声明

#include "base/util_pdu.h"
#include"http_parser_wrapper.h"
#include"netlib.h"
#include"tc_thread_pool.h"
#include"util.h"
#include<list>
#include<mutex>
#define HTTP_CONN_TIMEOUT 60000

#define READ_BUF_SIZE 2048

#define HTTP_RESPONSE_HTML                                                     \
    "HTTP/1.1 200 OK\r\n"                                                      \
    "Connection:close\r\n"                                                     \
    "Content-Length:%d\r\n"                                                    \
    "Content-Type:application/json;charset=utf-8\r\n\r\n%s"
#define HTTP_RESPONSE_HTML_MAX 4096
extern ThreadPool g_thread_pool;
//定义了一个枚举类型，用于表示 HTTP 连接的不同状态
enum{
    CONN_STATE_IDLE,
    CONN_STATE_CONNECTED,
    CONN_STATE_OPEN,
    CONN_STATE_CLOSED,
};

//定义了一个名为ResponsePdu_t的结构体，用于封装要回发给客户端的数据
typedef struct{
    uint32_t conn_uuid; //用于查找connection
    std::string resp_data;  //要回发的数据
}ResponsePdu_t;

class CHttpConn : public CRefObject{
public:
    CHttpConn();
    virtual ~CHttpConn();

    uint32_t GetConnHandle(){return conn_handle_;}
    char *GetPeerIP(){return (char *)peer_ip_.c_str();}

    int Send(void *data,int len);

    void Close();
    void OnConnect(net_handle_t handle);
    void OnRead();
    void OnWrite();
    void OnClose();
    void OnTimer(uint64_t curr_tick);
    void OnWriteComlete();

    static void AddResponseData(uint32_t conn_uuid,
                                string &resp_data); // 工作线程调用
    static void SendResponseDataList();             // 主线程调用 

private:
    // 账号注册处理
    int _HandleRegisterRequest(string &url, string &post_data);
    // 账号登陆处理
    int _HandleLoginRequest(string &url, string &post_data);
    // 用户加载表格
    int _HandleMytablesRequest(string &url, string &post_data);
    //处理文件
    int _HandleUploadTableRequest(string &url, string &post_data);


protected:
    net_handle_t m_sock_handle;
    uint32_t conn_handle_;
    bool busy_;

    uint32_t state_;
    std::string peer_ip_;
    uint16_t peer_port_;
    CSimpleBuffer in_buf_;
    CSimpleBuffer out_buf_;

    uint64_t last_send_tick_;
    uint64_t last_recv_tick_;

    CHttpParserWrapper http_parser_;

    static uint32_t s_uuid_alloctor;  //uuid分配
    uint32_t uuid_;

    static std::mutex s_resp_mutex;
    static std::list<ResponsePdu_t *> s_response_pdu_list; // 主线程发送回复消息
};

typedef hash_map<uint32_t,CHttpConn *>HttpConnMap_t;

//FindHttpConnByHandle函数根据连接句柄查找对应的CHttpConn对象
CHttpConn *FindHttpConnByHandle(uint32_t handle);
void InitHttpConn();
// CHttpConn *GetHttpConnByUuid(uint32_t uuid); /函数根据连接的唯一标识符（UUID）获取对应的CHttpConn对象

#endif