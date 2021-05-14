#ifndef __MAIN_H__
#define __MAIN_H__

#pragma pack(push,1)

#include "StdAfx.h"
#include <float.h>
#include <vector>
#include "tdxCL.h"

// --- for TDX --- //
typedef void(*pPluginFUNC)(int nCount, float *pOut, float *a, float *b, float *c);

typedef struct tagPluginTCalcFuncInfo
{
    unsigned short nFuncMark; // 
    pPluginFUNC    pCallFunc; //
} PluginTCalcFuncInfo;
// --- for TDX --- //

#ifdef __cplusplus
extern "C"
{
#endif //__cplusplus

__declspec(dllexport) BOOL RegisterTdxFunc(PluginTCalcFuncInfo **pInfo);

#ifdef __cplusplus
}
#endif //__cplusplus



#pragma pack(pop)
#endif
