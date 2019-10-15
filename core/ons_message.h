#ifndef __C_ONS_MESSAGE_H__
#define __C_ONS_MESSAGE_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rocketmq/CCommon.h>

typedef struct ONSMessage ONSMessage;

ROCKETMQCLIENT_API ONSMessage* CreateONSMessage(const char* topic);
ROCKETMQCLIENT_API int DestroyONSMessage(ONSMessage* msg);
ROCKETMQCLIENT_API int SetONSMessageTopic(ONSMessage* msg, const char* topic);
ROCKETMQCLIENT_API int SetONSMessageTags(ONSMessage* msg, const char* tags);
ROCKETMQCLIENT_API int SetONSMessageKeys(ONSMessage* msg, const char* keys);
ROCKETMQCLIENT_API int SetONSMessageBody(ONSMessage* msg, const char* body);
ROCKETMQCLIENT_API int SetONSByteMessageBody(ONSMessage* msg, const char* body, int len);
ROCKETMQCLIENT_API int SetONSMessageProperty(ONSMessage* msg, const char* key, const char* value);
ROCKETMQCLIENT_API int SetONSStartDeliverTime(ONSMessage* msg, long long time);

#ifdef __cplusplus
}
#endif
#endif  //__C_ONS_MESSAGE_H__
