#include "api_unreg.h"
#include "api_register.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api_common.h"
#include "http_conn.h"
#include <sys/time.h>
#include <time.h>

/*
{
    "user":xxx,
    "token":xxx,
}
*/
int decodeRegisterJson1(const std::string &str_json,string &user_name,string &token){
    bool res;
    Json::Value root;
    Json::Reader jsonReader; //用来解析json格式的字符串
    //提供parse方法按规则解析
    res = jsonReader.parse(str_json,root);
    if (!res) {
        LogError("parse reg json failed ");
        return -1;
    }

    //用户名
    if(root["user"].isNull()){
        LogError("user null\n");
        return -1;
    }
    user_name = root["user"].asString();

    //密码
    if (root["token"].isNull()) {
        LogError("token null\n");
        return -1;
    }
    token = root["token"].asString();

    return 0;
}

//封装注册用户的json,比如用户注册之后，如果成功，返回值是0，否则是1
int encodeRegisterJson1(int ret ,string &str_json){
    Json::Value root;
    root["code"] = ret;
    Json::FastWriter writer;
    str_json = writer.write(root);
    return 0;
}

template <typename... Args>
std::string formatString2(const std::string &format, Args... args) {
    auto size = std::snprintf(nullptr, 0, format.c_str(), args...) +
                1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(),
                       buf.get() + size - 1); // We don't want the '\0' inside
}

int unregisterUser(string &user_name,string &token){
    int ret = 0;
    uint32_t user_id;
    CDBManager *db_manager = CDBManager::getInstance();
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");
    AUTO_REL_DBCONN(db_manager, db_conn);

    string str_sql;
    // 查询用户是否已存在的SQL语句
    printf("%s\n",user_name.c_str());
    str_sql = formatString2("select user_id from Users where user_name='%s'", user_name.c_str());
    CResultSet *result_set = db_conn->ExecuteQuery(str_sql.c_str());

    if(result_set && result_set->Next()){  //存在，准备删除
        // 如果用户不存在，则进行注册
        int user_id = result_set->GetInt("user_id");
        str_sql = "delete from Users where user_id = ?";
        LogInfo("执行: {}", str_sql);

        // 必须在释放连接前delete
        // CPrepareStatement对象，否则有可能多个线程操作mysql对象，会crash
        CPrepareStatement *stmt = new CPrepareStatement();
        if(stmt->Init(db_conn->GetMysql(),str_sql)){
            uint32_t index = 0;
            stmt->SetParam(index++,user_id);
            bool bRet = stmt->ExecuteUpdate();
            if (bRet) {
                ret = 0;
            } else {
                LogError("delete user_info failed. {}", str_sql);
                ret = 1;
            }
        }
        delete stmt;
    }else{  //不存在
        delete result_set;
        ret = 2;
    }
    return ret;
}

#define HTTP_RESPONSE_HTML                                                     \
    "HTTP/1.1 200 OK\r\n"                                                      \
    "Connection:close\r\n"                                                     \
    "Content-Length:%d\r\n"                                                    \
    "Content-Type:application/json;charset=utf-8\r\n\r\n%s"

int ApiunRegisterUser(string &url, string &post_data, string &str_json){
    UNUSED(url);
    int ret = 0;
    string user_name;
    string pwd;

    // 判断数据是否为空
    if (post_data.empty()) {
        LogError("decodeRegisterJson failed");
        ret = -1;
        goto END;
    }
    // 解析json
    if (decodeRegisterJson1(post_data, user_name,pwd) <
        0) {
        LogError("decodeRegisterJson failed");
        ret = -1;
        goto END;
    }

    //注册账号
    ret = unregisterUser(user_name,pwd);

//!!!!!!!!!!!!!!!!!!!!!!!!!标签只是一个位置，正常顺序执行过来的代码也会执行下面的逻辑
END:
    Json::Value value;
    value["code"] = (ret == 0)? 0 : -1;
    str_json = value.toStyledString();

    return ret;
}



