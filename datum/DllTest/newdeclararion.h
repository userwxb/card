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


/*  定义端口模式类型 */
typedef enum { 
	AFDX_SAMPLING = 0, 
	AFDX_QUEUING  = 1,
	AFDX_SAP      = 2
}portModeType;


/*
AFDX配置文件，主要包括ES配置、端口配置、VL配置
*/

/* 分区配置 */
typedef struct{
    char name[32];
    unsigned short ESId;  /*由domainId、SideId和LocationId
                            按照协议组成*/
    char PartionId;       /*5位二进制代码*/    
    char unused;          /*保证四字节对齐*/    
}ES_PARTIONCfg;

/*afdx端口配置*/
typedef struct{
   unsigned int      ICDId;             /* ICDid号，全局唯一*/   
   unsigned int      IpSrc;             /*源IP地址*/            
   unsigned int      IpDst;             /*目的IP地址*/
   unsigned short    UdpSrc;            /*源udp号*/
   unsigned short    UdpDst;            /*目的udp号*/
   unsigned short    VLId;              /*虚拟链路ID*/
   unsigned short    SubVlId;           /*子虚拟链路号*/
   unsigned short    PortModeType;      /*端口类型，分为采样，队列和服务访问点三类*/
   unsigned short    UdpNumBufMessage;  /*udp缓冲消息个数，此参数用于队列模式 */
   unsigned short    UdpMaxMessageSize; /*udp缓冲消息最大长度*/
   unsigned short    UdpSamplingRate;   /*udp刷新频率    */
   unsigned int      fragment_flag;     /*分片标志*/     
}portCfg;

/*发送虚拟链路信息	*/
typedef  struct{
   unsigned  short  VLId;      /*VL唯一的ID号*/
   unsigned  short  SubVLNum;  /*子虚拟链路数*/
	 unsigned  short  unused;    /*偏移量*/
   unsigned  short  bag ;      /*带宽分配间隔*/
   unsigned  short  Lmax;      /*最大帧长度*/
   unsigned  short  Lmin;      /*最小帧长度*/
   unsigned  short  netsel;    /*网络选择*/
   unsigned  short  jitter;    /*最大允许抖动*/
}SendVLCfg;

/*接收虚拟链路信息*/
typedef  struct{
   unsigned  short  VLId;
	 unsigned  short  SkewMax;   /*偏移量*/
   unsigned  short  bag ;        /*带宽分配间隔*/
   unsigned  short  Lmax;   /*最大帧长度*/
   unsigned  short  Lmin;       /*最小帧长度*/  
   unsigned  char   IcckeckEnable;     /*完整性检测*/
   unsigned  char   RmEnable;        /*冗余管理*/
}RecVLCfg;

/*
对于ping一方：
可以配置多个，相当于可以ping多个目标机，
destIP 是要ping的对方的目的ip地址，
VLId   是发送ping包使用的vl
subVLId 是发送ping包使用的子vl

对于被ping一方：
可以配置多个，相当于可以被多个目标机ping，
destIP 是ping方的源ip地址，
VLId   是发送ping应答包使用的vl
subVLId 是发送ping应答包使用的子vl
*/
typedef struct 
{ 	
 unsigned int destIP;/*ping的目的ip,不包含分区号*/
 unsigned short VLId;/*回显请求或者回显应答使用的vl*/
 unsigned short subVLId; 
}ICMP_ECHO_CFG;

typedef struct 
{
 unsigned int pingInterVal;/*ping 间隔时间ms*/ 	 	
 unsigned int icmp_echo_req_num; 
 ICMP_ECHO_CFG *icmp_echo_req;/*回显请求配置，给管理机使用*/
 unsigned int icmp_echo_rep_num; 
 ICMP_ECHO_CFG *icmp_echo_rep;/*回显应答配置，给被管理者使用*/
}ICMP_ONLINE_CFG;


typedef struct 
{ 	
 unsigned int agentip;/*代理IP*/ 
 unsigned int rcvCommPortCfgid;/*接收afdx端口配置号*/
 unsigned int rcvTrapPortCfgid;/*trap afdx端口配置号*/
 unsigned int sndCommPortCfgid;/*发送afdx端口配置号*/ 
 unsigned short requdp;/*udp: 161,manager send request msg to this udp of the agent */
 unsigned short unused;
}AGENT_CFG;


typedef struct 
{ 	
 unsigned int managerip;/*代理IP*/
 unsigned int rcvInformPortCfgid;/*接收afdx端口配置号*/
 unsigned int rcvInformAckPortCfgid;/*trap afdx端口配置号*/
 unsigned int sndInformPortCfgid;/*接收afdx端口配置号*/
 unsigned int sndInformAckPortCfgid;/*接收afdx端口配置号*/
 unsigned short informackudp;/* 1301,manager send informack to this udp of other mgr*/
 unsigned short informrequdp;/* 1300,manager send informreq to this udp of other mgr*/
 
}OTHER_MANAGER_CFG;



typedef struct 
{ 	
 unsigned int managerip;/*代理IP*/
 unsigned int rcvCommPortCfgid;/*接收afdx端口配置号*/
 unsigned int sndCommPortCfgid;/*发送afdx端口配置号*/ 
 unsigned int sndTrapPortCfgid;/*trap afdx端口配置号*/ 
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

/*mode 1是服务器
       0是客户端
*/
typedef struct{
 unsigned short enable;/*使能标志*/
 unsigned short netsel;/*网络选择*/
 unsigned short intervalTime;/*发送周期*/
 unsigned short VLID; 
}RTC_SERVER_CFG;



typedef struct{ 
 unsigned short enable;/*使能标志*/
 unsigned short VLID; 
}RTC_CLIENT_CFG;

typedef struct{
 RTC_SERVER_CFG rtc_server;
 RTC_CLIENT_CFG rtc_client[2];
}RTC_CFG;

/*ES配置*/
/*
MAC1 {0X2,0X0,0X0,0x00000000+domainId,sideId<<0x5+locationId,0X20}
MAC2 {0X2,0X0,0X0,0x00000000+domainId,sideId<<0x5+locationId,0X40}
*/
typedef struct{
	  unsigned short esCfgNum;/*es 配置编号*/
	  unsigned short unused0;
	  unsigned int   cfgLen;
	  unsigned int   version;
    char name[32];   /*端系统名称*/
    char domainId;   /*4位二进制代码 */ 
    char SideId;     /*3位二进制代码*/
    char LocationId;  /*5位二进制代码*/
    
    char unused;      /*保证四字节对齐*/
    
    /*分区配置*/
    unsigned int   partNum;
    ES_PARTIONCfg *partcfg;
    
    /*afdx发送端口配置*/
    unsigned int   SndportNum;        /*发送端口个数*/
    portCfg        *Sndport;
        
    /*afdx接收端口配置*/
    unsigned int   RcvportNum;        /*接收端口个数*/
    portCfg        *Rcvport;
    
    /*发送VL*/
    unsigned int   SndVLNum;        /*发送VL个数*/
    SendVLCfg      *SndVL;
    
    /*接收VL*/
    unsigned int   RcvVLNum;        /*接收VL个数*/
    RecVLCfg      *RcvVL;
    
    ICMP_ONLINE_CFG *icmpCfg;/*icmp配置*/
    
    RTC_CFG  *rtc_cfg;/*RTC配置*/
    
    SNMP_INFO_CFG *snmpCfg;/*snmp配置*/
        
    unsigned int *arinc615aCfg;
    
}ESCfg;

/*加载配置*/
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
             unsigned int *datalen/*输入输出参数*/
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
             unsigned int *datalen,/*输入输出参数*/
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
             unsigned int *datalen,/*输入输出参数*/
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
