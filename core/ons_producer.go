package rocketmq

/*
#cgo LDFLAGS: -L../lib -lonsrocketmq
#include <stdio.h>
#include <stdlib.h>
#include "ons_producer.h"
*/
import "C"
import (
	"errors"
	log "github.com/sirupsen/logrus"
	"unsafe"
)

type onsProducer struct {
	config   *ProducerConfig
	onsproduer *C.struct_ONSProducer
}

func newONSProducer(config *ProducerConfig) (*onsProducer, error) {
	if config == nil {
		return nil, errors.New("config is nil")
	}

	if config.GroupID == "" {
		return nil, errors.New("GroupId is empty")
	}

	if config.NameServer == "" && config.NameServerDomain == "" {
		return nil, errors.New("NameServer and NameServerDomain is empty")
	}

	producer := &onsProducer{config: config}

	var prop C.struct_ONSFactoryProperty
	prop.ProducerId = C.CString(config.GroupID)
	prop.NAMESRV_ADDR = C.CString(config.NameServer)
	if config.Credentials != nil {
	  prop.AccessKey = C.CString(config.Credentials.AccessKey)
		prop.SecretKey = C.CString(config.Credentials.SecretKey)
	} else {
		prop.AccessKey = nil
		prop.SecretKey = nil
	}

	onsproduer := C.CreateONSProducer(&prop)

	C.free(unsafe.Pointer(prop.ProducerId))
	C.free(unsafe.Pointer(prop.NAMESRV_ADDR))
	if config.Credentials != nil {
		C.free(unsafe.Pointer(prop.AccessKey))
		C.free(unsafe.Pointer(prop.SecretKey))
	}

	if onsproduer == nil {
		return nil, errors.New("create Producer failed")
	}

	producer.onsproduer = onsproduer
	return producer, nil
}

func (p *onsProducer) String() string {
	return p.config.String()
}

// Start the producer.
func (p *onsProducer) Start() error {
	err := rmqError(C.StartONSProducer(p.onsproduer))
	if err != NIL {
		return err
	}
	return nil
}

// Shutdown the producer.
func (p *onsProducer) Shutdown() error {
	err := rmqError(C.ShutdownONSProducer(p.onsproduer))

	if err != NIL {
		return err
	}

	err = rmqError(int(C.DestroyONSProducer(p.onsproduer)))
	if err != NIL {
		return err
	}

	return err
}

func (p *onsProducer) SendMessageSync(msg *Message) (*SendResult, error) {
	cmsg := goMsgToONS(msg)
	defer C.DestroyONSMessage(cmsg)

	var sr C.struct__SendResult_
	err := rmqError(C.SendONSMessageSync(p.onsproduer, cmsg, &sr))

	if err != NIL {
		log.Warnf("send message error, error is: %s", err.Error())
		return nil, err
	}

	result := &SendResult{}
	result.Status = SendStatus(sr.sendStatus)
	result.MsgId = C.GoString(&sr.msgId[0])
	result.Offset = int64(sr.offset)
	return result, nil
}

// SendMessageOrderly send the message orderly
func (p *onsProducer) SendMessageOrderly(
		msg *Message,
		selector MessageQueueSelector,
		arg interface{},
		autoRetryTimes int) (*SendResult, error) {
	return nil, errors.New("TODO")
}

// SendMessageOneway send a message with oneway
func (p *onsProducer) SendMessageOneway(msg *Message) error {
	return errors.New("TODO")
}

func (p *onsProducer) SendMessageOrderlyByShardingKey(msg *Message, shardingkey string) (*SendResult, error) {
	return nil, errors.New("TODO")
}
