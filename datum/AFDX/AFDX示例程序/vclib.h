 #ifndef _VC_H_
#define _VC_H_

typedef unsigned char BYTE;
#define TRUE  1
#define FALSE 0
#define MALLOC vcAlloc
#define FREE   vcFree

/*
 * �û���Ϣ����󳤶���8K��ϵͳ�������ϢҪ���зֶδ���ÿ���ֶ���Ϣ����󳤶���4K,
 * Ȼ���ֶ���Ϣ�а�����Ϣͷ��24B�����Էֶ���Ϣ���û���ʵ����Ϣ������4096-24��4072��
 */
#define USR_MSG_MAX_SIZE    8192
#define SYS_MSG_MAX_SIZE    4000 /*������4000������4K����Ϊ�˺�653����һ��*/
#define SYS_HEAP_MAX_NUM    1000
#define SYS_MSG_HEADER_SIZE 24
#define SYS_MSG_USER_SIZE   (SYS_MSG_MAX_SIZE-SYS_MSG_HEADER_SIZE)

/*
 * ϵͳ��VC�Ľ��ջ����������Ϊ���¼�����:
 * ��ÿ���յ�һ�����ݺ󣬱�������Ϣ���ƿ��У�ÿ����Ϣ���ƿ���󱣴��������ݣ�
 * ������Ϊ�û���������Ϊ3����Ϣ���ͣ����ǵ�����ֶκ����Ϣ���ܻύ������
 * ϵͳ��ౣ��8������������Ϣ���ƿ飬ÿ���յ�һ����������Ϣ�󣬾Ͱ���Ϣ����
 * �鷢�͸�����Ϣ����ͨ������Ϣ���У������ͨ���Ϲ��������
 */
#define SYS_MAX_CHAN_NUM      100
#define SYS_MAX_CHAN_WAIT_NUM 8

/*653��Ϣ�ο���ͷ�ṹ*/
typedef struct{
	int         TC_Id;
	int         Channel_Id;
	int         Tag;                  /*������Ϣ�ǵڼ�����Ϣ���ڷ���ʱ�ɷ��Ͷ������д��
	                                      ���ն˵�������Ͼ��ǿ���ֵ����һ������ƫ����������*/
	int         Offset;               /*��������Ϣ����һ��������Ϣ�ĵڼ�����Ϣ��*/
	int         Cur_Msg_Seg_Length;   /*�ö��ڵ���Ч���ݵĳ��ȣ�����������ͷ��ʵ�ʾ���
	                                      Msg_Content��ĳ���*/
	int         Full_Msg_Length ;     /*����Ϣ�εĳ��ȣ���ָһ�������û���Ϣ�ĳ���*/
} MSG_SEGMENT_HEADER_TYPE;

/*��Ϣ�νṹ*/
typedef struct{
	MSG_SEGMENT_HEADER_TYPE  Msg_Seg_Ctl;    /*����Ϣ�εĿ���ͷ */
	unsigned char                    Msg_Content[1]; /*��Ϣ������       */
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
