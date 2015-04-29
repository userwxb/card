#ifndef AFDXPORTLIB_H_
#define AFDXPORTLIB_H_
#include "Windows.h"
#include "afdxcfgRec.h"
#include "pci_drv.h"
#include "stdio.h"
/******************************
*�˿ڿ��ƿ飺                 * 
*��Ҫ����˿����ã������У�   *
*         es��ַ              *
*         �˿�����            *
*         Դip��ַ            *
*         Ŀ��ip��ַ          *
*         Դudp�˿ں�         *
*         Ŀ��udp�˿ں�       *
*         ԴMAC��ַ           *
*         Ŀ��MAC��ַ         *
*         ��ָ��              *
*         дָ��              *
*         ����������          *
*         �˿ڻ���            *
******************************/
typedef struct{
	/*AFDXPCI_HANDLE  devHandle;*/
	unsigned int esobj_addr;
    portCfg         pCfg;/*ָ��˿ڵ�����*/
    unsigned long   srcIP;/*Դip��ַ*/
    unsigned long   dstIP;/*Ŀ��ip��ַ*/
    unsigned short  srcUDPport;/*Դudp�˿ں�*/
    unsigned short  dstUDPport;/*Ŀ��udp�˿ں�*/
    unsigned int    phyVLID;/*vlID*/
    char            srcMac[8];/**/
    char            dstMac[8];/**/    
	unsigned int        pW;/*��ָ��*/
	unsigned int        pR;/*дָ��*/	
	unsigned int bufLen;/*���������ȣ��������ݳ��ȵ�4���ֽں���Ϣʱ�����4���ֽ�*/
	char *portBuf;
}PortCtl;

/***************************************
*�˿ڿ��ƶ���                            * 
*��Ҫ�����У�                          *
*         �˿ڿ��ƿ��ַ               *
*         �˿��Ƿ��Ѿ������ı�־       *
****************************************/
typedef struct{    
    PortCtl          pCTL;/*�˿ڿ��ƿ��ַ*/	
    unsigned int     created_flag;/*�Ƿ��Ѿ������ı�־*/
}PortObjCtl;

/***************************************
*�˿ڿ��ƶ����                      * 
*��Ҫ�����У�                          *
*         �˿ڿ��ƶ����ַ             *
*         �˿���Ŀ                     *
****************************************/
typedef struct{
    PortObjCtl *portObjs;
    unsigned int portNum;
}PortObjTab;

/***************************************
*����·�����                        * 
*��Ҫ�����У�                          *
*         ����·���õ�ַ               *
*         ����·��Ŀ                   *
****************************************/
typedef struct{

    SendVLCfg *SndVL;
    unsigned int SndVLNum;

    RecVLCfg *RcvVL;
    unsigned int RcvVLNum;
	
}VLObjTab;



	

/***************************************
*ES���ƶ���                          * 
*��Ҫ�����У�                          *
*         ����                         *
*         esID                         *
*         ��ID                         *
*         ��ID                         *
*         λ��ID                       *
*         MAC��ַ1                     *
*         MAC��ַ2                     *
*         �豸ID                       *
*         ����ID                       *
  .........
****************************************/
typedef struct
{   
   unsigned int esCfgNum;
   char name[32];
   char esUniqueId;
   char DomainId;/*netWorkid=0x00000000+domainId*/
   char SideId;
   char LocationId;/*�豸id=sideId<<0x5+locationId*/


   
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
*ES���ƶ����                        * 
*��Ҫ�����У�                          *
*         ES���ƶ����ַ               *
*         ES��Ŀ                       *
****************************************/
typedef struct{
    ESObjCtl *ESObjs;
    unsigned int ESNum;
}ESObjTab;

extern ESObjTab AFDX_ES_TAB;

/***************************************
*ES���ƶ����                        * 
*��Ҫ�����У�                          *
*         ES���ƶ����ַ               *
*         ES��Ŀ                       *
****************************************/
typedef struct{
    unsigned int portid;
    int channelid;
	int len;/*�����û������Լ�4�ֽڵ�ip 4�ֽڵ�udp*/
	char portBuf[8192];
}ARINCSAPPORTCtl;

#endif /*AFDXPORTLIB_H_*/
