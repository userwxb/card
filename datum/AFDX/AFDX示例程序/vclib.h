 #ifndef _VC_H_
#define _VC_H_

typedef unsigned char BYTE;
#define TRUE  1
#define FALSE 0
#define MALLOC vcAlloc
#define FREE   vcFree

/*
 * 用户消息的最大长度是8K，系统对这个消息要进行分段处理，每个分段消息的最大长度是4K,
 * 然而分段消息中包含消息头是24B，所以分段消息中用户的实际消息长度是4096-24＝4072。
 */
#define USR_MSG_MAX_SIZE    8192
#define SYS_MSG_MAX_SIZE    4000 /*这里用4000而不用4K，是为了和653保持一致*/
#define SYS_HEAP_MAX_NUM    1000
#define SYS_MSG_HEADER_SIZE 24
#define SYS_MSG_USER_SIZE   (SYS_MSG_MAX_SIZE-SYS_MSG_HEADER_SIZE)

/*
 * 系统中VC的接收缓冲区管理分为以下几部分:
 * 在每接收到一包数据后，保存在消息控制块中，每个消息控制块最大保存三包数据，
 * 这是因为用户缓冲最大分为3段消息发送，考虑到多包分段后的消息可能会交错到来，
 * 系统最多保存8个不完整的消息控制块，每接收到一个完整的消息后，就把消息控制
 * 块发送给该消息所属通道的消息队列，激活该通道上挂起的任务。
 */
#define SYS_MAX_CHAN_NUM      100
#define SYS_MAX_CHAN_WAIT_NUM 8

/*653消息段控制头结构*/
typedef struct{
	int         TC_Id;
	int         Channel_Id;
	int         Tag;                  /*表明消息是第几个消息，在发送时由发送端软件填写，
	                                      接收端的数据组合就是靠该值和下一个属性偏移来决定的*/
	int         Offset;               /*表明该消息段是一个完整消息的第几个消息段*/
	int         Cur_Msg_Seg_Length;   /*该段内的有效数据的长度，不包含控制头，实际就是
	                                      Msg_Content里的长度*/
	int         Full_Msg_Length ;     /*该消息段的长度，是指一个完整用户消息的长度*/
} MSG_SEGMENT_HEADER_TYPE;

/*消息段结构*/
typedef struct{
	MSG_SEGMENT_HEADER_TYPE  Msg_Seg_Ctl;    /*该消息段的控制头 */
	unsigned char                    Msg_Content[1]; /*消息段数据       */
} MSG_SEGMENT_TYPE;

typedef struct{
	unsigned char* pBufAddr;
	int  BufLength;
} BUF_CONTROL_BLOCK;

typedef struct{
	BUF_CONTROL_BLOCK BufCtrlBlock[3];
	int tag;
} MSG_CONTROL_BLOCK;

typedef struct{
	int chanid;
	MSG_CONTROL_BLOCK WaitFullMsg[SYS_MAX_CHAN_WAIT_NUM];
} CHAN_RECV_BUF;

#define DIR_SEND 0
#define DIR_RECV 1

typedef struct {
	int chanid;
	int tcid;
	int cfg;
	int dir;
	int res;
} SYS_CHAN_TABLE;

//////////////////////////////////////////////////////////////////////////
void vcInit();
void vcExit();
int AddSysChans(SYS_CHAN_TABLE* pChanTab,int chans);
int DelSysChans(SYS_CHAN_TABLE* pChanTab,int chans);
int CheckVCCfg(SYS_CHAN_TABLE* pCfgData);
SYS_CHAN_TABLE* GetVCCfg(int chanId);
void SendEventHandler(void *p);
void ReceiveEventHandler(BYTE* msgBuffer,int msgLength);
int VcSendMessage(int chanId,BYTE* msgBuffer,int msgLength,int timeOut);
int VcReceiveMessage(int chanId,BYTE* msgBuffer,int* msgLength,int timeOut);
void vcHeapInit();
BYTE* vcAlloc();
int vcFree(BYTE* ptr);
void SwapVcNetData(int* netData,int length);
inline int LONGSWAP(int data);

#endif //_VC_H_
