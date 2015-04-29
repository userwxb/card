/*=====================================================================
//--------------File - AEC429D6_lib.h------------------
//
//-------Library for accessing the AEC429-PCI/S6 cards--
// 
//------Astro Explorer China InC.  http://www.senfetech.com--------
//
//-----  Author:Steven Ren    DATE:2010-10-19    -------
// 
//====================================================================*/

#ifndef _AEC429D6_LIB_H_
#define _AEC429D6_LIB_H_

#define BOOL			STATUS
#define TRUE			1
#define FALSE			0

#define BYTE unsigned char
#define WORD unsigned short
#define DWORD unsigned long
#define HANDLE unsigned long


#define FIFOEMPTY      0x0001
#define FIFOFULL       0x0002
#define FIFOTriggered  0x0004

/* Self structure definition */

typedef struct
{
	BYTE RBaudSel;
	BYTE RWLSel;	
}RXCFGWORD_STRUCT, *pRXCFGWORD_STRUCT;

typedef struct
{
	BYTE TBaudSel;
	BYTE TWLSel;
	BOOL TParityEn;
	BYTE TParitySel;
	BOOL SelfTest;
}TXCFGWORD_STRUCT, *pTXCFGWORD_STRUCT;

typedef struct
{
	BYTE BusType;
	WORD CardType;
	BYTE RChannelNumber;
	BYTE TChannelNumber;
}CARDTYPE_STRUCT, *pCARDTYPE_STRUCT;


/*******************
+++�򿪺͹رհ忨
*******************/

BOOL AEC429D6_Open (HANDLE *phAEC429D6, BYTE CardId);

BOOL AEC429D6_Close (HANDLE hAEC429D6);

/**********
+++ ��λ
**********/

/* �忨��λ */
BOOL AEC429D6_Reset (HANDLE hAEC429D6);

/* ����FIFO��λ */
BOOL AEC429D6_ResetRxFIFO (HANDLE hAEC429D6, BYTE ChanNo);

/* ����FIFO��λ */
BOOL AEC429D6_ResetTxFIFO (HANDLE hAEC429D6, BYTE ChanNo);

/*******************
+++ �忨��ʼ��
*******************/

/* �����ж����μĴ��� */
void AEC429D6_SetIntMaskReg (HANDLE hAEC429D6, BOOL IntEnable);

/* ���ý��������֣������ְ�������λ���ȡ������� */
BOOL AEC429D6_SetRxCfgWord (HANDLE hAEC429D6, BYTE ChanNo, pRXCFGWORD_STRUCT CfgWord);

/* ���÷��������֣������ְ�������λ���ȡ������ʡ���żУ������ */
BOOL AEC429D6_SetTxCfgWord (HANDLE hAEC429D6, BYTE ChanNo, pTXCFGWORD_STRUCT CfgWord);

/* 429������ת��ʹ�� */
void AEC429D6_WordConvertEn (HANDLE hAEC429D6, BOOL Enable);

/* ���ý��մ�����ȼĴ��� */
BOOL AEC429D6_SetTriggerDepth (HANDLE hAEC429D6, BYTE ChanNo, WORD Depth);

/* ���ý��ձ�ż�SD���˹��� */
BOOL AEC429D6_SetLabelFilter (HANDLE hAEC429D6, BYTE ChanNo, BYTE FilterAry[4][256]);

BOOL AEC429D6_StartLabelFilter (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* ���ý���ʱ���ǩ���� */
BOOL AEC429D6_AddTimeTag (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

void AEC429D6_StartTimeTag (HANDLE hAEC429D6, BOOL Enable);

/* ���ö�ʱ����ģʽ */
BOOL AEC429D6_EnableTimerMode (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* �ڴ���ʹ�� */
BOOL AEC429D6_InnerTriggerEnable (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* �����ڴ������� */
BOOL AEC429D6_SetInnerTriggerPeriod (HANDLE hAEC429D6, BYTE ChanNo, WORD Period);

/* �ⴥ��ʹ�� */
BOOL AEC429D6_ExternalTriggerEnable (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* �������ⴥ���ӳ�ʱ�� */
BOOL AEC429D6_SetDelayTime (HANDLE hAEC429D6, BYTE ChanNo, WORD Time);

/* �������ⴥ������ѡ�� */
BOOL AEC429D6_SetTriggerLevel (HANDLE hAEC429D6, BYTE ChanNo, BOOL FallEdge, BOOL RiseEdge);

/* �������ⴥ��429�ּ��� */
BOOL AEC429D6_SetWordInterval (HANDLE hAEC429D6, BYTE ChanNo, WORD WordInterval);

/* �������ⴥ�����ݷ��ʹ��� */
BOOL AEC429D6_NumToSend (HANDLE hAEC429D6, BYTE ChanNo, WORD Num);

/* �������ⴥ��ʱ���͵������� */
BOOL AEC429D6_TriggerCnt (HANDLE hAEC429D6, BYTE ChanNo, WORD Count);

/***************
++++��������
***************/

/* ��ȡ����FIFO��״̬ */
WORD AEC429D6_RxFIFOSTR (HANDLE hAEC429D6, BYTE ChanNo);

/* ��ȡ����FIFO��������� */
DWORD AEC429D6_RxLen (HANDLE hAEC429D6, BYTE ChanNo);

/* ���ݵĽ��� */
void AEC429D6_RxRead (HANDLE hAEC429D6, BYTE ChanNo, WORD RxLen, DWORD *RxBuf, WORD *nResult);

/* ��ʼ��ֹͣ���ݽ��� */
BOOL AEC429D6_Rx_Start (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/***************
++++��������
***************/

/* ��ȡ����FIFO��״̬ */
WORD AEC429D6_TxFIFOSTR (HANDLE hAEC429D6, BYTE ChanNo);

/* ��ȡ����FIFO��������� */
DWORD AEC429D6_TxLen (HANDLE hAEC429D6, BYTE ChanNo);

/* �������� */
void AEC429D6_TxWrite (HANDLE hAEC429D6, BYTE ChanNo, WORD TxLen, DWORD *TxBuf, WORD *nResult);

/* ��ʼ��ֹͣ���� */
BOOL AEC429D6_TxStart (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* ��ȡ�忨�ͺ� */
void AEC429D6_GetCardType (HANDLE hAEC429D6, pCARDTYPE_STRUCT Type);

/* ��ȡ�忨���к� */
DWORD AEC429D6_GetCardSN (HANDLE hAEC429D6);



#ifdef __cplusplus
}
#endif

#endif
