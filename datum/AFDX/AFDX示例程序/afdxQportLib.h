#ifndef AFDXPORTLIB_H_
#define AFDXPORTLIB_H_
#include "Windows.h"
#include "afdxcfgRec.h"
#include "pci_drv.h"
#include "stdio.h"
/******************************
*端口控制块：                 * 
*主要定义端口配置：其中有：   *
*         es地址              *
*         端口配置            *
*         源ip地址            *
*         目的ip地址          *
*         源udp端口号         *
*         目的udp端口号       *
*         源MAC地址           *
*         目的MAC地址         *
*         读指针              *
*         写指针              *
*         缓冲区长度          *
*         端口缓冲            *
******************************/
typedef struct{
	/*AFDXPCI_HANDLE  devHandle;*/
	unsigned int esobj_addr;
    portCfg         pCfg;/*指向端口的配置*/
    unsigned long   srcIP;/*源ip地址*/
    unsigned long   dstIP;/*目的ip地址*/
    unsigned short  srcUDPport;/*源udp端口号*/
    unsigned short  dstUDPport;/*目的udp端口号*/
    unsigned int    phyVLID;/*vlID*/
    char            srcMac[8];/**/
    char            dstMac[8];/**/    
	unsigned int        pW;/*读指针*/
	unsigned int        pR;/*写指针*/	
	unsigned int bufLen;/*缓冲区长度，包括数据长度的4个字节和消息时间戳的4个字节*/
	char *portBuf;
}PortCtl;

/***************************************
*端口控制对象：                            * 
*主要定义有：                          *
*         端口控制块地址               *
*         端口是否已经创建的标志       *
****************************************/
typedef struct{    
    PortCtl          pCTL;/*端口控制块地址*/	
    unsigned int     created_flag;/*是否已经创建的标志*/
}PortObjCtl;

/***************************************
*端口控制对象表：                      * 
*主要定义有：                          *
*         端口控制对象地址             *
*         端口数目                     *
****************************************/
typedef struct{
    PortObjCtl *portObjs;
    unsigned int portNum;
}PortObjTab;

/***************************************
*虚链路对象表：                        * 
*主要定义有：                          *
*         虚链路配置地址               *
*         虚链路数目                   *
****************************************/
typedef struct{

    SendVLCfg *SndVL;
    unsigned int SndVLNum;

    RecVLCfg *RcvVL;
    unsigned int RcvVLNum;
	
}VLObjTab;



	

/***************************************
*ES控制对象：                          * 
*主要定义有：                          *
*         名称                         *
*         esID                         *
*         域ID                         *
*         边ID                         *
*         位置ID                       *
*         MAC地址1                     *
*         MAC地址2                     *
*         设备ID                       *
*         网络ID                       *
  .........
****************************************/
typedef struct
{   
   unsigned int esCfgNum;
   char name[32];
   char esUniqueId;
   char DomainId;/*netWorkid=0x00000000+domainId*/
   char SideId;
   char LocationId;/*设备id=sideId<<0x5+locationId*/


   
   char AFDXMAC1[6];
   char AFDXMAC2[6];
   char AFDXdevId;
   char AFDXnetWorkId;
   unsigned short uid;        /* base for unique IP packet ID */
   unsigned long srcIPConstant;

   AFDXPCI_HANDLE  devHandle;
   unsigned int AFDXDRAMBASE;

   VLObjTab   AFDX_VL_CFG;


   PortObjTab AFDXSndPortTab;
   PortObjTab AFDXRcvPortTab;
      
   HANDLE g_hReciveEventArray;
   HANDLE g_hSendEventArray;
   HANDLE afdxDrvSndTaskId;
   HANDLE afdxDrvRcvTaskId;
   CRITICAL_SECTION Critical_Queue_Snd;
   CRITICAL_SECTION Critical_Queue_Rcv;
   CRITICAL_SECTION Critical_Queue_Creat;
}ESObjCtl;

/***************************************
*ES控制对象表：                        * 
*主要定义有：                          *
*         ES控制对象地址               *
*         ES数目                       *
****************************************/
typedef struct{
    ESObjCtl *ESObjs;
    unsigned int ESNum;
}ESObjTab;

extern ESObjTab AFDX_ES_TAB;

/***************************************
*ES控制对象表：                        * 
*主要定义有：                          *
*         ES控制对象地址               *
*         ES数目                       *
****************************************/
typedef struct{
    unsigned int portid;
    int channelid;
	int len;/*包含用户数据以及4字节的ip 4字节的udp*/
	char portBuf[8192];
}ARINCSAPPORTCtl;

#endif /*AFDXPORTLIB_H_*/
