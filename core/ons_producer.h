#ifndef __C_ONS_PRODUCER_H__
#define __C_ONS_PRODUCER_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <rocketmq/CSendResult.h>
#include "ons_message.h"

typedef struct ONSFactoryProperty {
  const char *ProducerId;
  const char *NAMESRV_ADDR;
  const char *AccessKey;
  const char *SecretKey;
} ONSFactoryProperty;

typedef struct ONSProducer ONSProducer;

ROCKETMQCLIENT_API ONSProducer* CreateONSProducer(const ONSFactoryProperty* factoryInfo);
ROCKETMQCLIENT_API int DestroyONSProducer(ONSProducer* producer);
ROCKETMQCLIENT_API int StartONSProducer(ONSProducer* producer);
ROCKETMQCLIENT_API int ShutdownONSProducer(ONSProducer* producer);

ROCKETMQCLIENT_API int SendONSMessageSync(ONSProducer* producer, ONSMessage* msg, CSendResult* result);

#ifdef __cplusplus
}
#endif
#endif  //__C_ONS_PRODUCER_H__
