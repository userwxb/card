//=====================================================================
//--------------File - BSTIOD48_lib.h------------------
//
//-------Library for accessing the BST34208 card-------
// 
//-----------------Beijing Senfetech Corporation---------------------------
//
//-----  Author:xaliu         DATE:2011-05-26       ---------------
// 
//=====================================================================
#ifndef _BSTIOD48_LIB_H_
#define _BSTIOD48_LIB_H_

#include <windows.h>

#ifdef __cplusplus
extern "C" {
#endif

#define DLL __declspec(dllimport)
#pragma comment(lib,"BSTIOD48.lib")

#ifndef  _VERSIONINFO_STRUCT_
#define  _VERSIONINFO_STRUCT_
typedef struct
{
	DWORD hwVersion;    //硬件版本号(高16位为主版本号，低16位为次版本号，版本号编码方式为BCD码)
	DWORD driverVersion;//驱动版本号
	DWORD libVersion;   //库版本号
}VERSIONINFO_STRUCT, *pVERSIONINFO_STRUCT;
#endif

DLL BOOL __stdcall BSTIOD48_Open (HANDLE *phDevice, BYTE CardId);

DLL BOOL __stdcall BSTIOD48_Close (HANDLE hDevice);

DLL BOOL __stdcall BSTIOD48_Reset (HANDLE hDevice);

DLL DWORD __stdcall BSTIOD48_GetSN (HANDLE hDevice);

DLL BOOL __stdcall BSTIOD48_GetVersion (HANDLE hDevice,pVERSIONINFO_STRUCT pVerInf);

//IO输入
DLL BOOL __stdcall BSTIOD48_IO_Get_Input_Status_Single (HANDLE hDevice, BYTE ChanNo,BYTE *pStatus);

DLL BOOL __stdcall BSTIOD48_IO_Get_Input_Status_Multi (HANDLE hDevice, DWORD PISR[2]);

DLL BOOL __stdcall BSTIOD48_Relay_SetStatus_Single (HANDLE hDevice, BYTE ChanNo,BYTE Status);

DLL BOOL __stdcall BSTIOD48_Relay_SetStatus_Multi (HANDLE hDevice, DWORD PISR[2]);

DLL BOOL __stdcall BSTIOD48_Relay_GetStatus_Single (HANDLE hDevice, BYTE ChanNo,BYTE *pStatus);

DLL BOOL __stdcall BSTIOD48_Relay_GetStatus_Multi (HANDLE hDevice, DWORD PISR[2]);




#ifdef __cplusplus
}
#endif

#endif

