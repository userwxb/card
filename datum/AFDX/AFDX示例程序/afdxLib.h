#ifndef AFDXLIB_H_
#define AFDXLIB_H_


#include "afdxCfgRec.h"
#include "vclib.h"

/*加载配置*/
int loadCfg(ESCfg  *escfg, unsigned int esNum);

unsigned int ReverseUInt(unsigned int a);
unsigned int ReverseUShort(unsigned int a);

/**/
unsigned int afdxPortLibInit();
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


unsigned int afdxSAPPortRcvMsg( 
             unsigned int  portid,
             char *data,
             unsigned int *datalen,/*输入输出参数*/
			       unsigned int  *ip_src,
             unsigned short *udp_src
);


unsigned int afdxSAPPortSndMsg(              
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

unsigned int afdxComPortRcvMsg(
			 unsigned int portid, 
			 char *data, 
			 unsigned int *datalen, 
			 unsigned int *RefreshFlag, 
			 int *timeStamp
);

unsigned int afdxComPortSndMsg(
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

unsigned long inet_addr_afdx(char * str);

typedef int (*AFDXFUNCPTR)(unsigned short udp,unsigned long ip,unsigned short vl );


#endif /*AFDXLIB_H_*/
