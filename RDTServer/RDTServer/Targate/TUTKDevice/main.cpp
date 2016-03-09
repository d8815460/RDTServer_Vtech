#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <errno.h>
#include <limits.h>
#include <iostream>

#include "Device.hpp"
#include "Body.hpp"
#include "IOTCException.hpp"
#include "Utility.hpp"
#include "sqlite3.h"


//// curlpp
//#include <curlpp/cURLpp.hpp>
//#include <curlpp/Easy.hpp>
//#include <curlpp/Options.hpp>
//#include <curlpp/Exception.hpp>
//#include <curlpp/Infos.hpp>
//
//// json
//#include <json/reader.h>

using namespace std;

//void MyCallback(FunctionInfo *pFunctionInfo)
//{
//    LOGD("MyCallback");
//    
//    LOGD("type = %u", pFunctionInfo->type);
//}

//void readJson()
//{
//    std::string strValue = "{\"name\":\"json\",\"array\":[{\"cpp\":\"jsoncpp\"},{\"java\":\"jsoninjava\"},{\"php\":\"support\"}]}";
//    
//    Json::Reader reader;
//    Json::Value value;
//    
//    if (reader.parse(strValue, value))
//    {
//        std::string out = value["name"].asString();
//        std::cout << out << std::endl;
//        const Json::Value arrayObj = value["array"];
//        
//        for (unsigned int i = 0; i < arrayObj.size(); i++)
//        {
//            if (!arrayObj[i].isMember("cpp"))
//                continue;
//            out = arrayObj[i]["cpp"].asString();
//            std::cout << out;
//            if (i != (arrayObj.size() - 1))
//                std::cout << std::endl;
//        }
//    }
//}

//void writeJson()
//{
//    Json::Value root;
//    Json::Value arrayObj;
//    Json::Value item;
//    
//    item["cpp"] = "jsoncpp";
//    item["java"] = "jsoninjava";
//    item["php"] = "support";
//    arrayObj.append(item);
//    
//    root["name"] = "json中文鑫";
//    root["array"] = arrayObj;
//    
//    root.toStyledString();
//    std::string out = root.toStyledString();
//    std::cout << out << std::endl;
//}

//void TPNSSend(char* url)
//{
//    try
//    {
//        curlpp::Cleanup cleaner;
//        curlpp::Easy request;
//        
//        using namespace curlpp::Options;
//        request.setOpt(Verbose(true));
//        request.setOpt(Url(url));
//        request.setOpt(new curlpp::options::SslEngineDefault());
//        
//        LOGD("Send TPNS message:%s", url);
//        request.perform();
//        
//        //        std::string effURL;
//        //        curlpp::infos::EffectiveUrl::get(request, effURL);
//        //        std::cout << "Effective URL: " << effURL << std::endl;
//        //
//        //        //other way to retreive URL
//        //        std::cout << std::endl
//        //        << "Effective URL: "
//        //        << curlpp::infos::EffectiveUrl::get(request)
//        //        << std::endl;
//        //
//        //        std::cout << "Response code: "
//        //        << curlpp::infos::ResponseCode::get(request)
//        //        << std::endl;
//        //
//        //        std::cout << "SSL engines: "
//        //        << curlpp::infos::SslEngines::get(request)
//        //        << std::endl;
//    }
//    catch ( curlpp::LogicError & e ) {
//        std::cout << e.what() << std::endl;
//    }
//    catch ( curlpp::RuntimeError & e ) {
//        std::cout << e.what() << std::endl;
//    }
//    
//    
////    try
////    {
////        curlpp::Cleanup myCleanup;
////        
////        // Creation of the URL option.
////        curlpp::Easy myRequest;
////        myRequest.setOpt(new curlpp::options::Url(std::string(url)));
////        myRequest.setOpt(new curlpp::options::SslEngineDefault());
////        myRequest.perform();
////    }
////    catch( curlpp::RuntimeError &e )
////    {
////        std::cout << e.what() << std::endl;
////    }
////    catch( curlpp::LogicError &e )
////    {
////        std::cout << e.what() << std::endl;
////    }
//}
//
//#define MQTTCLIENT_QOS2 1
//
//#include "MQTTClient.h"
//
//#define DEFAULT_STACK_SIZE -1
//
//#include "linux.h"
//
//int arrivedcount = 0;
//
//void messageArrived(MQTT::MessageData& md)
//{
//    MQTT::Message &message = md.message;
//    
//    printf("Message %d arrived: qos %d, retained %d, dup %d, packetid %d\n",
//           ++arrivedcount, message.qos, message.retained, message.dup, message.id);
//    printf("Payload %.*s\n", (int)message.payloadlen, (char*)message.payload);
//}

static char createsql[] = "CREATE TABLE Contact("
                        "ID INTEGER PRIMARY KEY,"
                        "Name VARCHAR(10),"
                        "PhoneNumber VARCHAR(10));";

static char insertsql[] = "INSERT INTO Contact VALUES(NULL, 'Fred', '09990123456');";
static char querysql[] = "SELECT * FROM Contact;";

int main(int argc, char *argv[])
{
    // MQTT
    {
//        IPStack ipstack = IPStack();
//        float version = 0.3;
//        const char* topic = "mbed-sample";
//        
//        printf("Version is %f\n", version);
//        
//        MQTT::Client<IPStack, Countdown> client = MQTT::Client<IPStack, Countdown>(ipstack);
//        
////        const char* hostname = "iot.eclipse.org";
//        const char* hostname = "localhost";
//        int port = 1883;
//        printf("Connecting to %s:%d\n", hostname, port);
//        int rc = ipstack.connect(hostname, port);
//        if (rc != 0)
//            printf("rc from TCP connect is %d\n", rc);
//        
//        printf("MQTT connecting\n");
//        MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
//        data.MQTTVersion = 3;
//        data.clientID.cstring = (char*)"mbed-icraggs";
//        rc = client.connect(data);
//        if (rc != 0)
//            printf("rc from MQTT connect is %d\n", rc);
//        printf("MQTT connected\n");
//        
//        rc = client.subscribe(topic, MQTT::QOS2, messageArrived);
//        if (rc != 0)
//            printf("rc from MQTT subscribe is %d\n", rc);
//        
//        MQTT::Message message;
//        
//        // QoS 0
//        char buf[100];
//        sprintf(buf, "Hello World!  QoS 0 message from app version %f", version);
//        message.qos = MQTT::QOS0;
//        message.retained = false;
//        message.dup = false;
//        message.payload = (void*)buf;
//        message.payloadlen = strlen(buf)+1;
//        rc = client.publish(topic, message);
//        if (rc != 0)
//            printf("Error %d from sending QoS 0 message\n", rc);
//        else while (arrivedcount == 0)
//            client.yield(100);
//        
//        // QoS 1
//        printf("Now QoS 1\n");
//        sprintf(buf, "Hello World!  QoS 1 message from app version %f", version);
//        message.qos = MQTT::QOS1;
//        message.payloadlen = strlen(buf)+1;
//        rc = client.publish(topic, message);
//        if (rc != 0)
//            printf("Error %d from sending QoS 1 message\n", rc);
//        else while (arrivedcount == 1)
//            client.yield(100);
//        
//        // QoS 2
//        sprintf(buf, "Hello World!  QoS 2 message from app version %f", version);
//        message.qos = MQTT::QOS2;
//        message.payloadlen = strlen(buf)+1;
//        rc = client.publish(topic, message);
//        if (rc != 0)
//            printf("Error %d from sending QoS 2 message\n", rc);
//        while (arrivedcount == 2)
//            client.yield(100);
//        
//        rc = client.unsubscribe(topic);
//        if (rc != 0)
//            printf("rc from unsubscribe was %d\n", rc);
//        
//        rc = client.disconnect();
//        if (rc != 0)
//            printf("rc from disconnect was %d\n", rc);
//        
//        ipstack.disconnect();
//        
//        printf("Finishing with %d messages received\n", arrivedcount);
    }
    
    // HTTP
    {
        /*
         步驟1. Device註冊
         https://push.iotcplatform.com:7380/tpns?cmd=device&uid=CZPABX7CV9RCVNPGYHDJ
         
         步驟2. 推送Event
         https://push.iotcplatform.com:7380/tpns?cmd=event&uid=CZPABX7CV9RCVNPGYHDJ&event_type=100&msg=MSG_STRING
         
         MSG_STRING為任意你想要推送的文字
         CZPABX7CV9RCVNPGYHDJ 為已經在白名單內的測試UID
         */
        
//        char uid[] = "E7YAB554YTZCAH6GY1E1";
//        char uid[] = "CZPABX7CV9RCVNPGYHDJ";
//        6JRCE4K63NMBBSHP111A
        
//        char url[] = "http://push.iotcplatform.com/apns?cmd=device&uid=6JRCE4K63NMBBSHP111A&interval=0";
//        char url[] = "https://push.iotcplatform.com:7380/tpns?cmd=device&uid=6JRCE4K63NMBBSHP111A&interval=0";
        
        
//        http://push.iotcplatform.com/apns/apns.php?cmd=event&uid=6JRCE4K63NMBBSHP111A&debug=1
//        TPNSSend(url);
        
//        char url2[] = "http://push.iotcplatform.com/apns?cmd=event&uid=6JRCE4K63NMBBSHP111A&event_type=100&msg=MSG_STRING&interval=0&debug=1";
//        char url2[] = "https://push.iotcplatform.com:7380/tpns?cmd=event&uid=6JRCE4K63NMBBSHP111A&event_type=100&msg=MSG_STRING&interval=0&debug=1";
//        TPNSSend(url2);
    }
    
    // json
    {
//        readJson();
//        writeJson();
    }
    
    {
//    const char *pLogFile = "iotcLogFile.txt";
//    IOTC_Set_Log_Path((char*)pLogFile , 0);
//    RDT_Set_Log_Path((char*)pLogFile, 0);
    }
    
    {
//        int rows, cols;
//        sqlite3 *db;
//        char *errMsg = NULL;
//        char **result;
//        
//        /* 開啟 database 檔 */
//        if (sqlite3_open_v2("database.db3", &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
//            return -1;
//        }
//        
//        /* 建立 Table */
//        sqlite3_exec(db, createsql, 0, 0, &errMsg);
//        
//        /* 新增一筆資料 */
//        sqlite3_exec(db, insertsql, 0, 0, &errMsg);
//        /* 取得該筆資料的 ID */
//        printf("%lld\n", sqlite3_last_insert_rowid(db));
//        
//        /* 取得 database 裡所有的資料 */
//        sqlite3_get_table(db , querysql, &result, &rows, &cols, &errMsg);
//        
//        /* 列出所有資料 */
//        for (int i=0 ; i<rows ; i++) {
//            for (int j=0 ; j<cols ; j++) {
//                printf("%s\t", result[i * cols + j]);
//            }
//            
//            printf("\n");
//        }
//        
//        /* 釋放 */
//        sqlite3_free_table(result);
//        
//        /* 關閉 database */
//        sqlite3_close(db);
    }
    
    // RDT
    {
        LOGD("argc:%d", argc);
        LOGD("argv[0]:%s", argv[0]);
        
        try {
            if (argc == 3) {
                char uid[21];
                memset(uid, 0, 21);
                strcpy(uid, argv[2]);
                LOGD("uid:%s", uid);
                
                Device *pDevice = NULL;
                Body::runBody(&pDevice, argv[1]);
                pDevice->run(uid);
                
                delete pDevice;
            }
            else {
                throw invalid_argument("參數數量不正確，必須數入兩個參數，如：./RDTServer PowerStripDevice 00000000000000000000");
            }
        }
        catch (Exception& e) {
            Utility::showException(e);
        }
        catch (string& message) {
            LOGE("%s", message.c_str());
        }
        catch (exception& e) {
            LOGE("%s", e.what());
        }
    }
    
    LOGD("Server exit!");
	return 0;
}
