#include"api_common.h"

string s_dfs_path_client;
string s_storage_web_server_ip;
string s_storage_web_server_port;

// 比如加载mysql相关的记录到redis
// https://blog.csdn.net/lxw1844912514/article/details/121528746
/*对于 Redis 在内存中的数据，需要定期的同步到磁盘中，但对于 Redis
异常重启，就没有办法了。比如在 Redis 中插入后，Redis 重启
，数据没有持久化到硬盘。这时可以在重启 Redis 后，从数据库执行下 count(*)
操作,然后更新到 Redis 中。一次全表扫描还是可行的。*/

//在这里模版与可变参数相辅相成,字符串的格式化和printf的参数填充相似
template<typename... Args>
std::string FormatString(const std::string &format,Args... args){
    auto size = std::snprintf(NULL,0,format.c_str(),args...)+1;
    std::unique_ptr<char[]> buf(new char[size]);
    std::snprintf(buf.get(),size,format.c_str(),args...);
    return std::string(buf.get(),
                       buf.get() + size - 1); // We don't want the '\0' inside
}

//mysql存储的部分信息加载redis缓存
int ApiInit(){
    CDBManager *db_manager = CDBManager::getInstance();
    CDBConn *db_conn = db_manager->GetDBConn("qs_slave");  //从数据库管理器获取一个名为 "tuchuang_slave" 的数据库连接对象。这个连接对象用于执行数据库操作
    AUTO_REL_DBCONN(db_manager, db_conn);
    CacheManager *cache_manager = CacheManager::getInstance();
    CacheConn *cache_conn = cache_manager->GetCacheConn("token");
    AUTO_REL_CACHECONN(cache_manager, cache_conn);

    int ret = 0;
    // 共享文件的数量 统计加载到redis
    int count = 0;
    ret = DBGetAllTablesCount(db_conn, count);
    printf("%d\n",count);
    if (ret < 0) {
        LogError("GetTablesCount failed");
        return -1;
    }
    // 加载到redis
    ret = CacheSetCount(cache_conn, TABLE_USER_COUNT, (int64_t)count);
    if (ret < 0) {
        LogError("CacheSetCount failed");
        return -1;
    }

    // 对于个人的文件数量 和图片分享数量，在登录的时候 读取到redis

    return 0;
}
int CacheSetCount(CacheConn *cache_conn,string key, int64_t count){
    string ret = cache_conn->Set(key,std::to_string(count));
    if (!ret.empty()) {
        return 0;
    } else {
        return -1;
    }
}

int CacheGetCount(CacheConn *cache_conn, string key, int64_t &count){
    count = 0;
    string str_count = cache_conn->Get(key);
    if (!str_count.empty()) {
        count = atoll(str_count.c_str());  //longlong
        return 0;
    } else {
        return -1;
    }
}

//键值递增
int CacheIncrCount(CacheConn *cache_conn, string key){
    int64_t count = 0;
    int ret = cache_conn->Incr(key, count);
    if (ret < 0) {
        return -1;
    }
    LogInfo("{}-{}", key, count);
    
    return 0;
}

//那这个自然是递减
int CacheDecrCount(CacheConn *cache_conn, string key) {
    int64_t count = 0;
    int ret = cache_conn->Decr(key, count);
    if (ret < 0) {
        return -1;
    }
    LogInfo("{}-{}", key, count);
    if (count < 0) {
        LogError("{} 请检测你的逻辑 decr  count < 0  -> {}", key , count);
        ret = CacheSetCount(cache_conn, key, 0); // 文件数量最小为0值
        if (ret < 0) {
            return -1;
        }
    }
    return 0;
}

//获取每个用户可以填写的调查问卷表的个数
int DBGetUserTableCountByUsername(CDBConn *db_conn, string user_name, int &count) {
    count = 0;
    int ret = 0;
    string str_sql;

    // 先通过用户名获取用户 ID
    str_sql = FormatString("select id from Users where user_name='%s'", user_name.c_str());
    LogInfo("执行：{}", str_sql);
    CResultSet *user_id_result_set = db_conn->ExecuteQuery(str_sql.c_str());
    int user_id = 0;
    if (user_id_result_set && user_id_result_set->Next()) {
        user_id = user_id_result_set->GetInt("id");
        delete user_id_result_set;
    } else {
        // 用户不存在
        LogError("找不到用户：{}", str_sql);
        ret = -1;
        return ret;
    }

    // 再使用用户 ID 查询调查问卷表个数
    str_sql = FormatString("select count(*) from Surveys where user_id=%d", user_id);
    LogInfo("执行：{}", str_sql);
    CResultSet *result_set = db_conn->ExecuteQuery(str_sql.c_str());
    if (result_set && result_set->Next()) {
        count = result_set->GetInt("count(*)");
        ret = 0;
        delete result_set;
    } else if (!result_set) {
        // 操作失败
        LogError("{} 操作失败", str_sql);
        ret = -1;
    } else {
        // 没有记录则初始化记录数量为 0
        ret = 0;
        LogInfo("没有记录: count: {}", count);
    }
    return ret;
}

//获取所有调查问卷的数量
int DBGetAllTablesCount(CDBConn *db_conn,int &count){
    count = 0;
    int ret = 0;

    //先查看用户是否存在
    string str_sql = "SELECT COUNT(DISTINCT title) AS total_unique_surveys FROM Surveys";
    printf("%s\n",str_sql.c_str());
    CResultSet *result_set = db_conn->ExecuteQuery(str_sql.c_str());
    if (result_set && result_set->Next()) {      //这个是执行语句返回的结果，可以按行循环读取
        // 存在在返回
        count = result_set->GetInt("count(*)");
        LogInfo("count: {}", count);
        ret = 0;
        delete result_set;
    } else if (!result_set) {
        // 操作失败
        LogError("{} 操作失败", str_sql);
        ret = -1;
    } else {
        ret = 0;
        LogInfo("没有记录: count: {}", count);
    }

    return ret;
}


