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
+++打开和关闭板卡
*******************/

DLL BOOL __stdcall AEC429D6_Open (HDEVICE *phAEC429D6, BYTE CardId);

DLL BOOL __stdcall AEC429D6_Close (HDEVICE hAEC429D6);

/**********
+++ 复位
**********/

//板卡复位
DLL BOOL __stdcall AEC429D6_Reset (HDEVICE hAEC429D6);

//接收FIFO复位
DLL BOOL __stdcall AEC429D6_ResetRxFIFO (HDEVICE hAEC429D6, BYTE ChanNo);

//发送FIFO复位
DLL BOOL __stdcall AEC429D6_ResetTxFIFO (HDEVICE hAEC429D6, BYTE ChanNo);

/*******************
+++ 板卡初始化
*******************/

//设置中断屏蔽寄存器
DLL void __stdcall AEC429D6_SetIntMaskReg (HDEVICE hAEC429D6, BOOL IntEnable);

//设置中断触发事件
DLL BOOL __stdcall AEC429D6_SetEvent (HDEVICE hAEC429D6, HANDLE hEvent);

//设置接收配置字，配置字包含数据位长度、波特率
DLL BOOL __stdcall AEC429D6_SetRxCfgWord (HDEVICE hAEC429D6, BYTE ChanNo, pRXCFGWORD_STRUCT CfgWord);

//设置发送配置字，配置字包含数据位长度、波特率、奇偶校验设置
DLL BOOL __stdcall AEC429D6_SetTxCfgWord (HDEVICE hAEC429D6, BYTE ChanNo, pTXCFGWORD_STRUCT CfgWord);

//429数据字转换使能
DLL void __stdcall AEC429D6_WordConvertEn (HDEVICE hAEC429D6, BOOL Enable);

//设置接收触发深度寄存器
DLL BOOL __stdcall AEC429D6_SetTriggerDepth (HDEVICE hAEC429D6, BYTE ChanNo, WORD Depth);

//设置接收标号及SD过滤功能
DLL BOOL __stdcall AEC429D6_SetLabelFilter (HDEVICE hAEC429D6, BYTE ChanNo, BYTE FilterAry[4][256]);

DLL BOOL __stdcall AEC429D6_StartLabelFilter (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//设置接收时间标签功能
DLL BOOL __stdcall AEC429D6_AddTimeTag (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

DLL void __stdcall AEC429D6_StartTimeTag (HDEVICE hAEC429D6, BOOL Enable, LPSYSTEMTIME CurSysTime);

//设置定时发送模式
DLL BOOL __stdcall AEC429D6_EnableTimerMode (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//内触发使能
DLL BOOL __stdcall AEC429D6_InnerTriggerEnable (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//设置内触发周期
DLL BOOL __stdcall AEC429D6_SetInnerTriggerPeriod (HDEVICE hAEC429D6, BYTE ChanNo, WORD Period);

//外触发使能
DLL BOOL __stdcall AEC429D6_ExternalTriggerEnable (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//设置内外触发延迟时间
DLL BOOL __stdcall AEC429D6_SetDelayTime (HDEVICE hAEC429D6, BYTE ChanNo, WORD Time);

//设置内外触发边沿选择
DLL BOOL __stdcall AEC429D6_SetTriggerLevel (HDEVICE hAEC429D6, BYTE ChanNo, BOOL FallEdge, BOOL RiseEdge);

//设置内外触发429字间间隔
DLL BOOL __stdcall AEC429D6_SetWordInterval (HDEVICE hAEC429D6, BYTE ChanNo, WORD WordInterval);

//设置内外触发数据发送次数
DLL BOOL __stdcall AEC429D6_NumToSend (HDEVICE hAEC429D6, BYTE ChanNo, WORD Num);

//设置内外触发时发送的数据量
DLL BOOL __stdcall AEC429D6_TriggerCnt (HDEVICE hAEC429D6, BYTE ChanNo, WORD Count);

/***************
++++接收数据
***************/

//读取接收FIFO的状态
DLL WORD __stdcall AEC429D6_RxFIFOSTR (HDEVICE hAEC429D6, BYTE ChanNo);

//读取接收FIFO里的数据量
DLL DWORD __stdcall AEC429D6_RxLen (HDEVICE hAEC429D6, BYTE ChanNo);

//数据的接收
DLL void __stdcall AEC429D6_RxRead (HDEVICE hAEC429D6, BYTE ChanNo, WORD RxLen, DWORD *RxBuf, WORD *nResult);

//开始或停止数据接收
DLL BOOL __stdcall AEC429D6_Rx_Start (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

/***************
++++发送数据
***************/

//读取发送FIFO的状态
DLL WORD __stdcall AEC429D6_TxFIFOSTR (HDEVICE hAEC429D6, BYTE ChanNo);

//读取发送FIFO里的数据量
DLL DWORD __stdcall AEC429D6_TxLen (HDEVICE hAEC429D6, BYTE ChanNo);

//发送数据
DLL void __stdcall AEC429D6_TxWrite (HDEVICE hAEC429D6, BYTE ChanNo, WORD TxLen, DWORD *TxBuf, WORD *nResult);

//开始或停止发送
DLL BOOL __stdcall AEC429D6_TxStart (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);

//获取板卡型号
DLL void __stdcall AEC429D6_GetCardType (HDEVICE hAEC429D6, pCARDTYPE_STRUCT Type);

//获取板卡序列号
DLL DWORD __stdcall AEC429D6_GetCardSN (HDEVICE hAEC429D6);


#ifdef __cplusplus
}
#endif

#endif
