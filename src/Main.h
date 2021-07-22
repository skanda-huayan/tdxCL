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
//·ÖÎöÖÜÆÚ
enum DATA_TYPE
{
	TICK_DATA=2,				//·Ö±Ê³É½»
	MIN1_DATA,					//1·ÖÖÓÏß
	MIN5_DATA,					//5·ÖÖÓÏß					
	MIN15_DATA,					//15·ÖÖÓÏß
	MIN30_DATA,					//30·ÖÖÓÏß
	MIN60_DATA,					//60·ÖÖÓÏß
	DAY_DATA,					//ÈÕÏß
	WEEK_DATA,					//ÖÜÏß
	MONTH_DATA,					//ÔÂÏß
	MULTI_DATA					//¶àÈÕÏß
};

///////////////////////////////////////////////////////////////////////////
//»ù±¾Êý¾Ý

typedef struct tagSTKDATA	
{
	time_t	m_time;			//Ê±¼ä,UCT
	float	m_fOpen;		//¿ªÅÌ
	float	m_fHigh;		//×î¸ß
	float	m_fLow;			//×îµÍ
	float	m_fClose;		//ÊÕÅÌ
	float	m_fVolume;		//³É½»Á¿
	float	m_fAmount;		//³É½»¶î
	WORD	m_wAdvance;		//ÉÏÕÇ¼ÒÊý(½ö´óÅÌÓÐÐ§)
	WORD	m_wDecline;		//ÏÂµø¼ÒÊý(½ö´óÅÌÓÐÐ§)
} STKDATA;


////////////////////////////////////////////////////////////////////////////
//À©Õ¹Êý¾Ý,ÓÃÓÚÃèÊö·Ö±Ê³É½»Êý¾ÝµÄÂòÂôÅÌ

typedef union tagSTKDATAEx
{
	struct
	{
		float m_fBuyPrice[3];		//Âò1--Âò3¼Û
		float m_fBuyVol[3];			//Âò1--Âò3Á¿
		float m_fSellPrice[3];		//Âô1--Âô3¼Û	
		float m_fSellVol[3];		//Âô1--Âô3Á¿
	};
	float m_fDataEx[12];			//±£Áô
} STKDATAEx;

/////////////////////////////////////////////////////////////////////////////
/*²ÆÎñÊý¾ÝË³Ðò(m_pfFinDataÄÚÈÝ)

	ÐòºÅ	ÄÚÈÝ

	0	×Ü¹É±¾(Íò¹É),
	1	¹ú¼Ò¹É,
	2	·¢ÆðÈË·¨ÈË¹É,
	3	·¨ÈË¹É,
	4	B¹É,
	5	H¹É,
	6	Á÷Í¨A¹É,
	7	Ö°¹¤¹É,
	8	A2×ªÅä¹É,
	9	×Ü×Ê²ú(Ç§Ôª),
	10	Á÷¶¯×Ê²ú,
	11	¹Ì¶¨×Ê²ú,
	12	ÎÞÐÎ×Ê²ú,
	13	³¤ÆÚÍ¶×Ê,
	14	Á÷¶¯¸ºÕ®,
	15	³¤ÆÚ¸ºÕ®,
	16	×Ê±¾¹«»ý½ð,
	17	Ã¿¹É¹«»ý½ð,
	18	¹É¶«È¨Òæ,
	19	Ö÷ÓªÊÕÈë,
	20	Ö÷ÓªÀûÈó,
	21	ÆäËûÀûÈó,
	22	ÓªÒµÀûÈó,
	23	Í¶×ÊÊÕÒæ,
	24	²¹ÌùÊÕÈë,
	25	ÓªÒµÍâÊÕÖ§,
	26	ÉÏÄêËðÒæµ÷Õû,
	27	ÀûÈó×Ü¶î,
	28	Ë°ºóÀûÈó,
	29	¾»ÀûÈó,
	30	Î´·ÖÅäÀûÈó,
	31	Ã¿¹ÉÎ´·ÖÅä,
	32	Ã¿¹ÉÊÕÒæ,
	33	Ã¿¹É¾»×Ê²ú,
	34	µ÷ÕûÃ¿¹É¾»×Ê,
	35	¹É¶«È¨Òæ±È,
	36	¾»×ÊÊÕÒæÂÊ
*/

/////////////////////////////////////////////////////////////////////////////
//º¯ÊýÊý¾Ý½á¹¹

typedef struct tagCALCINFO
{
	const DWORD			m_dwSize;				//½á¹¹´óÐ¡
	const DWORD			m_dwVersion;			//µ÷ÓÃÈí¼þ°æ±¾(V2.10 : 0x210)
	const DWORD			m_dwSerial;				//µ÷ÓÃÈí¼þÐòÁÐºÅ
	const char*			m_strStkLabel;			//¹ÉÆ±´úÂë
	const BOOL			m_bIndex;				//´óÅÌ

	const int			m_nNumData;				//Êý¾ÝÊýÁ¿(pData,pDataEx,pResultBufÊý¾ÝÊýÁ¿)
	const STKDATA*		m_pData;				//³£¹æÊý¾Ý,×¢Òâ:µ±m_nNumData==0Ê±¿ÉÄÜÎª NULL
	const STKDATAEx*	m_pDataEx;				//À©Õ¹Êý¾Ý,·Ö±Ê³É½»ÂòÂôÅÌ,×¢Òâ:¿ÉÄÜÎª NULL

	const int			m_nParam1Start;			//²ÎÊý1ÓÐÐ§Î»ÖÃ
	const float*		m_pfParam1;				//µ÷ÓÃ²ÎÊý1	
	const float*		m_pfParam2;				//µ÷ÓÃ²ÎÊý2
	const float*		m_pfParam3;				//µ÷ÓÃ²ÎÊý3
	const float*		m_pfParam4;				//µ÷ÓÃ²ÎÊý3

	float*				m_pResultBuf;			//½á¹û»º³åÇø
	const DATA_TYPE		m_dataType;				//Êý¾ÝÀàÐÍ
	const float*		m_pfFinData;			//²ÆÎñÊý¾Ý
} CALCINFO;

/* 
×¢: 
	1.º¯Êýµ÷ÓÃ²ÎÊýÓÉm_pfParam1--m_pfParam4´øÈë,ÈôÎªNULLÔò±íÊ¾¸Ã²ÎÊýÎÞÐ§.
	2.µ±Ò»¸ö²ÎÊýÎÞÐ§Ê±,ÔòÆäºóµÄËùÓÐ²ÎÊý¾ùÎÞÐ§.
		Èç:m_pfParam2ÎªNULL,Ôòm_pfParam3,m_pfParam4Ò»¶¨ÎªNULL.
	3.²ÎÊý1¿ÉÒÔÊÇ³£Êý²ÎÊý»òÐòÁÐÊý²ÎÊý,ÆäÓà²ÎÊýÖ»ÄÜÎª³£Êý²ÎÊý.
	4.Èôm_nParam1Start<0, Ôò²ÎÊý1Îª³£Êý²ÎÊý,²ÎÊýµÈÓÚ*m_pfParam1;
	5.Èôm_nParam1Start>=0,Ôò²ÎÊý1ÎªÐòÁÐÊý²ÎÊý,m_pfParam1Ö¸ÏòÒ»¸ö¸¡µãÐÍÊý×é,
		Êý×é´óÐ¡Îªm_nNumData,Êý¾ÝÓÐÐ§·¶Î§Îªm_nParam1Start--m_nNumData.
		ÔÚÊ±¼äÉÏm_pData[x] Óë m_pfParam1[x]ÊÇÒ»ÖÂµÄ
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
