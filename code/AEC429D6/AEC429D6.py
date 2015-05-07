#!/usr/bin/env python
import os,sys

_p = os.path.dirname(os.path.realpath(__file__))
sys.path.insert(0, os.path.join(_p,'..','lib'))
from base import *


# typedef struct
# {
# 	BYTE RBaudSel;
# 	BYTE RWLSel;	
# }RXCFGWORD_STRUCT, *pRXCFGWORD_STRUCT;
# *pRXCFGWORD_STRUCT:
class RXCFGWORD_STRUCT(Structure):
    _fields_ = [( 'RBaudSel', c_byte ),
                ( 'RWLSel',   c_byte )    
               ]

# typedef struct
# {
# 	BYTE TBaudSel;
# 	BYTE TWLSel;
# 	BOOL TParityEn;
# 	BYTE TParitySel;
# 	BOOL SelfTest;
# }TXCFGWORD_STRUCT, *pTXCFGWORD_STRUCT;
class TXCFGWORD_STRUCT(Structure): # *pTXCFGWORD_STRUCT:
    _fields_ = [( 'TBaudSel',   c_byte ), 
                ( 'TWLSel',     c_byte ), 
                ( 'TParityEn',  c_int  ), 
                ( 'TParitySel', c_byte ), 
                ( 'SelfTest',   c_int  ) 
               ]

# typedef struct
# {
# 	BYTE BusType;
# 	WORD CardType;
# 	BYTE RChannelNumber;
# 	BYTE TChannelNumber;
# }CARDTYPE_STRUCT, *pCARDTYPE_STRUCT;
class CARDTYPE_STRUCT(Structure):# *pCARDTYPE_STRUCT:
    _fields_ = [ ( 'BusType',         c_byte  ),
                 ( 'CardType',        c_ulong ),
                 ( 'RChannelNumber',  c_byte  ),
                 ( 'TChannelNumber',  c_byte  )
               ]

# typedef struct
# {
# 	HANDLE hCard;
# 	BYTE CardId;
# }ST_DEVDSC, *HDEVICE;
class ST_DEVDSC(Structure):# *HDEVICE,:
    _fields_ = [ ( 'hCard',   c_ulong ),
                 ( 'CardId',  c_byte  ) 
               ]

class SYSTEMTIME(Structure):
    _fields_ = [ ( 'wYear',         c_ushort ), 
                 ( 'wMonth',        c_ushort ),
                 ( 'wDayOfWeek',    c_ushort ),
                 ( 'wDay',          c_ushort ),
                 ( 'wHour',         c_ushort ),
                 ( 'wMinute',       c_ushort ),
                 ( 'wSecond',       c_ushort ),
                 ( 'wMilliseconds', c_ushort )
               ]


# wYear Specifies the current year.
# wMonth Specifies the current month; January = 1, February = 2, and so on.
# wDayOfWeek Specifies the current day of the week; Sunday = 0, Monday = 1, and so on.
# wDay Specifies the current day of the month.
# wHour Specifies the current hour.
# wMinute Specifies the current minute.
# wSecond Specifies the current second.
# wMilliseconds Specifies the current millisecond. 

class AEC429D6(Base):
    def __init__(self,module):
        modulepath=os.path.dirname(os.path.realpath(__file__))
        # Call base init function to init the object 
        Base.__init__(self,modulepath,module)
        self.log.info("class %s init" % self.__class__.__name__)
    
    def debuginfo(self,hAEC429D6,info):
        self.log.debug("hDevice: %d,hid: %d,%s" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,info))


    # DLL BOOL __stdcall AEC429D6_Open (HDEVICE *phAEC429D6, BYTE CardId);
    def AEC429D6_Open (self,CardId):
        hAEC429D6= POINTER(ST_DEVDSC)()
        self.capi.AEC429D6_Open.restype=c_int
        retval=self.capi.AEC429D6_Open(byref(hAEC429D6),c_byte(CardId))
        if retval > 0:
            self.debuginfo("Open Card: %d, return value: %d,hDevice: %d,hid: %d" % \
                           (CardId,retval,hAEC429D6.contents.hDevice, hAEC429D6.contents.hid))
            return retval,hAEC429D6
        else:
            return retval,None

    # DLL BOOL __stdcall AEC429D6_Close (HDEVICE hAEC429D6);
    def AEC429D6_Close (self, hAEC429D6):
        self.capi.AEC429D6_Close.restype = c_int
        retval=self.capi.AEC429D6_Close(hAEC429D6)
        self.log.debug("hDevice: %d,hid: %d,return value: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_Reset (HDEVICE hAEC429D6);
    def AEC429D6_Reset (self, hAEC429D6):
        self.capi.AEC429D6_Reset.restype = c_int
        retval=self.capi.AEC429D6_Reset(hAEC429D6)
        self.log.debug("hDevice: %d,hid: %d,return value: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_ResetRxFIFO (HDEVICE hAEC429D6, BYTE ChanNo);
    def AEC429D6_ResetRxFIFO (self, hAEC429D6, ChanNo):
        self.capi.AEC429D6_ResetRxFIFO.restype = c_int
        retval=self.capi.AEC429D6_ResetRxFIFO(hAEC429D6,c_byte(ChanNo))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d return value: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_ResetTxFIFO (HDEVICE hAEC429D6, BYTE ChanNo);
    def AEC429D6_ResetTxFIFO (self, hAEC429D6, ChanNo):
        self.capi.AEC429D6_ResetTxFIFO.restype = c_int
        retval=self.capi.AEC429D6_ResetTxFIFO(hAEC429D6,c_byte(ChanNo))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d return value: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL void __stdcall AEC429D6_SetIntMaskReg (HDEVICE hAEC429D6, BOOL IntEnable);
    def AEC429D6_SetIntMaskReg (self, hAEC429D6, IntEnable):
        self.capi.AEC429D6_SetIntMaskReg(hAEC429D6,c_int(IntEnable))
        self.log.debug("hDevice: %d,hid: %d,IntEnable: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,IntEnable))

    # DLL BOOL __stdcall AEC429D6_SetEvent (HDEVICE hAEC429D6, HANDLE hEvent);
    def AEC429D6_SetEvent (self, hAEC429D6, hEvent):
        self.capi.AEC429D6_SetEvent.restype = c_int
        retval=self.capi.AEC429D6_SetEvent(hAEC429D6,c_ulong(hEvent))
        self.log.debug("hDevice: %d,hid: %d,hEvent: %d return value: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,hEvent,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_SetRxCfgWord (HDEVICE hAEC429D6, BYTE ChanNo, pRXCFGWORD_STRUCT CfgWord);
    def AEC429D6_SetRxCfgWord (self, hAEC429D6, ChanNo, CfgWord):
        self.capi.AEC429D6_SetRxCfgWord.restype = c_int
        retval=self.capi.AEC429D6_SetRxCfgWord(hAEC429D6,c_byte(ChanNo),byref(CfgWord))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,RBaudSel: %d, RWLSel: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,CfgWord.RBaudSel, CfgWord.RWLSel,retval))
        return retval


    # DLL BOOL __stdcall AEC429D6_SetTxCfgWord (HDEVICE hAEC429D6, BYTE ChanNo, pTXCFGWORD_STRUCT CfgWord);
    def AEC429D6_SetTxCfgWord (self, hAEC429D6,ChanNo,CfgWord):
        self.capi.AEC429D6_SetTxCfgWord.restype = c_int
        retval=self.capi.AEC429D6_SetTxCfgWord(hAEC429D6,c_byte(ChanNo),byref(CfgWord))
        self.log.debug(("hDevice: %d,hid: %d,ChanNo: %d,"+ \
                        "TBaudSel: %d, TWLSel: %d,TParityEn: %d,TParity: %d,SelSelfTest: %d, return: %d") % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,\
                       CfgWord.TBaudSel, CfgWord.TWLSel,CfgWord.TParityEn,CfgWord.TParity,CfgWord.SelSelfTest,retval))
        return retval

    # DLL void __stdcall AEC429D6_WordConvertEn (HDEVICE hAEC429D6, BOOL Enable);
    def AEC429D6_WordConvertEn (self, hAEC429D6, Enable):
        self.capi.AEC429D6_WordConvertEn(hAEC429D6,c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,Enable: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,Enable))

    # DLL BOOL __stdcall AEC429D6_SetTriggerDepth (HDEVICE hAEC429D6, BYTE ChanNo, WORD Depth);
    def AEC429D6_SetTriggerDepth (self, hAEC429D6, ChanNo, Depth):
        self.capi.AEC429D6_SetTriggerDepth.restype = c_int
        retval=self.capi.AEC429D6_SetTriggerDepth(hAEC429D6,c_byte(ChanNo),c_ushort(Depth))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Depth: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Depth,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_SetLabelFilter (HDEVICE hAEC429D6, BYTE ChanNo, BYTE FilterAry[4][256]);
    # AEC429D6_SetLabelFilter (hAEC429D6,ChanNo,((c_byte*256)*4)( (),(),(),())):
    def AEC429D6_SetLabelFilter (self, hAEC429D6, ChanNo,FilterAry):
        self.log.debug("The FilterAry Value:" )
        for i in range(4):
            for j in range(256):
                self.log.debug("FilterAry[%d][%d]=%d" % (i,j,FilterAry[i][j]) )
        self.capi.AEC429D6_SetLabelFilter.restype = c_int
        retval=self.capi.AEC429D6_SetLabelFilter(hAEC429D6,c_byte(ChanNo),c_ushort(Depth))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_StartLabelFilter (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_StartLabelFilter (self, hAEC429D6, ChanNo, Enable):
        self.capi.AEC429D6_StartLabelFilter.restype = c_int
        retval=self.capi.AEC429D6_StartLabelFilter(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_AddTimeTag (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_AddTimeTag (self, hAEC429D6, ChanNo, Enable):
        self.capi.AEC429D6_AddTimeTag.restype = c_int
        retval=self.capi.AEC429D6_AddTimeTag(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL void __stdcall AEC429D6_StartTimeTag (HDEVICE hAEC429D6, BOOL Enable, LPSYSTEMTIME CurSysTime);
    def AEC429D6_StartTimeTag (self, hAEC429D6,Enable,CurSysTime):
        self.capi.AEC429D6_StartTimeTag(hAEC429D6,c_int(Enable),byref(CurSysTiem))
        self.log.debug(("hDevice: %d,hid: %d,Enable: %d," + \
                        "wYear: %d,wMonth: %d,wDayOfWeek: %d,wDay: %d," + \
                        "wHour: %d,wMinute: %d,wSecond: %d,wMilliseconds: %d" )% \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,Enable, \
                        CurSysTime.wYear,CurSysTime.wMonth,CurSysTime.wDayOfWeek,CurSysTime.wDay, \
                        CurSysTime.wHour,CurSysTime.wMinute,CurSysTime.wSecond,CurSysTime.wMilliseconds))

    # DLL BOOL __stdcall AEC429D6_EnableTimerMode (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_EnableTimerMode (self, hAEC429D6,ChanNo,Enable):
        self.capi.AEC429D6_EnableTimerMode.restype = c_int
        retval=self.capi.AEC429D6_EnableTimerMode(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_InnerTriggerEnable (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_InnerTriggerEnable (self, hAEC429D6,ChanNo,Enable):
        self.capi.AEC429D6_InnerTriggerEnable.restype = c_int
        retval=self.capi.AEC429D6_InnerTriggerEnable(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_SetInnerTriggerPeriod (HDEVICE hAEC429D6, BYTE ChanNo, WORD Period);
    def AEC429D6_SetInnerTriggerPeriod (self, hAEC429D6, ChanNo, Period):
        self.capi.AEC429D6_SetInnerTriggerPeriod.restype = c_int
        retval=self.capi.AEC429D6_SetInnerTriggerPeriod(hAEC429D6,c_byte(ChanNo),c_ushort(Period))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Period: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Period,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_ExternalTriggerEnable (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_ExternalTriggerEnable (self, hAEC429D6, ChanNo, Enable):
        self.capi.AEC429D6_ExternalTriggerEnable.restype = c_int
        retval=self.capi.AEC429D6_ExternalTriggerEnable(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_SetDelayTime (HDEVICE hAEC429D6, BYTE ChanNo, WORD Time);
    def AEC429D6_SetDelayTime (self, hAEC429D6, ChanNo, Time):
        self.capi.AEC429D6_SetDelayTime.restype = c_int
        retval=self.capi.AEC429D6_SetDelayTime(hAEC429D6,c_byte(ChanNo),c_ushort(Time))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Time: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Time,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_SetTriggerLevel (HDEVICE hAEC429D6, BYTE ChanNo, BOOL FallEdge, BOOL RiseEdge);
    def AEC429D6_SetTriggerLevel (self, hAEC429D6, ChanNo, FallEdge, RiseEdge):
        self.capi.AEC429D6_SetTriggerLevel.restype = c_int
        retval=self.capi.AEC429D6_SetTriggerLevel(hAEC429D6,c_byte(ChanNo),c_int(FallEdge),c_int(RiseEdge))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,FallEdge: %d,RiseEdge: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,FallEdge,RiseEdge,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_SetWordInterval (HDEVICE hAEC429D6, BYTE ChanNo, WORD WordInterval);
    def AEC429D6_SetWordInterval (self, hAEC429D6, ChanNo, WordInterval):
        self.capi.AEC429D6_SetWordInterval.restype = c_int
        retval=self.capi.AEC429D6_SetWordInterval(hAEC429D6,c_byte(ChanNo),c_ushort(WordInterval))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, WordInterval: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,WordInterval,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_NumToSend (HDEVICE hAEC429D6, BYTE ChanNo, WORD Num);
    def AEC429D6_NumToSend (self, hAEC429D6, ChanNo, Num):
        self.capi.AEC429D6_NumToSend.restype = c_int
        retval=self.capi.AEC429D6_NumToSend(hAEC429D6,c_byte(ChanNo),c_ushort(WordInterval))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Num: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Num,retval))
        return retval

    # DLL BOOL __stdcall AEC429D6_TriggerCnt (HDEVICE hAEC429D6, BYTE ChanNo, WORD Count);
    def AEC429D6_TriggerCnt (self, hAEC429D6, ChanNo, Count):
        self.capi.AEC429D6_TriggerCnt.restype = c_int
        retval=self.capi.AEC429D6_TriggerCnt(hAEC429D6,c_byte(ChanNo),c_ushort(Count))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Count: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Count,retval))
        return retval

    # DLL WORD __stdcall AEC429D6_RxFIFOSTR (HDEVICE hAEC429D6, BYTE ChanNo);
    def AEC429D6_RxFIFOSTR (self, hAEC429D6,ChanNo):
        self.capi.AEC429D6_RxFIFOSTR.restype = c_ushort
        retval=self.capi.AEC429D6_RxFIFOSTR(hAEC429D6,c_byte(ChanNo))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL DWORD __stdcall AEC429D6_RxLen (HDEVICE hAEC429D6, BYTE ChanNo);
    def AEC429D6_RxLen (self, hAEC429D6,ChanNo):
        self.capi.AEC429D6_RxLen.restype = c_ulong
        retval=self.capi.AEC429D6_RxLen(hAEC429D6,c_byte(ChanNo))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL void __stdcall AEC429D6_RxRead (HDEVICE hAEC429D6, BYTE ChanNo, WORD RxLen, DWORD *RxBuf, WORD *nResult);
    def AEC429D6_RxRead (self, hAEC429D6, ChanNo, RxLen, RxBuf):
        nResult=c_ushort()
        self.capi.AEC429D6_RxRead(hAEC429D6,c_byte(ChanNo),c_ushort(RxLen),RxBuf,byref(nResult))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,RxLen: %d,nResult: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,RxLen,nResult.value))
        return nResult.value

    # DLL BOOL __stdcall AEC429D6_Rx_Start (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_Rx_Start (self, hAEC429D6, ChanNo, Enable):
        self.capi.AEC429D6_Rx_Start.restype = c_int
        retval=self.capi.AEC429D6_Rx_Start(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL WORD __stdcall AEC429D6_TxFIFOSTR (HDEVICE hAEC429D6, BYTE ChanNo);
    def AEC429D6_TxFIFOSTR (self, hAEC429D6, ChanNo):
        self.capi.AEC429D6_TxFIFOSTR.restype = c_ushort
        retval=self.capi.AEC429D6_TxFIFOSTR(hAEC429D6,c_byte(ChanNo))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL DWORD __stdcall AEC429D6_TxLen (HDEVICE hAEC429D6, BYTE ChanNo);
    def AEC429D6_TxLen (self, hAEC429D6, ChanNo):
        self.capi.AEC429D6_TxLen.restype = c_ulong
        retval=self.capi.AEC429D6_TxLen(hAEC429D6,c_byte(ChanNo))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,retval))
        return retval

    # DLL void __stdcall AEC429D6_TxWrite (HDEVICE hAEC429D6, BYTE ChanNo, WORD TxLen, DWORD *TxBuf, WORD *nResult);
    def AEC429D6_TxWrite (self, hAEC429D6, ChanNo, TxLen, TxBuf):
        nResult=c_ushort()
        self.capi.AEC429D6_TxWrite(hAEC429D6,c_byte(ChanNo),c_ushort(TxLen),TxBuf,byref(nResult))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d,TxLen: %d,nResult: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,TxLen,nResult.value))
        return nResult.value

    # DLL BOOL __stdcall AEC429D6_TxStart (HDEVICE hAEC429D6, BYTE ChanNo, BOOL Enable);
    def AEC429D6_TxStart (self, hAEC429D6, ChanNo, Enable):
        self.capi.AEC429D6_TxStart.restype = c_int
        retval=self.capi.AEC429D6_TxStart(hAEC429D6,c_byte(ChanNo),c_int(Enable))
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,ChanNo,Enable,retval))
        return retval

    # DLL void __stdcall AEC429D6_GetCardType (HDEVICE hAEC429D6, pCARDTYPE_STRUCT Type);
    def AEC429D6_GetCardType (self, hAEC429D6, Type):
        self.capi.AEC429D6_GetCardType(hAEC429D6,byref(Type))
        self.log.debug("hDevice: %d,hid: %d,BusType: %d,CardType: %d,RChannelNumber: %d,TChannelNumber: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,Type.BusType,Type.CardType,\
                        Type.RChannelNumber,Type.TChannelNumber))

    # DLL DWORD __stdcall AEC429D6_GetCardSN (HDEVICE hAEC429D6);
    def AEC429D6_GetCardSN (self, hAEC429D6):
        self.capi.AEC429D6_GetCardSN.c_ulong
        retval=self.capi.AEC429D6_GetCardSN(hAEC429D6)
        self.log.debug("hDevice: %d,hid: %d,ChanNo: %d, Enable: %d,return: %d" % \
                       (hAEC429D6.contents.hDevice, hAEC429D6.contents.hid,retval))
        return retval




if __name__ == "__main__":
    cardid=0 
    TRUE=1
    FLASE=0
    card=AEC429D6("AEC429D6.dll")
    ##
    retval,hDevce=card.AEC429D6_Open(cardid)
    if retval < 1:
        print "open hardware: %d failed" % retval
        exit(1)
    ##
    retval=card.AEC429D6_Reset(hDevce)
    if retval < 1:
        print "Reset card: %d failed" % retval
        exit(1)
    ##
	CardType=CARDTYPE_STRUCT()
    card.AEC429D6_GetCardType(hDevce,CardType)
    ##
    RxCfgWord=RXCFGWORD_STRUCT()
    retval=card.AEC429D6_SetRxCfgWord(hDevce,RxCfgWord)
    if retval < 1:
        print "RX cfg word: %d failed" % retval
        exit(1)    
    ##
    TxCfgWord=TXCFGWORD_STRUCT()
    retval=card.AEC429D6_SetTxCfgWord(hDevce,TxCfgWord)
    if retval < 1:
        print "TX cfg word: %d failed" % retval
        exit(1)        
    ##
    retval=card.AEC429D6_GetCardSN(hDevce)
    ##
    retval=card.AEC429D6_ResetRxFIFO(hDevce,1)
    if retval < 1:
        print "CH 1 Reset RX FIFO %d failed" % retval
        exit(1) 
    ##
    retval=card.AEC429D6_ResetTxFIFO(hDevce,1)
    if retval < 1:
        print "CH 1 Reset TX FIFO %d failed" % retval
        exit(1) 
    ##
    card.AEC429D6_SetIntMaskReg(hDevce,TRUE)
    ##
    card.AEC429D6_RxLen(hDevce,1)
    ##
    card.AEC429D6_TxLen(hDevce,1)
    ##
    card.AEC429D6_WordConvertEn(hDevce,TRUE)
    ##
    retval=card.AEC429D6_Rx_Start(hDevce,1,TRUE)
    if retval < 1:
        print "Start RX channel enable %d failed" % retval
        exit(1)     
    ##
    retval=card.AEC429D6_TxStart(hDevce,1,TRUE)
    if retval < 1:
        print "Start TX channel enable %d failed" % retval
        exit(1)
    ##
    card.AEC429D6_TxFIFOSTR(hDevce,1)
    ##
    card.AEC429D6_RxFIFOSTR(hDevce,1)
    ##
    card.AEC429D6_SetEvent(hDevce,0x12345678)
    ##    
    retval=card.AEC429D6_SetTriggerDepth(hDevce,1,2)
    if retval < 1:
        print "Set RX Trigger Depth %d failed" % retval
        exit(1)
    ##    
    retval=card.AEC429D6_AddTimeTag(hDevce,1,TRUE)
    if retval < 1:
        print "Set timer tag %d failed" % retval
        exit(1)
    ##
    system_time=SYSTEMTIME()
    card.AEC429D6_StartTimeTag(hDevce,TRUE,system_time)
    ##
    # SdLable=[[0 for col in range(256)] for row in range(4)]
    data=[[col for col in range(256)] for row in range(4)]
    SdLable=((c_byte*256)*4)((c_byte*256)(*(data[0]) ),(c_byte*256)(*(data[1]) ),(c_byte*256)(*(data[2]) ),(c_byte*256)(*(data[3]) ) )
    # or
    # SdLable = ((c_byte*256)*4)( (0),(0),(0),(0))
    retval=card.AEC429D6_SetLabelFilter(hDevce, i, SdLable)
    if retval < 1:
        print "Set timer tag %d failed" % retval
        exit(1)
    ##
    retval=card.AEC429D6_StartLabelFilter(hDevce,1,TRUE)
    if retval < 1:
        print "Start Label Filter %d failed" % retval
        exit(1)
    ##
    retval=card.AEC429D6_EnableTimerMode(hDevce,1,TRUE)
    if retval < 1:
        print "Enable timer to send %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_InnerTriggerEnable(hDevce,1,TRUE)
    if retval < 1:
        print "Enable Inner trigger %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_SetInnerTriggerPeriod(hDevce,1,30)
    if retval < 1:
        print "Enable Inner trigger period %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_ExternalTriggerEnable(hDevce,1,FLASE)
    if retval < 1:
        print "Enable External trigger period %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_SetDelayTime(hDevce,1,234)
    if retval < 1:
        print "set inner/exter trigger delay %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_SetTriggerLevel(hDevce,1,0,1)
    if retval < 1:
        print "set inner/exter trigger level type %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_SetWordInterval(hDevce,1,23)
    if retval < 1:
        print "set inner/exter trigger interval time %d failed" % retval
        exit(1)

    ##
    retval=card.AEC429D6_NumToSend(hDevce,1,20)
    if retval < 1:
        print "set inner/exter trigger send times %d failed" % retval
        exit(1)
    ##
    retval=card.AEC429D6_TriggerCnt(hDevce,1,200)
    if retval < 1:
        print "set inner/exter trigger send data number in total %d failed" % retval
        exit(1)
    ##
    # Rx_Buf=[0]*256
    Rx_Buf=(c_ulong*256)(0)
    retval=card.AEC429D6_RxRead(hDevce,1,256,Rx_Buf)
    ##   
    # Tx_Buf=[0]*256
    Tx_Buf=(c_ulong*256)(0)
    retval=card.AEC429D6_TxWrite(hDevce,1,256,Tx_Buf)
    ##
    card.AEC429D6_Close(hDevce)
    
    print "Test Done"




