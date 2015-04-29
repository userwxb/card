//=====================================================================
//--------------File - AEC429D6_lib.h------------------
//
//-------Library for accessing the AEC429-CPCI/PCI-S6 card--
// 
//------Astro Explorer China InC.  http://www.senfetech.com--------
//
//-----  Author:lhjzm         DATE:2010-08-05       ---------------
// 
//=====================================================================

#ifndef _AEC429D6_LIB_H_
#define _AEC429D6_LIB_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DLL __declspec(dllimport)

#pragma comment(lib,"AEC429D6.lib")

#define AEC429D6_FIFOEMPTY      0x0001
#define AEC429D6_FIFOFULL       0x0002
#define AEC429D6_FIFOTriggered  0x0004

//Self structure definition

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

typedef struct
{
	HANDLE hCard;
	BYTE CardId;
}ST_DEVDSC, *HDEVICE;


//DLL Function Declaration

/*******************
+++�򿪺͹رհ忨
*******************/

DLL BOOL __stdcall AEC429D6_Open (HDEVICE *phAEC429D6, BYTE CardId);

DLL BOOL __stdcall AEC429D6_Close (HDEVICE hAEC429D6);

/**********
+++ ��λ
**********/

//�忨��λ
DLL BOOL __stdcall AEC429D6_Reset (HDEVICE hAEC429D6);

//����FIFO��λ
DLL BOOL __stdcall AEC429D6_ResetRxFIFO (HDEVICE hAEC429D6, BYTE ChanNo);

//����FIFO��λ
DLL BOOL __stdcall AEC429D6_ResetTxFIFO (HDEVICE hAEC429D6, BYTE ChanNo);

/*******************
+++ �忨��ʼ��
*******************/

//�����ж����μĴ���
DLL void __stdcall AEC429D6_SetIntMaskReg (HDEVICE hAEC429D6, BOOL IntEnable);

//�����жϴ����¼�
DLL BOOL __stdcall AEC429D6_SetEvent (HDEVICE hAEC429D6, HANDLE hEvent);

//���ý��������֣������ְ�������λ���ȡ�������
DLL BOOL __stdcall AEC429D6_SetRxCfgWord (HDEVICE hAEC429D6, BYTE ChanNo, pRXCFGWORD_STRUCT CfgWord);

//���÷��������֣������ְ�������λ���ȡ������ʡ���żУ������
DLL BOOL __stdcall AEC429D6_SetTxCfgWord (HDEVICE hAEC429D6, BYTE ChanNo, pTXCFGWORD_STRUCT CfgWord);

//429������ת��ʹ��
DLL void __stdcall AEC429D6_WordConvertEn (HDEVICE hAEC429D6, BOOL Enable);

//���ý��մ�����ȼĴ���
DLL BOOL __stdcall AEC429D6_SetTriggerDepth (HDEVICE hAEC429D6, BYTE ChanNo, WORD Depth);

//���ý��ձ�ż�SD���˹���
DLL BOOL __stdcall AEC429D6_SetLabelFilter (HDEVICE hAEC429D6, BYTE ChanNo, BYTE FilterAry[4][256]);

DLL BOOL __stdcall AEC429D6_StartLabelFilter (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//���ý���ʱ���ǩ����
DLL BOOL __stdcall AEC429D6_AddTimeTag (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

DLL void __stdcall AEC429D6_StartTimeTag (HDEVICE hAEC429D6, BOOL Enable, LPSYSTEMTIME CurSysTime);

//���ö�ʱ����ģʽ
DLL BOOL __stdcall AEC429D6_EnableTimerMode (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//�ڴ���ʹ��
DLL BOOL __stdcall AEC429D6_InnerTriggerEnable (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//�����ڴ�������
DLL BOOL __stdcall AEC429D6_SetInnerTriggerPeriod (HDEVICE hAEC429D6, BYTE ChanNo, WORD Period);

//�ⴥ��ʹ��
DLL BOOL __stdcall AEC429D6_ExternalTriggerEnable (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//�������ⴥ���ӳ�ʱ��
DLL BOOL __stdcall AEC429D6_SetDelayTime (HDEVICE hAEC429D6, BYTE ChanNo, WORD Time);

//�������ⴥ������ѡ��
DLL BOOL __stdcall AEC429D6_SetTriggerLevel (HDEVICE hAEC429D6, BYTE ChanNo, BOOL FallEdge, BOOL RiseEdge);

//�������ⴥ��429�ּ���
DLL BOOL __stdcall AEC429D6_SetWordInterval (HDEVICE hAEC429D6, BYTE ChanNo, WORD WordInterval);

//�������ⴥ�����ݷ��ʹ���
DLL BOOL __stdcall AEC429D6_NumToSend (HDEVICE hAEC429D6, BYTE ChanNo, WORD Num);

//�������ⴥ��ʱ���͵�������
DLL BOOL __stdcall AEC429D6_TriggerCnt (HDEVICE hAEC429D6, BYTE ChanNo, WORD Count);

/***************
++++��������
***************/

//��ȡ����FIFO��״̬
DLL WORD __stdcall AEC429D6_RxFIFOSTR (HDEVICE hAEC429D6, BYTE ChanNo);

//��ȡ����FIFO���������
DLL DWORD __stdcall AEC429D6_RxLen (HDEVICE hAEC429D6, BYTE ChanNo);

//���ݵĽ���
DLL void __stdcall AEC429D6_RxRead (HDEVICE hAEC429D6, BYTE ChanNo, WORD RxLen, DWORD *RxBuf, WORD *nResult);

//��ʼ��ֹͣ���ݽ���
DLL BOOL __stdcall AEC429D6_Rx_Start (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

/***************
++++��������
***************/

//��ȡ����FIFO��״̬
DLL WORD __stdcall AEC429D6_TxFIFOSTR (HDEVICE hAEC429D6, BYTE ChanNo);

//��ȡ����FIFO���������
DLL DWORD __stdcall AEC429D6_TxLen (HDEVICE hAEC429D6, BYTE ChanNo);

//��������
DLL void __stdcall AEC429D6_TxWrite (HDEVICE hAEC429D6, BYTE ChanNo, WORD TxLen, DWORD *TxBuf, WORD *nResult);

//��ʼ��ֹͣ����
DLL BOOL __stdcall AEC429D6_TxStart (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//��ȡ�忨�ͺ�
DLL void __stdcall AEC429D6_GetCardType (HDEVICE hAEC429D6, pCARDTYPE_STRUCT Type);

//��ȡ�忨���к�
DLL DWORD __stdcall AEC429D6_GetCardSN (HDEVICE hAEC429D6);


#ifdef __cplusplus
}
#endif

#endif
