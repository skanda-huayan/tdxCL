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
 
/********************************************************************/
//************************交易师 大智慧******************************//
/********************************************************************/
__declspec(dllexport) int WINAPI RUNMODE();
__declspec(dllexport) int WINAPI KXFX(CALCINFO* pData);     // K线方向
__declspec(dllexport) int WINAPI KXBH(CALCINFO* pData);     // K线包含
__declspec(dllexport) int WINAPI KXBH2VAR(CALCINFO* pData); // K线包含处理
__declspec(dllexport) int WINAPI KXBHG(CALCINFO* pData);    // K线包含处理后的高点
__declspec(dllexport) int WINAPI KXBHD(CALCINFO* pData);    // K线包含处理后的低点
__declspec(dllexport) int WINAPI BI(CALCINFO* pData);       // 笔端点
__declspec(dllexport) int WINAPI DUANVAR(CALCINFO* pData);  // 段端点
__declspec(dllexport) int WINAPI ZSZGVAR(CALCINFO* pData);  // 中枢高
__declspec(dllexport) int WINAPI ZSZDVAR(CALCINFO* pData);  // 中枢低点
__declspec(dllexport) int WINAPI ZSSEVAR(CALCINFO* pData);  // 中枢开始结束
__declspec(dllexport) int WINAPI ZSFXVAR(CALCINFO* pData);  // 中枢方向

#ifdef __cplusplus
}
#endif //__cplusplus



#pragma pack(pop)
#endif
