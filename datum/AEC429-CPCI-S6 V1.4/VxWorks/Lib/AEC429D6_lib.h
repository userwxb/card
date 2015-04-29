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
+++打开和关闭板卡
*******************/

BOOL AEC429D6_Open (HANDLE *phAEC429D6, BYTE CardId);

BOOL AEC429D6_Close (HANDLE hAEC429D6);

/**********
+++ 复位
**********/

/* 板卡复位 */
BOOL AEC429D6_Reset (HANDLE hAEC429D6);

/* 接收FIFO复位 */
BOOL AEC429D6_ResetRxFIFO (HANDLE hAEC429D6, BYTE ChanNo);

/* 发送FIFO复位 */
BOOL AEC429D6_ResetTxFIFO (HANDLE hAEC429D6, BYTE ChanNo);

/*******************
+++ 板卡初始化
*******************/

/* 设置中断屏蔽寄存器 */
void AEC429D6_SetIntMaskReg (HANDLE hAEC429D6, BOOL IntEnable);

/* 设置接收配置字，配置字包含数据位长度、波特率 */
BOOL AEC429D6_SetRxCfgWord (HANDLE hAEC429D6, BYTE ChanNo, pRXCFGWORD_STRUCT CfgWord);

/* 设置发送配置字，配置字包含数据位长度、波特率、奇偶校验设置 */
BOOL AEC429D6_SetTxCfgWord (HANDLE hAEC429D6, BYTE ChanNo, pTXCFGWORD_STRUCT CfgWord);

/* 429数据字转换使能 */
void AEC429D6_WordConvertEn (HANDLE hAEC429D6, BOOL Enable);

/* 设置接收触发深度寄存器 */
BOOL AEC429D6_SetTriggerDepth (HANDLE hAEC429D6, BYTE ChanNo, WORD Depth);

/* 设置接收标号及SD过滤功能 */
BOOL AEC429D6_SetLabelFilter (HANDLE hAEC429D6, BYTE ChanNo, BYTE FilterAry[4][256]);

BOOL AEC429D6_StartLabelFilter (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* 设置接收时间标签功能 */
BOOL AEC429D6_AddTimeTag (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

void AEC429D6_StartTimeTag (HANDLE hAEC429D6, BOOL Enable);

/* 设置定时发送模式 */
BOOL AEC429D6_EnableTimerMode (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* 内触发使能 */
BOOL AEC429D6_InnerTriggerEnable (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* 设置内触发周期 */
BOOL AEC429D6_SetInnerTriggerPeriod (HANDLE hAEC429D6, BYTE ChanNo, WORD Period);

/* 外触发使能 */
BOOL AEC429D6_ExternalTriggerEnable (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* 设置内外触发延迟时间 */
BOOL AEC429D6_SetDelayTime (HANDLE hAEC429D6, BYTE ChanNo, WORD Time);

/* 设置内外触发边沿选择 */
BOOL AEC429D6_SetTriggerLevel (HANDLE hAEC429D6, BYTE ChanNo, BOOL FallEdge, BOOL RiseEdge);

/* 设置内外触发429字间间隔 */
BOOL AEC429D6_SetWordInterval (HANDLE hAEC429D6, BYTE ChanNo, WORD WordInterval);

/* 设置内外触发数据发送次数 */
BOOL AEC429D6_NumToSend (HANDLE hAEC429D6, BYTE ChanNo, WORD Num);

/* 设置内外触发时发送的数据量 */
BOOL AEC429D6_TriggerCnt (HANDLE hAEC429D6, BYTE ChanNo, WORD Count);

/***************
++++接收数据
***************/

/* 读取接收FIFO的状态 */
WORD AEC429D6_RxFIFOSTR (HANDLE hAEC429D6, BYTE ChanNo);

/* 读取接收FIFO里的数据量 */
DWORD AEC429D6_RxLen (HANDLE hAEC429D6, BYTE ChanNo);

/* 数据的接收 */
void AEC429D6_RxRead (HANDLE hAEC429D6, BYTE ChanNo, WORD RxLen, DWORD *RxBuf, WORD *nResult);

/* 开始或停止数据接收 */
BOOL AEC429D6_Rx_Start (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/***************
++++发送数据
***************/

/* 读取发送FIFO的状态 */
WORD AEC429D6_TxFIFOSTR (HANDLE hAEC429D6, BYTE ChanNo);

/* 读取发送FIFO里的数据量 */
DWORD AEC429D6_TxLen (HANDLE hAEC429D6, BYTE ChanNo);

/* 发送数据 */
void AEC429D6_TxWrite (HANDLE hAEC429D6, BYTE ChanNo, WORD TxLen, DWORD *TxBuf, WORD *nResult);

/* 开始或停止发送 */
BOOL AEC429D6_TxStart (HANDLE hAEC429D6, BYTE ChanNo, BOOL Enable);

/* 获取板卡型号 */
void AEC429D6_GetCardType (HANDLE hAEC429D6, pCARDTYPE_STRUCT Type);

/* 获取板卡序列号 */
DWORD AEC429D6_GetCardSN (HANDLE hAEC429D6);



#ifdef __cplusplus
}
#endif

#endif
