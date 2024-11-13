#include "api_root_tables.h"
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "api_common.h"
#include "json/json.h"
#include "http_conn.h"
#include <sys/time.h>

//root用户不用验证token了

int encodeCountJson1(int ret, int total, string &str_json) {
    Json::Value root;
    root["code"] = ret;
    if (ret == 0) {
        root["total"] = total; // 正常返回的时候才写入token
    }
    Json::FastWriter writer;
    str_json = writer.write(root);
    return 0;
}

//解析json包，处理参数cmd=normal的情况
/*
{
    "title":xxx
}
*/
int decodeRootTablelistJson(string &str_json,string &table_name){
    bool res;
    Json::Value root;
    Json::Reader jsonReader;
    res = jsonReader.parse(str_json, root);
    if (!res) {
        LogError("parse reg json failed ");
        return -1;
    }
    int ret = 0;

    if(root["title"].isNull()){
        LogError("table_name null\n");
        return -1;
    }
    table_name = root["title"].asString();

    return ret;
}


//获取所有创建的调查问卷个数
int getTablesCount(CDBConn *db_conn,int &count){
    int ret = 0;
    int64_t table_count = 0;

    if(DBGetUserTableCountByUsername(db_conn,"root",count)){
        LogError("DBGetRootTablesCountByRootname failed");
        return -1;
    }

    return 0;
}

// url="http://192.168.186.138/api/root/tables?cmd=count"
template <typename... Args>
std::string FormatString3(const std::string &format, Args... args) {
    auto size = std::snprintf(nullptr, 0, format.c_str(), args...) +
                1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args...);
    return std::string(buf.get(),
                      buf.get() + size - 1); // We don't want the '\0' inside
}

//回发的格式
/*
{
    "code":xxx,
    "total":xxx,
    {
        "table_name":xxx
        "deadline":xxx,
    }
    {
        "table_name":xxx
        "deadline":xxx,
    }
    ...
}
*/
//// url="http://192.168.186.138/api/root/tables?cmd=count"
int getRootTableList(std::string &str_json){
    LogInfo("getRootTableList info");
    int ret = 0;
    int total = 0;
    std::string str_sql;
    CDBManager *db_manager = CDBManager::getInstance();
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");
    AUTO_REL_DBCONN(db_manager, db_conn);

    ret = getTablesCount(db_conn, total);
    if (ret < 0) {
        LogError("getRootFilesCount failed");
        return -1;
    } else {  // root用户还没有发布任何表格
        if (total == 0) {
            Json::Value root;
            root["code"] = 0;
            root["total"] = 0;
            Json::FastWriter writer;
            str_json = writer.write(root);
            LogWarn("getRootTablesCount = 0");
            return 0;
        }
    }

    //到这里就意味着创建了表格，所有的表格在root里都有，但是root用户不负责填写，所以其他表没有root信息，除了Surveys

    //root用户id是1
    // 从Surveys表中查询所有这个user_id对应的title和deadline
    std::vector<std::string> table_titles;
    std::vector<std::string> table_deadlines;
    str_sql = FormatString3("select title, deadline from Surveys where user_id = 1");
    CResultSet *result_set = db_conn->ExecuteQuery(str_sql.c_str());
    while (result_set && result_set->Next()) {
        table_titles.push_back(result_set->GetString("title"));
        table_deadlines.push_back(result_set->GetString("deadline"));
    }
    delete result_set;

    // 组织成指定的JSON格式
    Json::Value root;
    root["code"] = 0;
    root["total"] = static_cast<int>(table_titles.size());
    Json::Value tables;
    for (size_t i = 0; i < table_titles.size(); ++i) {
        Json::Value table;
        table["table_name"] = table_titles[i];
        table["deadline"] = table_deadlines[i];
        tables.append(table);
    }
    root["tables"] = tables;

    // 使用Json::FastWriter将JSON对象转换为字符串
    Json::FastWriter writer;
    str_json = writer.write(root);

    return 0;
}

// url="http://192.168.186.138/api/root/tables?cmd=normal"
/*
当root管理员点击特定的表格后，接下来就要获取普通用户填写的结果了
*/
/*
{
    "code":0,
    "survey_title":"调查问卷标题示例",
    "total_questions":3,
    "questions":[
        {
            "question_text":"你最喜欢的颜色是什么？",
            "question_type":"单选",
            "options": [
            {
                "option_text":"红色"，
                "option_count":10,
            },
            {
                "option_text": "蓝色"
                "option_count":6,
            },
            {
                "option_text": "绿色",
                "option_count":1,
            }
            ]
        },
        {
            "question_text": "你平时的兴趣爱好有哪些？",
            "question_type": "多选",
            "options": [
                {
                    "option_text": "阅读",
                    "option_count":13,
                },
                {
                    "option_text": "运动",
                    "option_count":12,
                },
                {
                    "option_text": "绘画",
                    "option_count":7,
                },
                {
                    "option_text": "音乐",
                    "option_count":15,
                }
            ]
        },
        {
            "question_text": "请填写你所在的城市",
            "question_type": "填空",
            "options": [
                option_texts:[
                    {
                        "option_text":"大连"
                    },
                    {
                        "option_text":"北京"
                    }
                ]
            ] 
        },
    ]
}
*/
int getRootTable(string &table_name, string &str_json) {
    LogInfo("getRootTable info");
    int ret = 0;
    int total = 0;
    string str_sql;
    CDBManager *db_manager = CDBManager::getInstance();
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");
    AUTO_REL_DBCONN(db_manager, db_conn);

    // 1. 查询 Surveys 表，查找给定 table_name 的 survey_id 和 user_id
    str_sql = FormatString3("SELECT survey_id, user_id FROM Surveys WHERE title = '%s'", table_name.c_str());
    CResultSet *result_set = db_conn->ExecuteQuery(str_sql.c_str());
    if (result_set == nullptr || !result_set->Next()) {
        LogError("No surveys found for table_name: %s", table_name.c_str());
        return -1;  // 没有找到匹配的调查问卷
    }

    vector<int> survey_ids;
    vector<int> user_ids;
    do {
        int survey_id = result_set->GetInt("survey_id");
        survey_ids.push_back(survey_id);
        int user_id = result_set->GetInt("user_id");
        user_ids.push_back(user_id);
    } while (result_set->Next());

    // 2. 查询 Questions 表，根据 survey_id 查找所有问题
    Json::Value root;
    root["code"] = 0;  // 返回码，成功
    root["survey_title"] = table_name.c_str(); 
    root["total_questions"] = Json::UInt(survey_ids.size());  // 显式转换为 Json::UInt 类型

    Json::Value questions(Json::arrayValue);
    for (int survey_id : survey_ids) {
        str_sql = FormatString3("SELECT question_id, question_text, question_type FROM Questions WHERE survey_id = %d", survey_id);
        result_set = db_conn->ExecuteQuery(str_sql.c_str());
        if (result_set == nullptr) {
            LogError("Failed to fetch questions for survey_id: %d", survey_id);
            return -1;
        }

        // 3. 对于每个问题，查询 Options 表获取选项信息
        Json::Value questions_list(Json::arrayValue);
        while (result_set->Next()) {
            int question_id = result_set->GetInt("question_id");
            string question_text = result_set->GetString("question_text");
            string question_type = result_set->GetString("question_type");

            Json::Value question;
            question["question_text"] = question_text;
            question["question_type"] = question_type;

            // 查询 Options 表，获取选项信息
            str_sql = FormatString3("SELECT option_id, option_text FROM Options WHERE question_id = %d", question_id);
            CResultSet *options_result = db_conn->ExecuteQuery(str_sql.c_str());
            Json::Value options(Json::arrayValue);
            map<string, int> option_count_map;

            while (options_result->Next()) {
                string option_text = options_result->GetString("option_text");
                Json::Value option;
                option["option_text"] = option_text;
                options.append(option);
                option_count_map[option_text] = 0;  // 初始化选项的计数
            }

            // 如果是单选或多选题，统计每个选项的回答数量
            if (question_type != "填空") {
                // 查询 Answers 表，统计每个选项的选中数量
                for (const auto& user_id : user_ids) {
                    str_sql = FormatString3("SELECT answer FROM Answers WHERE survey_id = %d AND question_id = %d AND user_id = %d", survey_id, question_id, user_id);
                    CResultSet *answers_result = db_conn->ExecuteQuery(str_sql.c_str());
                    while (answers_result->Next()) {
                        string answer = answers_result->GetString("answer");
                        if (option_count_map.find(answer) != option_count_map.end()) {
                            option_count_map[answer]++;  // 选项的计数加1
                        }
                    }
                }

                // 将计数结果添加到 options 中
                for (auto& option : options) {
                    string option_text = option["option_text"].asString();
                    option["option_count"] = option_count_map[option_text];
                }
            }

            question["options"] = options;

            // 4. 处理填空题：如果是填空题，我们仅记录用户的回答
            if (question_type == "填空") {
                Json::Value fill_in_answers(Json::arrayValue);
                for (const auto& user_id : user_ids) {
                    str_sql = FormatString3("SELECT answer FROM Answers WHERE survey_id = %d AND question_id = %d AND user_id = %d", survey_id, question_id, user_id);
                    CResultSet *answers_result = db_conn->ExecuteQuery(str_sql.c_str());
                    while (answers_result->Next()) {
                        string answer = answers_result->GetString("answer");
                        Json::Value ans;
                        ans["answer_text"] = answer;
                        fill_in_answers.append(ans);
                    }
                }
                question["answers"] = fill_in_answers;
            }

            questions_list.append(question);
        }

        root["questions"] = questions_list;
    }

    // 5. 返回 JSON 数据
    Json::FastWriter writer;
    str_json = writer.write(root);
    return 0;
}



int ApiRootTables(string &url,string &post_data,string &str_json){
    UNUSED(url);
    char cmd[20];
    int ret = 0;
    int count = 0;
    string table_name;

    //解析命令 解析url获取自定义参数
    QueryParseKeyValue(url.c_str(), "cmd", cmd, NULL);
    LogInfo("url: {}, cmd: {} ",url, cmd);

    if(strcmp(cmd,"count") == 0){   //第一次返回表格数量和名字
        if(getRootTableList(str_json)<0){
            ret = -1;
            return -1;   
        }
    }else{
        if(strcmp(cmd, "normal") != 0){
            LogError("unknow cmd: {}", cmd);
            encodeCountJson1(1, 0, str_json);
            return -1;
        }
        ret = decodeRootTablelistJson(post_data,table_name);

        if(ret == 0){
            if(getRootTable(table_name,str_json)){
                LogError("getRootTable failed");
                encodeCountJson1(1, 0, str_json);
                return -1;
            }
        }else{
            LogError("decodeTableslistJson failed");
            encodeCountJson1(1, 0, str_json);
            return -1;
        }
    }
    return 0;
}