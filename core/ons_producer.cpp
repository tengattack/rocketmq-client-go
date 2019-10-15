
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <rocketmq/ONSFactory.h>
#include <rocketmq/ONSClientException.h>
#include "ons_producer.h"

//using namespace ons;

struct ONSProducer {
  ons::Producer *pProducer;
};

ONSProducer* CreateONSProducer(const ONSFactoryProperty* factoryInfo) {
  // 创建 producer，并配置发送消息所必需的信息；
  ons::ONSFactoryProperty onsFactoryInfo;
  onsFactoryInfo.setFactoryProperty(ons::ONSFactoryProperty::ProducerId, factoryInfo->ProducerId);//您在控制台创建的 Group ID
  onsFactoryInfo.setFactoryProperty(ons::ONSFactoryProperty::NAMESRV_ADDR, factoryInfo->NAMESRV_ADDR); //设置 TCP 接入域名，进入控制台的实例管理页面的“获取接入点信息”区域查看
  onsFactoryInfo.setFactoryProperty(ons::ONSFactoryProperty::AccessKey, factoryInfo->AccessKey);//阿里云身份验证，在阿里云服务器管理控制台创建
  onsFactoryInfo.setFactoryProperty(ons::ONSFactoryProperty::SecretKey, factoryInfo->SecretKey);//阿里云身份验证，在阿里云服务器管理控制台创建
  // create producer;
  try {
    ons::Producer *pProducer = ons::ONSFactory::getInstance()->createProducer(onsFactoryInfo);
    ONSProducer *producer = (ONSProducer *)malloc(sizeof(ONSProducer));
    if (producer == NULL) {
      pProducer->shutdown();
      return NULL;
    }
    producer->pProducer = pProducer;
    return producer;
  } catch (ons::ONSClientException &e) {
    // TODO: return errors
    return NULL;
  }
}

int DestroyONSProducer(ONSProducer* producer) {
  if (producer->pProducer != NULL) {
    producer->pProducer->shutdown();
    producer->pProducer = NULL;
  }
  free(producer);
  return OK;
}

int StartONSProducer(ONSProducer* producer) {
  producer->pProducer->start();
  return OK;
}

int ShutdownONSProducer(ONSProducer* producer) {
  producer->pProducer->shutdown();
  producer->pProducer = NULL;
  return OK;
}

int SendONSMessageSync(ONSProducer* producer, ONSMessage* msg, CSendResult* result) {
  if (producer == NULL || producer->pProducer == NULL) {
    return NULL_POINTER;
  }

  ons::Message *onsMsg = (ons::Message *)msg;

  const std::map<std::string, std::string> props = onsMsg->getSystemProperties();
  for (std::map<std::string, std::string>::const_iterator it = props.begin(); it != props.end(); ++it) {
    std::cout << "props: " << it->first << "=" << it->second << "\n";
  }

  // 发送消息，只要不抛出异常，就代表发送成功
  try
  {
    ons::SendResultONS sendResult = producer->pProducer->send(*onsMsg);
    strcpy(result->msgId, sendResult.getMessageId());
    result->sendStatus = E_SEND_OK;
  }
  catch(ons::ONSClientException & e)
  {
    result->sendStatus = CSendStatus(e.GetError());
    return PRODUCER_SEND_SYNC_FAILED;
  }

  return OK;
}
