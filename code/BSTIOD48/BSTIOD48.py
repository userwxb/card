#!/usr/bin/env python

import os,sys

_p = os.path.dirname(os.path.realpath(__file__))
sys.path.insert(0, os.path.join(_p,'..','lib'))

from base import *

# typedef struct
# {
# 	DWORD hwVersion;
# 	DWORD driverVersion;
# 	DWORD libVersion;
# }VERSIONINFO_STRUCT, *pVERSIONINFO_STRUCT;
class VERSIONINFO_STRUCT(Structure):
    _fields_ = [('hwVersion',     c_ulong),
                ('driverVersion', c_ulong), 
                ('libVersion',    c_ulong)
               ]

class BSTIOD48(Base):
    def __init__(self,module):
        modulepath=os.path.dirname(os.path.realpath(__file__))
        
        Base.__init__(self,modulepath,module)
        self.log.info("class %s init" % self.__class__.__name__)

    # DLL BOOL __stdcall BSTIOD48_Open (HANDLE *phDevice, BYTE CardId);
    def BSTIOD48_Open(self,hid):
        handler=c_long()
        self.capi.BSTIOD48_Open.restype = c_int # set function return value type
        retval=self.capi.BSTIOD48_Open(byref(handler),c_ulong(hid))
        # another way to call the c function
        # retval=getattr(self.capi,"BSTIOD48_Open")(byref(handler),c_ulong(hid))
        self.log.debug("open HID: %d,the Handler : %d" % (hid,handler.value))
        return retval,handler.value

    # DLL BOOL __stdcall BSTIOD48_Close (HANDLE hDevice);
    def BSTIOD48_Close (self,hDevice):
        self.capi.BSTIOD48_Close.restype = c_int
        retval=self.capi.BSTIOD48_Close (c_long(hDevice))
        self.log.debug("Handler : %d,return value: %d" % (hDevice,retval))
        return retval

    # DLL DWORD __stdcall BSTIOD48_GetSN (HANDLE hDevice);
    def BSTIOD48_GetSN (self,hDevice):
        self.capi.BSTIOD48_GetSN.restype = c_ulong
        retval=self.capi.BSTIOD48_GetSN(c_long(hDevice))
        self.log.debug("Handler: %d SN: %d" % (hDevice,retval))
        return retval

    # DLL BOOL __stdcall BSTIOD48_Reset (HANDLE hDevice);
    def BSTIOD48_Reset(self,hDevice):
        self.capi.BSTIOD48_Reset.restype = c_int
        retval=self.capi.BSTIOD48_Reset(c_long(hDevice))
        self.log.debug("Handler: %d return value: %d" % (hDevice,retval))
        return retval

    # DLL BOOL __stdcall BSTIOD48_GetVersion (HANDLE hDevice,pVERSIONINFO_STRUCT pVerInf);
    # verinfo should be defined as verinfo=VERSIONINFO_STRUCT()
    # reference the verinfo's member should be verinfo.hwVersion ...
    def BSTIOD48_GetVersion(self,hDevice,verinfo):
        self.capi.BSTIOD48_GetVersion.restype = c_int
        retval=self.capi.BSTIOD48_GetVersion(c_long(hDevice),byref(verinfo))
        self.log.debug("handler: %d,return value: %d,hwVersion: %d driverVersion: %d libVersion: %d" % \
                        (hDevice,retval,verinfo.hwVersion,verinfo.driverVersion,verinfo.libVersion) )
        return retval

    # DLL BOOL __stdcall BSTIOD48_IO_Get_Input_Status_Single (HANDLE hDevice, BYTE ChanNo,BYTE *pStatus);
    # pStatus should be defined as pStatus=c_ubyte() , and reference as pStatus.value
    def BSTIOD48_IO_Get_Input_Status_Single (self,hDevice,ChanNo,pStatus):
        self.capi.BSTIOD48_IO_Get_Input_Status_Single.restype = c_int
        retval=self.capi.BSTIOD48_IO_Get_Input_Status_Single(c_long(hDevice),c_byte(ChanNo),byref(pStatus))
        self.log.debug("handler: %d,ChanNo: %d Status: %d, return value: %d" % \
                        (hDevice,ChanNo,pStatus.value,retval) )
        return retval

    # DLL BOOL __stdcall BSTIOD48_IO_Get_Input_Status_Multi (HANDLE hDevice, DWORD PISR[2]);
    def BSTIOD48_IO_Get_Input_Status_Multi(self,hDevice,PISR):
        isr=c_ulong*2
        self.capi.BSTIOD48_IO_Get_Input_Status_Multi.restype = c_int
        retval=self.capi.BSTIOD48_IO_Get_Input_Status_Multi(c_long(hDevice),isr)
        del PISR[:]
        PISR[:]=isr[:]
        self.log.debug("handler: %d,isr[0]: %d isr[1]: %d, return value: %d" % \
                        ( hDevice,PISR[0],PISR[1],retval) )
        return retval

    # DLL BOOL __stdcall BSTIOD48_Relay_SetStatus_Single (HANDLE hDevice, BYTE ChanNo,BYTE Status);
    def BSTIOD48_Relay_SetStatus_Single (self,hDevice,ChanNo,Status):
        self.capi.BSTIOD48_Relay_SetStatus_Single.restype = c_int
        retval=self.capi.BSTIOD48_Relay_SetStatus_Single(c_long(hDevice),c_ubyte(ChanNo),c_ubyte(Status))
        self.log.debug("handler: %d,ChanNo: %d Status: %d, return value: %d"  % \
                        (hDevice,ChanNo,Status,retval) )
        return retval

    # DLL BOOL __stdcall BSTIOD48_Relay_SetStatus_Multi (HANDLE hDevice, DWORD PISR[2]);
    def BSTIOD48_Relay_SetStatus_Multi (self,hDevice,PISR):
        isr=(c_ulong*2)(PISR[0],PISR[1])
        self.capi.BSTIOD48_Relay_SetStatus_Multi.restype = c_int
        retval=self.capi.BSTIOD48_Relay_SetStatus_Multi(c_long(hDevice),isr)
        self.log.debug("handler: %d,ChanNo: %d Status: %d, return value: %d" % \
                        ( hDevice,ChanNo,Status,retval) )
        return retval

    # DLL BOOL __stdcall BSTIOD48_Relay_GetStatus_Single (HANDLE hDevice, BYTE ChanNo,BYTE *pStatus);
    # pStatus should be defined as pStatus=c_ubyte() , and reference as pStatus.value
    def BSTIOD48_Relay_GetStatus_Single (self,hDevice,ChanNo,pStatus):
        self.capi.BSTIOD48_Relay_GetStatus_Single.restype = c_int
        retval=self.capi.BSTIOD48_Relay_GetStatus_Single(c_long(hDevice),c_ubyte(ChanNo),byref(pStatus))
        self.log.debug("Get handler: %d,ChanNo: %d Status: %d, return value: %d" % \
                        (hDevice,ChanNo,pStatus.value,retval) )
        return retval

    # DLL BOOL __stdcall BSTIOD48_Relay_GetStatus_Multi (HANDLE hDevice, DWORD PISR[2]);
    def BSTIOD48_Relay_GetStatus_Multi(self,hDevice,PISR):
        isr=c_ulong*2
        self.capi.BSTIOD48_Relay_GetStatus_Multi.restype = c_int
        retval=self.capi.BSTIOD48_Relay_GetStatus_Multi(c_long(hDevice),isr)
        del PISR[:]
        PISR[:]=isr[:]
        # PISR.append(isr[0])
        # PISR.append(isr[1])
        self.log.debug("Get handler: %d,isr[0]: %d isr[1]: %d, return value: %d" % \
                        ( hDevice,PISR[0],PISR[1],retval) )
        return retval

if __name__ == "__main__":
    hid=0 
    ChanNo=0
    card=BSTIOD48("BSTIOD48.dll")
    retval,hCard=card.BSTIOD48_Open(hid)
    if retval < 1:
        print "open hardware: %d failed" % retval
        exit(1)

    retval=card.BSTIOD48_Reset(hCard)
    print "Reset hCard: %d return value: %d" %(hCard,retval)

    sn=card.BSTIOD48_GetSN(hCard)
    print "SN Number: %d" % sn

    verinfo=VERSIONINFO_STRUCT()
    retval=card.BSTIOD48_GetVersion(hCard,verinfo)
    if retval > 0:
        print("hwVersion: %d driverVersion: %d libVersion: %d" % \
                (verinfo.hwVersion,verinfo.driverVersion,verinfo.libVersion) )

    btstatus=0
    card.BSTIOD48_Relay_SetStatus_Single(hCard,ChanNo,btstatus)
    pStatus=c_ubyte()
    retval=card.BSTIOD48_Relay_GetStatus_Single(hCard,ChanNo,pStatus)
    print "Relay SetStatus: %d, Return status: %d" % (pStatus.value,retval)

    ChanNo= 48
    pStatus=c_ubyte()
    retval=card.BSTIOD48_IO_Get_Input_Status_Single(hCard,ChanNo,pStatus)
    print "Input statua single: %d" % pStatus.value
    retval=card.BSTIOD48_Close(hCard)
    print "Close card: %d return value: %d" % (hCard,retval)

    print "Test Done"




