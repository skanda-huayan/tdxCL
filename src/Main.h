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

///////////////////////////////////////////////////////////////////////////
//分析周期
enum DATA_TYPE
{
	TICK_DATA=2,				//分笔成交
	MIN1_DATA,					//1分钟线
	MIN5_DATA,					//5分钟线					
	MIN15_DATA,					//15分钟线
	MIN30_DATA,					//30分钟线
	MIN60_DATA,					//60分钟线
	DAY_DATA,					//日线
	WEEK_DATA,					//周线
	MONTH_DATA,					//月线
	MULTI_DATA					//多日线
};

///////////////////////////////////////////////////////////////////////////
//基本数据

typedef struct tagSTKDATA	
{
	time_t	m_time;			//时间,UCT
	float	m_fOpen;		//开盘
	float	m_fHigh;		//最高
	float	m_fLow;			//最低
	float	m_fClose;		//收盘
	float	m_fVolume;		//成交量
	float	m_fAmount;		//成交额
	WORD	m_wAdvance;		//上涨家数(仅大盘有效)
	WORD	m_wDecline;		//下跌家数(仅大盘有效)
} STKDATA;


////////////////////////////////////////////////////////////////////////////
//扩展数据,用于描述分笔成交数据的买卖盘

typedef union tagSTKDATAEx
{
	struct
	{
		float m_fBuyPrice[3];		//买1--买3价
		float m_fBuyVol[3];			//买1--买3量
		float m_fSellPrice[3];		//卖1--卖3价	
		float m_fSellVol[3];		//卖1--卖3量
	};
	float m_fDataEx[12];			//保留
} STKDATAEx;

/////////////////////////////////////////////////////////////////////////////
/*财务数据顺序(m_pfFinData内容)

	序号	内容

	0	总股本(万股),
	1	国家股,
	2	发起人法人股,
	3	法人股,
	4	B股,
	5	H股,
	6	流通A股,
	7	职工股,
	8	A2转配股,
	9	总资产(千元),
	10	流动资产,
	11	固定资产,
	12	无形资产,
	13	长期投资,
	14	流动负债,
	15	长期负债,
	16	资本公积金,
	17	每股公积金,
	18	股东权益,
	19	主营收入,
	20	主营利润,
	21	其他利润,
	22	营业利润,
	23	投资收益,
	24	补贴收入,
	25	营业外收支,
	26	上年损益调整,
	27	利润总额,
	28	税后利润,
	29	净利润,
	30	未分配利润,
	31	每股未分配,
	32	每股收益,
	33	每股净资产,
	34	调整每股净资,
	35	股东权益比,
	36	净资收益率
*/

/////////////////////////////////////////////////////////////////////////////
//函数数据结构

typedef struct tagCALCINFO
{
	const DWORD			m_dwSize;				//结构大小
	const DWORD			m_dwVersion;			//调用软件版本(V2.10 : 0x210)
	const DWORD			m_dwSerial;				//调用软件序列号
	const char*			m_strStkLabel;			//股票代码
	const BOOL			m_bIndex;				//大盘

	const int			m_nNumData;				//数据数量(pData,pDataEx,pResultBuf数据数量)
	const STKDATA*		m_pData;				//常规数据,注意:当m_nNumData==0时可能为 NULL
	const STKDATAEx*	m_pDataEx;				//扩展数据,分笔成交买卖盘,注意:可能为 NULL

	const int			m_nParam1Start;			//参数1有效位置
	const float*		m_pfParam1;				//调用参数1	
	const float*		m_pfParam2;				//调用参数2
	const float*		m_pfParam3;				//调用参数3
	const float*		m_pfParam4;				//调用参数3

	float*				m_pResultBuf;			//结果缓冲区
	const DATA_TYPE		m_dataType;				//数据类型
	const float*		m_pfFinData;			//财务数据
} CALCINFO;

/* 
注: 
	1.函数调用参数由m_pfParam1--m_pfParam4带入,若为NULL则表示该参数无效.
	2.当一个参数无效时,则其后的所有参数均无效.
		如:m_pfParam2为NULL,则m_pfParam3,m_pfParam4一定为NULL.
	3.参数1可以是常数参数或序列数参数,其余参数只能为常数参数.
	4.若m_nParam1Start<0, 则参数1为常数参数,参数等于*m_pfParam1;
	5.若m_nParam1Start>=0,则参数1为序列数参数,m_pfParam1指向一个浮点型数组,
		数组大小为m_nNumData,数据有效范围为m_nParam1Start--m_nNumData.
		在时间上m_pData[x] 与 m_pfParam1[x]是一致的
*/

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
