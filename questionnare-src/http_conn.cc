#include"http_conn.h"
#include"api_common.h"
#include"api_register.h"
#include"api_login.h"
#include "dlog.h"
#include "http_parser_wrapper.h"


void CHttpConn::AddResponseData(uint32_t conn_uuid, string &resp_data) {
    LogInfo("into");
    ResponsePdu_t *pResp = new ResponsePdu_t;
    pResp->conn_uuid = conn_uuid;
    pResp->resp_data = std::move(resp_data);

    s_resp_mutex.lock();
    s_response_pdu_list.push_back(pResp);
    s_resp_mutex.unlock();
}