#include <iostream>
#include <fstream>
#include "tdxCL.h"

using namespace std;

// --- 处理包含关系
void BaoHan(int nCount, float *pDirection, float *pOutHigh, float *pOutLow, float *pInclude, float *pHigh, float *pLow)
{
    if (pHigh[1] > pHigh[0] && pLow[1] > pLow[0])
    {
        pDirection[0] = 1;
        pDirection[1] = 1;

        pInclude[0] = 0;
        pInclude[1] = 0;

        pOutHigh[0] = pHigh[0];
        pOutHigh[1] = pHigh[1];

        pOutLow[0] = pLow[0];
        pOutLow[1] = pLow[1];
    }
    else if (pHigh[1] < pHigh[0] && pLow[1] < pLow[0])
    {
        pDirection[0] = -1;
        pDirection[1] = -1;

        pInclude[0] = 0;
        pInclude[1] = 0;

        pOutHigh[0] = pHigh[0];
        pOutHigh[1] = pHigh[1];

        pOutLow[0] = pLow[0];
        pOutLow[1] = pLow[1];
    }
    else if (pHigh[1] <= pHigh[0] && pLow[1] >= pLow[0])
    {
        pDirection[0] = -1;
        pDirection[1] = -1;

        pInclude[0] = 0;
        pInclude[1] = 1;

        float hign = pHigh[1];
        float low = pLow[0];

        pOutHigh[0] = hign;
        pOutHigh[1] = hign;

        pOutLow[0] = low;
        pOutLow[1] = low;
    }
    else
    {
        pDirection[0] = 1;
        pDirection[1] = 1;

        pInclude[0] = 0;
        pInclude[1] = 1;

        float hign = pHigh[1];
        float low = pLow[0];

        pOutHigh[0] = hign;
        pOutHigh[1] = hign;

        pOutLow[0] = low;
        pOutLow[1] = low;
    }

    for (int i = 2; i < nCount; i++)
    {
        if (pHigh[i] > pOutHigh[i-1] && pLow[i] > pOutLow[i-1])
        {
            pDirection[i] = 1;
            pInclude[i] = 0;
            pOutHigh[i] = pHigh[i];
            pOutLow[i] = pLow[i];
        }
        else if (pHigh[i] < pOutHigh[i-1] && pLow[i] < pOutLow[i-1])
        {
            pDirection[i] = -1;
            pInclude[i] = 0;
            pOutHigh[i] = pHigh[i];
            pOutLow[i] = pLow[i];
        }
        else if (pHigh[i] <= pOutHigh[i-1] && pLow[i] >= pOutLow[i-1])
        {
            pDirection[i] = pDirection[i-1];
            pInclude[i] = 1;
            if (pDirection[i-1] == 1)
            {
                float high = pOutHigh[i-1];
                float low = pLow[i];
                int j = i;
                while (j >=0)
                {
                    pOutHigh[j] = high;
                    pOutLow[j] = low;
                    if (pInclude[j] == 0)
                    {
                        break;
                    }
                    j--;
                }
            }
            else
            {
                float high = pHigh[i];
                float low = pOutLow[i-1];
                int j = i;
                while (j >=0)
                {
                    pOutHigh[j] = high;
                    pOutLow[j] = low;
                    if (pInclude[j] == 0)
                    {
                        break;
                    }
                    j--;
                }
            }
        }
        else
        {
            pDirection[i] = pDirection[i-1];
            pInclude[i] = 1;
            if (pDirection[i-1] == 1)
            {
                float high = pHigh[i];
                float low = pOutLow[i-1];
                int j = i;
                while (j >=0)
                {
                    pOutHigh[j] = high;
                    pOutLow[j] = low;
                    if (pInclude[j] == 0)
                    {
                        break;
                    }
                    j--;
                }
            }
            else
            {
                float high = pOutHigh[i-1];
                float low = pLow[i];
                int j = i;
                while (j >=0)
                {
                    pOutHigh[j] = high;
                    pOutLow[j] = low;
                    if (pInclude[j] == 0)
                    {
                        break;
                    }
                    j--;
                }
            }
        }
    }
}

// 从fromIndex到toIndex，最后一个值是最低的
int LastIsMin(float *pLow, int fromIndex, int toIndex)
{
    for (int i = fromIndex; i < toIndex; i++)
    {
        if (pLow[i] < pLow[toIndex])
        {
            return 0;
        }
    }
    return 1;
}

// 从fromIndex到toIndex，最后一个值是最高的
int LastIsMax(float *pHigh, int fromIndex, int toIndex)
{
    for (int i = fromIndex; i < toIndex; i++)
    {
        if (pHigh[i] > pHigh[toIndex])
        {
            return 0;
        }
    }
    return 1;
}

// 计算底分型中间K线区间高
float RangeHigh(float *pOutHigh, int nLastD)
{
    for (int i = nLastD - 1; i >= 0; i--)
    {
        if (pOutHigh[i] > pOutHigh[nLastD])
        {
            return pOutHigh[i];
        }
    }
    return pOutHigh[0];
}

// 计算底分型中间K线区间低
float RangeLow(float *pOutLow, int nLastG)
{
    for (int i = nLastG - 1; i >= 0; i--)
    {
        if (pOutLow[i] < pOutLow[nLastG])
        {
            return pOutLow[i];
        }
    }
    return pOutLow[0];
}

// 反向跳空
int IsReverseJump(int i, int nState, int nLastD, int nLastG, float *pHigh, float *pLow)
{
    if (nState == 1)
    {
        if (pHigh[i] < pLow[nLastD])
        {
            if (i > nLastG && pHigh[i] < pLow[i-1])
            {
                return 1;
            }
        }
    }
    else if (nState == -1)
    {
        if (pLow[i] > pHigh[nLastG])
        {
            if (i > nLastD && pLow[i] > pHigh[i-1])
            {
                return 1;
            }
        }
    }
    return 0;
}

// 从index往前找低点坐标
int GetLastDIndex(int index, float *pSig)
{
    for (int x = index; x >= 0; x--)
    {
        if (pSig[x] == -1)
        {
            return x;
        }
    }
    return -1;
}

// 从index往前找高点坐标
int GetLastGIndex(int index, float *pSig)
{
    for (int x = index; x >= 0; x--)
    {
        if (pSig[x] == 1)
        {
            return x;
        }
    }
    return -1;
}

// 比较强势的上涨或者下跌也成笔
int IsStrongMove(int i, int nState, int nLastD, int nLastG, float *pHigh, float *pLow, float* pSig)
{
    if (nState == 1)
    {
        if (pLow[i] < pLow[nLastD])
        {
            int g1 = GetLastGIndex(i, pSig);
            int g2 = GetLastGIndex(g1 - 1, pSig);
            if (g1 >= 0 && g2 >= 0 && pHigh[g1] > pHigh[g2] && i - g1 >= 4)
            {
                return 1;
            }
        }
    }
    else if (nState == -1)
    {
        if (pHigh[i] > pHigh[nLastG])
        {
            int d1 = GetLastDIndex(i, pSig);
            int d2 = GetLastDIndex(d1 - 1, pSig);
            if (d1 >= 0 && d2 >= 0 && pLow[d1] < pLow[d2] && i - d1 >= 4)
            {
                return 1;
            }
        }
    }
    return 0;
}

bool HasTempBi(int nState, int nCount, int i, float *pHigh, float *pLow, float *pInclude, float *pOutHigh, float *pOutLow)
{
    int kCount = 1;
    if (nState == 1) // 找向上笔
    {
        for (int x = i; x < nCount; x++)
        {
            if (pLow[x] < pLow[i])
            {
                return false;
            }
            else
            {
                if (pInclude[x] == 0)
                {
                    kCount++;
                }
                if (kCount >= 5 && LastIsMax(pHigh, i, x) && pOutHigh[x] > pOutHigh[i])
                {
                    return true;
                }
            }
        }
    }
    else if (nState == -1) // 找向下笔
    {
        for (int x = i; x < nCount; x++)
        {
            if (pHigh[x] > pHigh[i])
            {
                return false;
            }
            else
            {
                if (pInclude[x] == 0)
                {
                    kCount++;
                }
                if (kCount >= 5 && LastIsMin(pLow, i, x) && pOutLow[x] < pOutLow[i])
                {
                    return true;
                }
            }
        }
    }
    return true;
}

// --- 严格笔 --- //
void Bi2(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    int iFenXingQuJian = 2;

    float *pDirection = new float[nCount];
    float *pOutHigh = new float[nCount];
    float *pOutLow = new float[nCount];
    float *pInclude = new float[nCount];

    BaoHan(nCount, pDirection, pOutHigh, pOutLow, pInclude, pHigh, pLow);

    pOut[0] = -1; // -1表示笔底，1表示笔顶，初始化是第一根K线认为是一个底。
    int nState = -1; // -1表示向下笔中，1表示向上笔中，初始化时候认为是向下笔的延续中
    int nLastD = 0; // 底位置
    int nLastG = -1; // 顶位置，初始化没有顶
    int kCountDown = 5; // 计数K线数量，初始值假设已经向下笔第五根K线
    int kCountUp = 1;

    for (int i = 1; i < nCount; i++)
    {
        if (nState == -1)
        {
            // 向下笔中遇到K线出新低，底就要移到新低这里，这里不需要管K线的方向。
            if (pLow[i] < pLow[nLastD])
            {
                pOut[nLastD] = 0;
                nLastD = i;
                pOut[nLastD] = -1;
                kCountUp = 1;
            }
            // 向下笔中遇到K线不出新低。
            else
            {
                if (pInclude[i] == 0)
                {
                    kCountUp++;
                }
                if ((kCountUp >= 5 || IsStrongMove(i, nState, nLastD, nLastG, pHigh, pLow, pOut) || IsReverseJump(i, nState, nLastD, nLastG, pHigh, pLow)) &&
                        LastIsMax(pHigh, nLastD, i) && (iFenXingQuJian == 1 ? pOutHigh[i] > RangeHigh(pOutHigh, nLastD) : pOutHigh[i] > pOutHigh[nLastD]))
                {
                    nState = 1;
                    nLastG = i;
                    pOut[nLastG] = 1;
                    kCountDown = 1;
                }
                else
                {
                    int d1 = GetLastDIndex(i, pOut);
                    int d2 = GetLastDIndex(d1 - 1, pOut);
                    int g1 = GetLastGIndex(i, pOut);
                    if (d1 >=0 && d2 >= 0 && g1 >= 0 && g1 < d1 && d2 < g1 && pLow[d1] > pLow[d2] && pHigh[i] > pHigh[g1] && HasTempBi(nState, nCount, i, pHigh, pLow, pInclude, pOutHigh, pOutLow))
                    {
                        pOut[d1] = 0;
                        pOut[g1] = 0;
                        nState = 1;
                        nLastG = i;
                        pOut[nLastG] = 1;
                        kCountDown = 1;
                    }
                    else
                    {
                        pOut[i] = 0;
                    }
                }
            }
        }
        else if (nState == 1)
        {
            // 向上笔中遇到K线出新高，顶就要移到新高这里，这里不需要管K线的方向。
            if (pHigh[i] > pHigh[nLastG])
            {
                pOut[nLastG] = 0;
                nLastG = i;
                pOut[nLastG] = 1;
                kCountDown = 1;
            }
            // 向上笔中遇到K线不出新高。
            else
            {
                if (pInclude[i] == 0)
                {
                    kCountDown++;
                }
                if ((kCountDown >= 5 || IsStrongMove(i, nState, nLastD, nLastG, pHigh, pLow, pOut) || IsReverseJump(i, nState, nLastD, nLastG, pHigh, pLow)) &&
                        LastIsMin(pLow, nLastG, i) && (iFenXingQuJian == 1 ? pOutLow[i] < RangeLow(pOutLow, nLastG) : pOutLow[i] < pOutLow[nLastG]))
                {
                    // 转向到向下笔状态
                    nState = -1;
                    nLastD = i;
                    pOut[nLastD] = -1;
                    kCountUp = 1;
                }
                else
                {
                    int g1 = GetLastGIndex(i, pOut);
                    int g2 = GetLastGIndex(g1 - 1, pOut);
                    int d1 = GetLastDIndex(i, pOut);
                    if (g1 >= 0 && g2 >=0 && d1 >= 0 && d1 < g1 && g2 < d1 && pHigh[g1] < pHigh[g2] && pLow[i] < pLow[d1] && HasTempBi(nState, nCount, i, pHigh, pLow, pInclude, pOutHigh, pOutLow))
                    {
                        pOut[g1] = 0;
                        pOut[d1] = 0;
                        nState = -1;
                        nLastD = i;
                        pOut[nLastD] = -1;
                        kCountUp = 1;
                    }
                    else
                    {
                        pOut[i] = 0;
                    }
                }
            }

        }

        // 向下笔中有高点大于前高，前高要调整。
        // 向上笔中有低点小于前低，低点要调整。
        while (pOut[i] == -1 || pOut[i] == 1)
        {
            if (pOut[i] == -1)
            {
                // 中间如果有更高的K线，前面的顶要移到更高K线那里
                int IsLastGMoved = 0;
                int nTemp = 0;
                if (nLastG >= 0)
                {
                    nTemp = nLastG + 1;
                    while (nTemp <= i)
                    {
                        if (pHigh[nTemp] > pHigh[nLastG])
                        {
                            IsLastGMoved = 1;
                            break;
                        }
                        nTemp++;
                    }
                }
                if (IsLastGMoved == 1)
                {
                    pOut[nLastG] = 0; // 消掉原来顶
                    nLastG = nTemp;
                    pOut[nLastD] = 0;
                    pOut[nLastG] = 1; // 顶后移
                    nLastD = GetLastDIndex(nLastG, pOut);// 底归位
                    i = nLastG; // 从新的顶重新开始计算
                    kCountDown = 1; // 向下K线数量归位
                    nState = 1;
                }
                else
                {
                    break;
                }
            }
            else if (pOut[i] == 1)
            {
                // 中间如果有更低的K线，前面的底要移到更低K线那里
                int IsLastDMoved = 0;
                int nTemp = 0;
                if (nLastD >= 0)
                {
                    nTemp = nLastD + 1;
                    while (nTemp <= i)
                    {
                        if (pLow[nTemp] < pLow[nLastD])
                        {
                            IsLastDMoved = 1;
                            break;
                        }
                        nTemp++;
                    }
                }
                if (IsLastDMoved == 1)
                {
                    pOut[nLastD] = 0; // 消掉原来底
                    nLastD = nTemp;
                    pOut[nLastG] = 0;
                    pOut[nLastD] = -1; // 底后移
                    nLastG = GetLastGIndex(nLastD, pOut);// 底归位
                    i = nLastD; // 从新的顶重新开始计算
                    kCountUp = 1; // 向上K线数量归位
                    nState = -1;
                }
                else
                {
                    break;
                }
            }
        }
    }

    delete []pDirection;
    delete []pOutHigh;
    delete []pOutLow;
    delete []pInclude;
}


// --- Duan ---
// --- 特征序列画段
void Duan0(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    int nState = 0;
    int nLastD = 0; // 前一个向下线段的底
    int nLastG = 0; // 前一个向上线段的顶
    float fTop0 = 0;
    float fTop1 = 0;
    float fTop2 = 0;
    float fBot0 = 0;
    float fBot1 = 0;
    float fBot2 = 0;
    for (int i = 0; i < nCount; i++)
    {
        if (pIn[i] == 1)
        {
            fTop1 = fTop2;
            fTop2 = pHigh[i];
        }
        else if (pIn[i] == -1) {
            fBot1 = fBot2;
            fBot2 = pLow[i];
        }
        
        if (nState == 0)
        {
            if (pIn[i] == 1)
            {
                nState = 1;
                nLastG = i;
                pOut[nLastG] = 1;
                fTop0 = 0;
                fBot0 = 0;
            }
            else if (pIn[i] == -1)
            {
                nState = -1;
                nLastD = i;
                pOut[nLastD] = -1;
                fTop0 = 0;
                fBot0 = 0;
            }
        }
        else if (nState == 1) // 向上线段运行中
        {
            if (pIn[i] == 1) // 遇到高点
            {
                if (pHigh[i] > pHigh[nLastG]) // 比线段最高点还高，高点后移
                {
                    pOut[nLastG] = 0;
                    nLastG = i;
                    pOut[nLastG] = 1;
                    fTop0 = 0;
                    fBot0 = 0;
                }
            }
            else if (pIn[i] == -1) // 遇到低点
            {
                if (pLow[i] < pLow[nLastD]) // 低点比向上线段最低点还低了，当一段处理，也是终结。
                {
                    nState = -1;
                    nLastD = i;
                    pOut[nLastD] = -1;
                    fTop0 = 0;
                    fBot0 = 0;
                }
                else if (fTop1 > 0 && fTop2 > 0 && fBot1 > 0 && fBot2 > 0 && fTop2 < fTop1 && fBot2 < fBot1) // 向上线段终结
                {
                    nState = -1;
                    nLastD = i;
                    pOut[nLastD] = -1;
                    fTop0 = 0;
                    fBot0 = 0;
                }
                else
                {
                    if (fBot0 == 0)
                    {
                        fBot0 = pLow[i];
                    }
                    else if (pLow[i] < fBot0) // 向上线段终结
                    {
                        nState = -1;
                        nLastD = i;
                        pOut[nLastD] = -1;
                        fTop0 = 0;
                        fBot0 = 0;
                    }
                }
            }
        }
        else if (nState == -1) // 向下线段运行中
        {
            if (pIn[i] == -1) // 遇到低点
            {
                if (pLow[i] < pLow[nLastD]) // 比线段最低点还低，低点后移
                {
                    pOut[nLastD] = 0;
                    nLastD = i;
                    pOut[nLastD] = -1;
                    fTop0 = 0;
                    fBot0 = 0;
                }
            }
            else if (pIn[i] == 1) // 遇到高点
            {
                if (pHigh[i] > pHigh[nLastG]) // 高点比向下线段最高点还高了，当一段处理，也是终结。
                {
                    nState = 1;
                    nLastG = i;
                    pOut[nLastG] = 1;
                    fTop0 = 0;
                    fBot0 = 0;
                }
                else if (fTop1 > 0 && fTop2 > 0 && fBot1 > 0 && fBot2 > 0 && fTop2 > fTop1 && fBot2 > fBot1) // 向下线段终结
                {
                    nState = 1;
                    nLastG = i;
                    pOut[nLastG] = 1;
                    fTop0 = 0;
                    fBot0 = 0;
                }
                else
                {
                    if (fTop0 == 0)
                    {
                        fTop0 = pHigh[i];
                    }
                    else if (pHigh[i] > fTop0) // 向下线段终结
                    {
                        nState = 1;
                        nLastG = i;
                        pOut[nLastG] = 1;
                        fTop0 = 0;
                        fBot0 = 0;
                    }
                }
            }
        }
    }
}


// --- 中枢
ZhongShu::ZhongShu()
{
    this->bValid = false;
    this->nTop1  = 0;
    this->nTop2  = 0;
    this->nTop3  = 0;
    this->nBot1  = 0;
    this->nBot2  = 0;
    this->nBot3  = 0;
    this->fTop1  = 0;
    this->fTop2  = 0;
    this->fTop3  = 0;
    this->fBot1  = 0;
    this->fBot2  = 0;
    this->fBot3  = 0;
    this->nLines = 0;
    this->nStart = 0;
    this->nEnd   = 0;
    this->fHigh  = 0;
    this->fLow   = 0;
    this->nDirection = 0;
    this->nTerminate = 0;
}

ZhongShu::~ZhongShu()
{
}

void ZhongShu::Reset()
{
    this->bValid = false;
    this->nTop1  = 0;
    this->nTop2  = 0;
    this->nTop3  = 0;
    this->nBot1  = 0;
    this->nBot2  = 0;
    this->nBot3  = 0;
    this->fTop1  = 0;
    this->fTop2  = 0;
    this->fTop3  = 0;
    this->fBot1  = 0;
    this->fBot2  = 0;
    this->fBot3  = 0;
    this->nLines = 0;
    this->nStart = 0;
    this->nEnd   = 0;
    this->fHigh  = 0;
    this->fLow   = 0;
    this->nDirection = 0;
    this->nTerminate = 0;
}

// 推入高点并计算状态
bool ZhongShu::PushHigh(int nIndex, float fValue)
{
    nTop3 = nTop2;
    fTop3 = fTop2;
    nTop2 = nTop1;
    fTop2 = fTop1;
    nTop1 = nIndex;
    fTop1 = fValue;
    if (bValid == true)
    {
        if (fTop1 < fLow)   // 中枢终结
        {
            nTerminate = -1;
            if (nTop2 > nEnd)
            {
                nEnd = nTop2;
            }
            return true;
        }
        else
        {
            if (nBot1 > nEnd)
            {
                nEnd = nBot1; // 中枢终结点后移
            }
        }
    }
    else
    {
        if (nTop3 > 0 && nTop2 > 0 && nTop1 > 0 && nBot2 > 0 && nBot1 > 0)   // 有两个高点和两个低点
        {
            float fTempHigh = (fTop1 < fTop2 ? fTop1 : fTop2);
            float fTempLow = (fBot1 > fBot2 ? fBot1 : fBot2);
            if (fTop3 > fTop2 && fTempHigh > fTempLow)   // 有中枢
            {
                nDirection = -1; // 向下中枢
                nStart = nBot2;
                nEnd = nTop1;
                fHigh = fTempHigh;
                fLow = fTempLow;
                bValid = true;
            }
        }
    }
    return false;
}

bool ZhongShu::PushLow(int nIndex, float fValue)
{
    nBot3 = nBot2;
    fBot3 = fBot2;
    nBot2 = nBot1;
    fBot2 = fBot1;
    nBot1 = nIndex;
    fBot1 = fValue;
    if (bValid == true)
    {
        if (fBot1 > fHigh)   // 中枢终结
        {
            nTerminate = 1;
            if (nBot2 > nEnd)
            {
                nEnd = nBot2;
            }
            return true;
        }
        else
        {
            if (nTop1 > nEnd)
            {
                nEnd = nTop1; // 中枢终结点后移
            }
        }
    }
    else
    {
        if (nTop2 > 0 && nTop1 > 0 && nBot3 > 0 && nBot2 > 0 && nBot1 > 0)   // 有两个高点和两个低点
        {
            float fTempHigh = (fTop1 < fTop2 ? fTop1 : fTop2);
            float fTempLow = (fBot1 > fBot2 ? fBot1 : fBot2);
            if (fBot3 < fBot2 && fTempHigh > fTempLow)   // 有中枢
            {
                nDirection = 1; // 向上中枢
                nStart = nTop2;
                nEnd = nBot1;
                fHigh = fTempHigh;
                fLow = fTempLow;
                bValid = true;
            }
        }
    }
    return false;
}
