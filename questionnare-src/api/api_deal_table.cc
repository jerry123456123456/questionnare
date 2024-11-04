#include "api_dealtable.h"
#include "api_common.h"
#include "redis_keys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

int decodeDealTableJson(string &str_json,string &user_name,string &token,string &tablename){
    bool res;
    Json::Value root;
    Json::Reader jsonReader;
    res = jsonReader.parse(str_json, root);
    if (!res) {
        LogError("parse reg json failed ");
        return -1;
    }

    if (root["user"].isNull()) {
        LogError("user null");
        return -1;
    }
    user_name = root["user"].asString();

    if (root["token"].isNull()) {
        LogError("token null");
        return -1;
    }
    token = root["token"].asString();

    if (root["tablename"].isNull()) {
        LogError("tablename null");
        return -1;
    }
    tablename = root["tablename"].asString();

    return 0;
}

int encodeDealtableJson(int ret, string &str_json) {
    Json::Value root;
    root["code"] = ret;
    Json::FastWriter writer;
    str_json = writer.write(root);

    LogInfo("str_json: {}", str_json);
    return 0;
}

//这个函数的功能就是用户上传一条答案
int handleUpdateQuestion(string &user,string questionname,string answer){
    CDBManager *db_manager = CDBManager::getInstance(); 
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");
    AUTO_REL_DBCONN(db_manager, db_conn);

    CacheManager *cache_manager = CacheManager::getInstance();
    CacheConn *cache_conn = cache_manager->GetCacheConn("token");
    AUTO_REL_CACHECONN(cache_manager, cache_conn);

    int ret = 0;
    char sql_cmd[SQL_MAX_LEN] = {0};

    int user_id;
    int question_id;
    
    //由于前端界面中题目单选题的答案必定是a,b,c,d所以没有必要判断类型是否一致
    //直接插入便是，先从user获取user_id,再从questionname获取question_id，最后结合answer插入responses表
    sprintf(sql_cmd,"select user_id from Users where user_name = '%s'",user);
    CResultSet *result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        //从结果获取到user_id
        user_id = result_set->GetInt("user_id");
        ret = 0;
    }else{
        ret = -1;
    }
    delete result_set;

    memset(sql_cmd, 0, sizeof(sql_cmd));

    sprintf(sql_cmd,"select question_id from Questions where question_text = '%s'",questionname);
    result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        //从结果获取到user_id
        question_id = result_set->GetInt("question_id");
        ret = 0;
    }else{
        ret = -1;
    }
    delete result_set;

    //到这里为止question_id和user_id获取成功
    memset(sql_cmd, 0, sizeof(sql_cmd));

    //插入数据库
    sprintf(sql_cmd,"insert into Responses (question_id,user_id,answer) values (%d,%d,'%s')",question_id,user_id,answer);
    if(!db_conn->ExecuteCreate(sql_cmd)){
        //执行插入语句
        LogError("{} 操作失败", sql_cmd);
        ret = -1;
        goto END;
    }

    //查询用户表数量+1      web热点 大明星  微博存在缓存里面。
    if (CacheIncrCount(cache_conn, string(user)) < 0) {
        LogError(" CacheIncrCount 操作失败");
    }

END:
    return ret;
}


//这个函数功能是用户删除自己填写的表
//但是，在mysql数据库中，能暴露给用户使用的表只有responses
//但是由于调查问卷，用户只需要在全部填完之后才选择删除或者提交，所以向上的接口就这一个
//所以用户想删除一张整表，实际上是删除所有survey_id相同,question_id不同的回答
//所以这里其实是不断调用下面的函数
//这个函数功能是用户删除自己回答的一个问题
int handleDeleteQuestion(string &user, string &questionname) {
    CDBManager *db_manager = CDBManager::getInstance();
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");
    AUTO_REL_DBCONN(db_manager, db_conn);

    CacheManager *cache_manager = CacheManager::getInstance();
    CacheConn *cache_conn = cache_manager->GetCacheConn("token");
    AUTO_REL_CACHECONN(cache_manager, cache_conn);

    int ret = 0;
    char sql_cmd[SQL_MAX_LEN] = {0};

    int user_id;
    int question_id;

    // 先从user获取user_id
    sprintf(sql_cmd, "select user_id from Users where user_name = '%s'", user);
    CResultSet *result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        // 从结果获取到user_id
        user_id = result_set->GetInt("user_id");
        ret = 0;
    } else {
        ret = -1;
    }
    delete result_set;

    memset(sql_cmd, 0, sizeof(sql_cmd));

    // 再从questionname获取question_id
    sprintf(sql_cmd, "select question_id from Questions where question_text = '%s'", questionname);
    result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        // 从结果获取到question_id
        question_id = result_set->GetInt("question_id");
        ret = 0;
    } else {
        ret = -1;
    }
    delete result_set;

    // 到这里为止question_id和user_id获取成功
    memset(sql_cmd, 0, sizeof(sql_cmd));

    // 根据question_id和user_id删除Responses表中的对应记录
    sprintf(sql_cmd, "delete from Responses where question_id = %d and user_id = %d", question_id, user_id);
    if (!db_conn->ExecuteDelete(sql_cmd)) {
        // 执行删除语句
        LogError("{} 操作失败", sql_cmd);
        ret = -1;
        goto END;
    }

    // 查询用户表数量-1（假设这里和更新操作类似，也需要对缓存进行处理，这里是数量减1）
    if (CacheDecrCount(cache_conn, string(user)) < 0) {
        LogError(" CacheDecrCount 操作失败");
    }

END:
    return ret;
}

//我希望前端发来的一张用户填好的表的json格式如下：
/*
{
    user_name:xxx,
    table_name,
    {
        question_text xxx,
        answer xxx,
    }
    {
        question_text xxx,
        answer xxx,
    }
    ...
}
*/
int ApiUpload(string &url, string &post_data, string &str_json) {
    UNUSED(url);
    int ret = 0;
    string table_name;
    string question_name;
    string answer;
    string user;

    // 创建JSON解析器对象
    Json::Reader reader;
    Json::Value root;

    // 解析JSON数据
    if (!reader.parse(post_data, root)) {
        LogError("JSON解析失败: {}", reader.getFormattedErrorMessages());
        ret = -1;
        goto END;
    }

    // 获取用户名称
    user = root["user_name"].asString();

    // 获取问卷名称（假设问卷名称在JSON中的键为"table_name"，根据实际情况修改）
    table_name = root["table_name"].asString();

    // 获取问题和答案数组
    const Json::Value& questions = root["questions"];  // 假设问题数据在JSON中的键为"questions"，根据实际情况修改
    for (const auto& question : questions) {
        // 获取问题文本
        question_name = question["question_text"].asString();

        // 获取答案
        answer = question["answer"].asString();

        // 调用handleUpdateQuestion函数插入答案到数据库
        if (handleUpdateQuestion(user, question_name, answer)!= 0) {
            LogError("插入答案到数据库失败");
            ret = -1;
            goto END;
        }
    }

    ret = 0;

END:
    Json::Value value;
    value["code"] = (ret == 0)? 0 : 1;
    str_json = value.toStyledString();
    return ret;
}
