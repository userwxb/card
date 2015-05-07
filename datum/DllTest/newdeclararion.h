#ifndef AFDXLIB_H_
#define AFDXLIB_H_


#ifdef __cplusplus
extern "C" {
#endif



#define MAX_AFDX_SND_PORT_NUM 128
#define MAX_AFDX_RCV_PORT_NUM 128
#define MAX_AFDX_VL_NUM 128
#define MAX_AFDX_ES_NUM 2


typedef enum{
    AFDX_SOURCE=0,
	  AFDX_DESTINATION=1
}portDirectionType;


/*  ����˿�ģʽ���� */
typedef enum { 
	AFDX_SAMPLING = 0, 
	AFDX_QUEUING  = 1,
	AFDX_SAP      = 2
}portModeType;


/*
AFDX�����ļ�����Ҫ����ES���á��˿����á�VL����
*/

/* �������� */
typedef struct{
    char name[32];
    unsigned short ESId;  /*��domainId��SideId��LocationId
                            ����Э�����*/
    char PartionId;       /*5λ�����ƴ���*/    
    char unused;          /*��֤���ֽڶ���*/    
}ES_PARTIONCfg;

/*afdx�˿�����*/
typedef struct{
   unsigned int      ICDId;             /* ICDid�ţ�ȫ��Ψһ*/   
   unsigned int      IpSrc;             /*ԴIP��ַ*/            
   unsigned int      IpDst;             /*Ŀ��IP��ַ*/
   unsigned short    UdpSrc;            /*Դudp��*/
   unsigned short    UdpDst;            /*Ŀ��udp��*/
   unsigned short    VLId;              /*������·ID*/
   unsigned short    SubVlId;           /*��������·��*/
   unsigned short    PortModeType;      /*�˿����ͣ���Ϊ���������кͷ�����ʵ�����*/
   unsigned short    UdpNumBufMessage;  /*udp������Ϣ�������˲������ڶ���ģʽ */
   unsigned short    UdpMaxMessageSize; /*udp������Ϣ��󳤶�*/
   unsigned short    UdpSamplingRate;   /*udpˢ��Ƶ��    */
   unsigned int      fragment_flag;     /*��Ƭ��־*/     
}portCfg;

/*����������·��Ϣ	*/
typedef  struct{
   unsigned  short  VLId;      /*VLΨһ��ID��*/
   unsigned  short  SubVLNum;  /*��������·��*/
	 unsigned  short  unused;    /*ƫ����*/
   unsigned  short  bag ;      /*���������*/
   unsigned  short  Lmax;      /*���֡����*/
   unsigned  short  Lmin;      /*��С֡����*/
   unsigned  short  netsel;    /*����ѡ��*/
   unsigned  short  jitter;    /*���������*/
}SendVLCfg;

/*����������·��Ϣ*/
typedef  struct{
   unsigned  short  VLId;
	 unsigned  short  SkewMax;   /*ƫ����*/
   unsigned  short  bag ;        /*���������*/
   unsigned  short  Lmax;   /*���֡����*/
   unsigned  short  Lmin;       /*��С֡����*/  
   unsigned  char   IcckeckEnable;     /*�����Լ��*/
   unsigned  char   RmEnable;        /*�������*/
}RecVLCfg;

/*
����pingһ����
�������ö�����൱�ڿ���ping���Ŀ�����
destIP ��Ҫping�ĶԷ���Ŀ��ip��ַ��
VLId   �Ƿ���ping��ʹ�õ�vl
subVLId �Ƿ���ping��ʹ�õ���vl

���ڱ�pingһ����
�������ö�����൱�ڿ��Ա����Ŀ���ping��
destIP ��ping����Դip��ַ��
VLId   �Ƿ���pingӦ���ʹ�õ�vl
subVLId �Ƿ���pingӦ���ʹ�õ���vl
*/
typedef struct 
{ 	
 unsigned int destIP;/*ping��Ŀ��ip,������������*/
 unsigned short VLId;/*����������߻���Ӧ��ʹ�õ�vl*/
 unsigned short subVLId; 
}ICMP_ECHO_CFG;

typedef struct 
{
 unsigned int pingInterVal;/*ping ���ʱ��ms*/ 	 	
 unsigned int icmp_echo_req_num; 
 ICMP_ECHO_CFG *icmp_echo_req;/*�����������ã��������ʹ��*/
 unsigned int icmp_echo_rep_num; 
 ICMP_ECHO_CFG *icmp_echo_rep;/*����Ӧ�����ã�����������ʹ��*/
}ICMP_ONLINE_CFG;


typedef struct 
{ 	
 unsigned int agentip;/*����IP*/ 
 unsigned int rcvCommPortCfgid;/*����afdx�˿����ú�*/
 unsigned int rcvTrapPortCfgid;/*trap afdx�˿����ú�*/
 unsigned int sndCommPortCfgid;/*����afdx�˿����ú�*/ 
 unsigned short requdp;/*udp: 161,manager send request msg to this udp of the agent */
 unsigned short unused;
}AGENT_CFG;


typedef struct 
{ 	
 unsigned int managerip;/*����IP*/
 unsigned int rcvInformPortCfgid;/*����afdx�˿����ú�*/
 unsigned int rcvInformAckPortCfgid;/*trap afdx�˿����ú�*/
 unsigned int sndInformPortCfgid;/*����afdx�˿����ú�*/
 unsigned int sndInformAckPortCfgid;/*����afdx�˿����ú�*/
 unsigned short informackudp;/* 1301,manager send informack to this udp of other mgr*/
 unsigned short informrequdp;/* 1300,manager send informreq to this udp of other mgr*/
 
}OTHER_MANAGER_CFG;



typedef struct 
{ 	
 unsigned int managerip;/*����IP*/
 unsigned int rcvCommPortCfgid;/*����afdx�˿����ú�*/
 unsigned int sndCommPortCfgid;/*����afdx�˿����ú�*/ 
 unsigned int sndTrapPortCfgid;/*trap afdx�˿����ú�*/ 
 unsigned short trapudp;/* 162:agent send trapmsg to this udp of the manager */
 unsigned short ackudp;/* 1200:agent send normal response to this udp of the manager */
}MANAGER_CFG;


typedef struct 
{ 
 unsigned int mode; 
 unsigned int agent_num; 
 AGENT_CFG *agent;/**/
 unsigned int otherManager_num; 
 OTHER_MANAGER_CFG *otherManager;	
 unsigned int manager_num; 
 MANAGER_CFG *manager; 
}SNMP_INFO_CFG;

/*mode 1�Ƿ�����
       0�ǿͻ���
*/
typedef struct{
 unsigned short enable;/*ʹ�ܱ�־*/
 unsigned short netsel;/*����ѡ��*/
 unsigned short intervalTime;/*��������*/
 unsigned short VLID; 
}RTC_SERVER_CFG;



typedef struct{ 
 unsigned short enable;/*ʹ�ܱ�־*/
 unsigned short VLID; 
}RTC_CLIENT_CFG;

typedef struct{
 RTC_SERVER_CFG rtc_server;
 RTC_CLIENT_CFG rtc_client[2];
}RTC_CFG;

/*ES����*/
/*
MAC1 {0X2,0X0,0X0,0x00000000+domainId,sideId<<0x5+locationId,0X20}
MAC2 {0X2,0X0,0X0,0x00000000+domainId,sideId<<0x5+locationId,0X40}
*/
typedef struct{
	  unsigned short esCfgNum;/*es ���ñ��*/
	  unsigned short unused0;
	  unsigned int   cfgLen;
	  unsigned int   version;
    char name[32];   /*��ϵͳ����*/
    char domainId;   /*4λ�����ƴ��� */ 
    char SideId;     /*3λ�����ƴ���*/
    char LocationId;  /*5λ�����ƴ���*/
    
    char unused;      /*��֤���ֽڶ���*/
    
    /*��������*/
    unsigned int   partNum;
    ES_PARTIONCfg *partcfg;
    
    /*afdx���Ͷ˿�����*/
    unsigned int   SndportNum;        /*���Ͷ˿ڸ���*/
    portCfg        *Sndport;
        
    /*afdx���ն˿�����*/
    unsigned int   RcvportNum;        /*���ն˿ڸ���*/
    portCfg        *Rcvport;
    
    /*����VL*/
    unsigned int   SndVLNum;        /*����VL����*/
    SendVLCfg      *SndVL;
    
    /*����VL*/
    unsigned int   RcvVLNum;        /*����VL����*/
    RecVLCfg      *RcvVL;
    
    ICMP_ONLINE_CFG *icmpCfg;/*icmp����*/
    
    RTC_CFG  *rtc_cfg;/*RTC����*/
    
    SNMP_INFO_CFG *snmpCfg;/*snmp����*/
        
    unsigned int *arinc615aCfg;
    
}ESCfg;

/*��������*/
__declspec(dllexport) int __stdcall  loadCfg(ESCfg  *escfg,   unsigned int esNum);



/**/
__declspec(dllexport) unsigned int __stdcall afdxPortLibInit();
unsigned int afdxCreateQPort(
             unsigned int esCfgNum, 
             unsigned int portCfgID,
             unsigned int direction,
             unsigned int  *portid
);

unsigned int afdxGetRcvPortID(
			 unsigned int portid, 
			 unsigned int *esCfgNum,
			 unsigned int *PortModeType,
			 unsigned int *portId_vl
);

unsigned int afdxGetSndPortID(
			 unsigned int portid, 
			 unsigned int *esCfgNum,
			 unsigned int *PortModeType,
			 unsigned int *portId_vl
);

unsigned int afdxQPortRcvMsg( 
             unsigned int  portid,
             char *data,
             unsigned int *datalen/*�����������*/
);


unsigned int afdxQPortSndMsg(              
             unsigned int  portid,
             char *data,
             unsigned int datalen
);

unsigned int afdxCreateSAPPort(
             unsigned int esCfgNum,
             unsigned int portCfgID, 
             unsigned int direction,             
             unsigned int  *portid
);


__declspec(dllexport)  unsigned int __stdcall afdxSAPPortRcvMsg( 
             
             unsigned int  portid,
             char *data,
             unsigned int *datalen,/*�����������*/
			       unsigned int  *ip_src,
             unsigned short *udp_src
);


__declspec(dllexport)  unsigned int __stdcall afdxSAPPortSndMsg(      
                                                               
             unsigned int  portid,
             char *data,
             unsigned int datalen,
			       unsigned int  ip_dst,
             unsigned short udp_dst
);


unsigned int afdxCreateSPort(
             unsigned int esCfgNum,
             unsigned int portCfgID, 
             unsigned int direction,            
             unsigned int  *portid
);

unsigned int afdxSPortSndMsg(              
             unsigned int  portid,
             char *data,
             unsigned int  datalen             
);
unsigned int afdxSPortRcvMsg( 
             unsigned int  portid,
             char *data,
             unsigned int *datalen,/*�����������*/
             int *timeStamp
);

__declspec(dllexport)  unsigned int __stdcall afdxComPortRcvMsg(

			 unsigned int portid, 
			 char *data, 
			 unsigned int *datalen, 
			 unsigned int *RefreshFlag, 
			 int *timeStamp
);

__declspec(dllexport)  unsigned int __stdcall afdxComPortSndMsg(
			 unsigned int portid,
			 char *data,
			 unsigned int datalen
);

unsigned int createARINCSAP(
							SYS_CHAN_TABLE channelcfg,
							unsigned int *arincSAPportid
							);

unsigned int receiveARINCSAP(							
							unsigned int arincSAPportid,
							char *data,
							unsigned *len,
							unsigned int *ipsrc,
							unsigned short *udpsrc,
							int timeout
							); 

unsigned int sendARINCSAP(							
							unsigned int arincSAPportid,
							char *data,
							unsigned len,
							unsigned int ipdst,
							unsigned short udpdst,
							int timeout
							);

unsigned int createARINCQUEUING(
							SYS_CHAN_TABLE channelcfg,
							unsigned int *arincQUEUINGportid
							);

unsigned int sendARINCQUEUING(							
							unsigned int arincQUEUINGportid,
							char *data,
							unsigned len,						
							int timeout
							);


unsigned int receiveARINCQUEUING(							
							unsigned int arincQUEUINGportid,
							char *data,
							unsigned *len,
							int timeout
							);

__declspec(dllexport)  unsigned long __stdcall inet_addr_afdx(char * str);

typedef int (*AFDXFUNCPTR)(unsigned short udp,unsigned long ip,unsigned short vl );



#ifdef __cplusplus
}
#endif


#endif /*AFDXLIB_H_*/
