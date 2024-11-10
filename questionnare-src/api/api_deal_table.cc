#include "api_deal_table.h"
#include "api_common.h"
#include "redis_keys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

// int decodeDealTableJson(string &str_json,string &user_name,string &token,string &tablename){
//     bool res;
//     Json::Value root;
//     Json::Reader jsonReader;
//     res = jsonReader.parse(str_json, root);
//     if (!res) {
//         LogError("parse reg json failed ");
//         return -1;
//     }

//     if (root["user"].isNull()) {
//         LogError("user null");
//         return -1;
//     }
//     user_name = root["user"].asString();

//     if (root["token"].isNull()) {
//         LogError("token null");
//         return -1;
//     }
//     token = root["token"].asString();

//     if (root["tablename"].isNull()) {
//         LogError("tablename null");
//         return -1;
//     }
//     tablename = root["tablename"].asString();

//     return 0;
// }

int encodeDealtableJson(int ret, string &str_json) {
    Json::Value root;
    root["code"] = ret;
    Json::FastWriter writer;
    str_json = writer.write(root);

    LogInfo("str_json: {}", str_json);
    return 0;
}

//这个函数的功能就是用户上传一条答案
int handleUpdateQuestion(string user,string questionname,string table_name,string answer){
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
    int survey_id;
    
    //由于前端界面中题目单选题的答案必定是a,b,c,d所以没有必要判断类型是否一致
    //直接插入便是，先从user获取user_id,再从questionname获取question_id，最后结合answer插入responses表
    sprintf(sql_cmd,"select user_id from Users where user_name = '%s'",user.c_str());
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

    sprintf(sql_cmd,"select survey_id from Surveys where title = '%s' and user_id = %d",table_name.c_str(),user_id);
    result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        //从结果获取到user_id
        survey_id = result_set->GetInt("survey_id");
        ret = 0;
    }else{
        ret = -1;
    }
    delete result_set;

    memset(sql_cmd, 0, sizeof(sql_cmd));

    sprintf(sql_cmd, "select question_id from Questions where question_text = '%s' and survey_id = '%d'", questionname.c_str(), survey_id);
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
    sprintf(sql_cmd,"insert into Responses (question_id,user_id,answer,survey_id) values (%d,%d,'%s',%d)",question_id,user_id,answer.c_str(),survey_id);
    if(!db_conn->ExecuteCreate(sql_cmd)){
        //执行插入语句
        LogError("{} 操作失败", sql_cmd);
        return -1;
    }

    //简单起见，每次都更新is_filled字段为1
    string update_sql = "UPDATE Surveys SET is_filled = 1 WHERE survey_id =?";
    LogInfo("执行更新is_filled的语句: {}", update_sql);

    CPrepareStatement *update_stmt = new CPrepareStatement();
    if (update_stmt->Init(db_conn->GetMysql(), update_sql)) {
        uint32_t update_index = 0;
        update_stmt->SetParam(update_index++, survey_id);
        bool update_bRet = update_stmt->ExecuteUpdate();
        if (update_bRet) {
            LogInfo("成功将is_filled更新为1，对应survey_id: {}", user_id);
        } else {
            LogError("更新is_filled失败，对应survey_id: {}", user_id);
        }
    }
    delete update_stmt;

    //查询用户表数量+1      web热点 大明星  微博存在缓存里面。
    if (CacheIncrCount(cache_conn, string(user)) < 0) {
        LogError(" CacheIncrCount 操作失败");
    }

END:
    return ret;
}


// 辅助函数，用于将vector<int> 类型的question_ids转换为逗号分隔的字符串，以便在SQL语句中使用IN关键字
string getQuestionIdListString(const vector<int>& question_ids) {
    stringstream ss;
    for (size_t i = 0; i < question_ids.size(); ++i) {
        if (i > 0) {
            ss << ", ";
        }
        ss << question_ids[i];
    }
    return ss.str();
}

//这个函数功能是用户删除自己填写的表
int handleDeleteTable(string user, string table_name) {
    CDBManager *db_manager = CDBManager::getInstance();
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");
    AUTO_REL_DBCONN(db_manager, db_conn);

    CacheManager *cache_manager = CacheManager::getInstance();
    CacheConn *cache_conn = cache_manager->GetCacheConn("token");
    AUTO_REL_CACHECONN(cache_manager, cache_conn);

    int ret = 0;
    char sql_cmd[SQL_MAX_LEN] = {0};
    int user_id = -1;
    int survey_id = -1;

    // 先从user获取user_id
    sprintf(sql_cmd, "select user_id from Users where user_name = '%s'", user.c_str());
    CResultSet *result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        // 从结果获取到user_id
        user_id = result_set->GetInt("user_id");
        ret = 0;
    } else {
        LogError("未能获取到用户 {} 的user_id", user);
        ret = -1;
        return ret;
    }
    delete result_set;

    memset(sql_cmd, 0, sizeof(sql_cmd));

    // 根据表名和user_id查到survey_id
    sprintf(sql_cmd, "select survey_id from Surveys where title = '%s' and user_id = %d", table_name.c_str(), user_id);
    result_set = db_conn->ExecuteQuery(sql_cmd);
    if (result_set && result_set->Next()) {
        // 从结果获取到survey_id
        survey_id = result_set->GetInt("survey_id");
        ret = 0;
    } else {
        LogError("未能根据表名 {} 和用户ID {} 获取到survey_id", table_name, user_id);
        ret = -1;
        return ret;;
    }
    delete result_set;

    // 根据survey_id查到Questions表中所有相关问题的question_id
    vector<int> question_ids;
    memset(sql_cmd, 0, sizeof(sql_cmd));
    sprintf(sql_cmd, "select question_id from Questions where survey_id = %d", survey_id);
    result_set = db_conn->ExecuteQuery(sql_cmd);
    while (result_set && result_set->Next()) {
        // 将获取到的每个question_id存入vector
        question_ids.push_back(result_set->GetInt("question_id"));
    }
    delete result_set;

    // 删除Responses表中所有符合条件的记录（该用户填写的这个表的所有答案）
    if (!question_ids.empty()) {
        // 构建删除语句，使用IN关键字处理多个question_id
        sprintf(sql_cmd, "delete from Responses where user_id = %d and question_id IN (%s)", user_id, getQuestionIdListString(question_ids).c_str());
        if (!db_conn->ExecuteDrop(sql_cmd)) {
            // 执行删除语句
            LogError("{} 操作失败", sql_cmd);
            ret = -1;
            return ret;
        }
    } else {
        LogError("未找到与survey_id {} 相关的任何问题ID，无法删除Responses表中的记录", survey_id);
        ret = -1;
        return ret;
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
    token:xxx,
    table_name xxx,
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
//当调用到这个函数的时候，post_data已经被http_conn函数解析到上面的格式
//这个函数的任务是用户上传填好的表，后端存到数据库
int ApiUploadTable(string &url, string &post_data, string &str_json) {
    //url这个参数没有用
    UNUSED(url);
    int ret = 0;
    string table_name;
    string question_name;
    string answer;
    string user_name;
    string token;

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
    user_name = root["user_name"].asString();

    //获取token,并验证
    token = root["token"].asString();
    //验证登陆token，成功返回0，失败-1
    ret = VerifyToken(user_name, token); // util_cgi.h
    if(ret == 0){  //验证成功
        // 获取问卷名称
        table_name = root["table_name"].asString();

        // 获取问题和答案数组
        const Json::Value& answers = root["answers"];  // 假设问题数据在JSON中的键为"questions"，根据实际情况修改
        for (const auto& ans : answers) {
            // 获取问题文本
            question_name = ans["question_text"].asString();

            // 获取答案
            answer = ans["answer"].asString();

            // 调用handleUpdateQuestion函数插入答案到数据库
            if (handleUpdateQuestion(user_name, question_name,table_name, answer)!= 0) {
                LogError("插入答案到数据库失败");
                ret = -1;
                goto END;
            }
        }
    }else{
        goto END;
    }

END:
    Json::Value value;
    value["code"] = (ret == 0)? 0 : 1;
    str_json = value.toStyledString();
    return ret;
}


/*
{
    user_name:xxx,
    token:xxx,
    table_name xxx,
}
*/
//下面这个函数的目的是用户想要删除填好的一张表
int ApiDeleteTable(string &url, string &post_data, string &str_json){
    //url这个参数没有用
    UNUSED(url);
    int ret = 0;
    string table_name;
    string question_name;
    string answer;
    string user_name;
    string token;

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
    user_name = root["user_name"].asString();

    //获取token,并验证
    token = root["token"].asString();
    //验证登陆token，成功返回0，失败-1
    ret = VerifyToken(user_name, token); // util_cgi.h

    if(ret == 0){  //验证成功
        // 获取问卷名称
        table_name = root["table_name"].asString();

        //接着删除这个table_name表所有的信息
        if (handleDeleteTable(user_name,table_name)!= 0) {
            LogError("删除答案到数据库失败");
            ret = -1;
            goto END;
        }
    }else{
        goto END;
    }

END:
    Json::Value value;
    value["code"] = (ret == 0)? 0 : 1;
    str_json = value.toStyledString();
    return ret;
}
