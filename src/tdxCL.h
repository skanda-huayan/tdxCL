#ifndef __TDXCL_H__
#define __TDXCL_H__

#pragma pack(push,1)

// --- 包含处理
void BaoHan(int nCount, float *pDirection, float *pOutHigh, float *pOutLow, float *pInclude, float *pHigh, float *pLow);
// --- 严格笔
void Bi2(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow);
// --- 特征序列画段
void Duan0(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow);

struct ZhongShu
{
    bool  bValid;
    int   nTop1, nTop2, nTop3, nBot1, nBot2, nBot3;
    float fTop1, fTop2, fTop3, fBot1, fBot2, fBot3;
    int   nLines, nStart, nEnd;
    float fHigh, fLow, fPHigh, fPLow;
    int nDirection;
    int nTerminate;

    ZhongShu();
    ~ZhongShu();

    void Reset();
    bool PushHigh(int nIndex, float fValue);
    bool PushLow (int nIndex, float fValue);
};


#pragma pack(pop)

#endif
