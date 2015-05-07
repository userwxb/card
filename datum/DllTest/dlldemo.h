//=====================================================================
//--------------File - AEC429D22_lib.h------------------
//
//--------Library for accessing the AEC429D22 card------------
// 
//   Copyright (c) 2005 Astro Explorer China Inc.  http://www.aectech.cn
//
//   Author:lhjzm  DATE:2006-04-25
// 
//=====================================================================


#ifndef _DLLDEMO_H_
#define _DLLDEMO_H_


#ifdef __cplusplus
extern "C" {
#endif

#define DLL  __declspec(dllexport)

DLL int __stdcall Onadd(int a,int b);

    



#ifdef __cplusplus
}
#endif

#endif
