
#include <stdio.h>
#include <stdlib.h>
#include <rocketmq/Message.h>
#include "ons_message.h"

//using namespace ons;

ONSMessage* CreateONSMessage(const char* topic) {
  ons::Message *msg = new ons::Message();
  msg->setTopic(topic);
  return (ONSMessage *)msg;
}

int DestroyONSMessage(ONSMessage* msg) {
  ons::Message *onsMsg = (ons::Message *)msg;
  delete onsMsg;
  return OK;
}

int SetONSMessageTopic(ONSMessage* msg, const char* topic) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->setTopic(topic);
  return OK;
}

int SetONSMessageTags(ONSMessage* msg, const char* tags) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->setTag(tags);
  return OK;
}

int SetONSMessageKeys(ONSMessage* msg, const char* keys) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->setKey(keys);
  return OK;
}

int SetONSMessageBody(ONSMessage* msg, const char* body) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->setMsgBody(body);
  return OK;
}

int SetONSByteMessageBody(ONSMessage* msg, const char* body, int len) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->setBody((unsigned char *)body, len);
  return OK;
}

int SetONSMessageProperty(ONSMessage* msg, const char* key, const char* value) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->putSystemProperties(key, value);
  return OK;
}

int SetONSStartDeliverTime(ONSMessage* msg, long long time) {
  ons::Message *onsMsg = (ons::Message *)msg;
  onsMsg->setStartDeliverTime(time);
  return OK;
}
