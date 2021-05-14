#include "Main.h"
#include <iostream>
#include <fstream>

using namespace std;

// ����DLL�������ں���
BOOL APIENTRY DllMain( HANDLE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

//=============================================================================
// �������1�ţ�K�߷���
//=============================================================================
void Func1(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    float *pDirection = new float[nCount];
    float *pOutHigh = new float[nCount];
    float *pOutLow = new float[nCount];
    float *pInclude = new float[nCount];

    BaoHan(nCount, pDirection, pOutHigh, pOutLow, pInclude, pHigh, pLow);

    for (int i = 0; i < nCount; i++)
    {
        pOut[i] = pDirection[i];
    }

    delete []pDirection;
    delete []pOutHigh;
    delete []pOutLow;
    delete []pInclude;
}

//=============================================================================
// �������2�ţ��Ƿ����а�����ϵ��K��
//=============================================================================
void Func2(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    float *pDirection = new float[nCount];
    float *pOutHigh = new float[nCount];
    float *pOutLow = new float[nCount];
    float *pInclude = new float[nCount];

    BaoHan(nCount, pDirection, pOutHigh, pOutLow, pInclude, pHigh, pLow);

    for (int i = 0; i < nCount; i++)
    {
        pOut[i] = pInclude[i];
    }

    delete []pDirection;
    delete []pOutHigh;
    delete []pOutLow;
    delete []pInclude;
}

//=============================================================================
// �������3�ţ�����������K�߸�
//=============================================================================
void Func3(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    float *pDirection = new float[nCount];
    float *pOutHigh = new float[nCount];
    float *pOutLow = new float[nCount];
    float *pInclude = new float[nCount];

    BaoHan(nCount, pDirection, pOutHigh, pOutLow, pInclude, pHigh, pLow);

    for (int i = 0; i < nCount; i++)
    {
        pOut[i] = pOutHigh[i];
    }

    delete []pDirection;
    delete []pOutHigh;
    delete []pOutLow;
    delete []pInclude;
}

//=============================================================================
// �������4�ţ�����������K�ߵ�
//=============================================================================
void Func4(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    float *pDirection = new float[nCount];
    float *pOutHigh = new float[nCount];
    float *pOutLow = new float[nCount];
    float *pInclude = new float[nCount];

    BaoHan(nCount, pDirection, pOutHigh, pOutLow, pInclude, pHigh, pLow);

    for (int i = 0; i < nCount; i++)
    {
        pOut[i] = pOutLow[i];
    }

    delete []pDirection;
    delete []pOutHigh;
    delete []pOutLow;
    delete []pInclude;
}

//=============================================================================
// �������5�ţ�����һ�°����źţ�����ͨ���Ż���
//=============================================================================
void Func5(int nCount, float *pOut, float *pIn1, float *pIn2, float *pInclude)
{
    pOut[0] = 0;
    float n = 1;
    for (int i = 1; i < nCount; i++)
    {
        if (pInclude[i-1] == 0 && pInclude[i] == 0)
        {
            pOut[i] = 0;
        }
        else if (pInclude[i-1] == 0 && pInclude[i] == 1)
        {
            pOut[i-1] = n;
            pOut[i] = n;
        }
        else if (pInclude[i-1] == 1 && pInclude[i] == 1)
        {
            pOut[i] = n;
        }
        else if (pInclude[i-1] == 1 && pInclude[i] == 0)
        {
            pOut[i] = 0;
            if (n == 1)
            {
                n = 2;
            }
            else
            {
                n = 1;
            }

        }
    }
}

//=============================================================================
// �������6�ţ�����ʶ��׶˵�
//=============================================================================
void Func6(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    Bi2(nCount, pOut, pIn, pHigh, pLow); // �ϸ��
}
 
//=============================================================================
// �������7�ţ��߶ζ����ź�
//=============================================================================
void Func7(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    Duan0(nCount, pOut, pIn, pHigh, pLow);// �������з���
}

//=============================================================================
// �������8�ţ�����ߵ�����
//=============================================================================
void Func8(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{
    ZhongShu ZhongShuOne;

    for (int i = 0; i < nCount; i++)
    {
        if (pIn[i] == 1)
        {
            // �����߶θߵ㣬���������㷨
            if (ZhongShuOne.PushHigh(i, pHigh[i]))
            {
                bool bValid = true;
                float fHighValue;
                int nHignIndex;
                int nLowIndex;
                int nLowIndexTemp;
                int nHighCount = 0;
                if (ZhongShuOne.nDirection == 1 && ZhongShuOne.nTerminate == -1) // �������౻�����ս�
                {
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == 1)
                        {
                            if (nHighCount == 0)
                            {
                                nHighCount++;
                                fHighValue = pHigh[x];
                                nHignIndex = x;
                            }
                            else
                            {
                                nHighCount++;
                                if (pHigh[x] >= fHighValue)
                                {
                                    if (nHighCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fHighValue = pHigh[x];
                                    nHignIndex = x;
                                    nLowIndex = nLowIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == -1)
                        {
                            nLowIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        ZhongShuOne.nEnd = nLowIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    i = nHignIndex - 1;
                }
                else
                {
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // �����ڸ�����õ����������
                    for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
                    {
                        pOut[j] = ZhongShuOne.fHigh;
                    }

                }

                ZhongShuOne.Reset();
            }
        }
        else if (pIn[i] == -1)
        {
            // �����߶ε͵㣬���������㷨
            if (ZhongShuOne.PushLow(i, pLow[i]))
            {
                bool bValid = true;
                float fLowValue;
                int nLowIndex;
                int nHighIndex;
                int nHighIndexTemp;
                int nLowCount = 0;
                if (ZhongShuOne.nDirection == -1 && ZhongShuOne.nTerminate == 1) // �������౻�����ս�
                {
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == -1)
                        {
                            if (nLowCount == 0)
                            {
                                nLowCount++;
                                fLowValue = pLow[x];
                                nLowIndex = x;
                            }
                            else
                            {
                                nLowCount++;
                                if (pLow[x] <= fLowValue)
                                {
                                    if (nLowCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fLowValue = pLow[x];
                                    nLowIndex = x;
                                    nHighIndex = nHighIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == 1)
                        {
                            nHighIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        ZhongShuOne.nEnd = nHighIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    i = nLowIndex - 1;
                }
                else
                {
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // �����ڸ�����õ����������
                    for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
                    {
                        pOut[j] = ZhongShuOne.fHigh;
                    }

                }

                ZhongShuOne.Reset();
            }
        }
    }
    if (ZhongShuOne.bValid) // ���һ����û�б��ս�����ࡣ
    {
        // �����ڸ�����õ����������
        for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
        {
            pOut[j] = ZhongShuOne.fHigh;
        }
    }
}

//=============================================================================
// �������9�ţ�����͵�����
//=============================================================================
void Func9(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{

    ZhongShu ZhongShuOne;

    for (int i = 0; i < nCount; i++)
    {
        if (pIn[i] == 1)
        {
            // �����߶θߵ㣬���������㷨
            if (ZhongShuOne.PushHigh(i, pHigh[i]))
            {
                bool bValid = true;
                float fHighValue;
                int nHignIndex;
                int nLowIndex;
                int nLowIndexTemp;
                int nHighCount = 0;
                if (ZhongShuOne.nDirection == 1 && ZhongShuOne.nTerminate == -1) // �������౻�����ս�
                {
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == 1)
                        {
                            if (nHighCount == 0)
                            {
                                nHighCount++;
                                fHighValue = pHigh[x];
                                nHignIndex = x;
                            }
                            else
                            {
                                nHighCount++;
                                if (pHigh[x] >= fHighValue)
                                {
                                    if (nHighCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fHighValue = pHigh[x];
                                    nHignIndex = x;
                                    nLowIndex = nLowIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == -1)
                        {
                            nLowIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        ZhongShuOne.nEnd = nLowIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    i = nHignIndex - 1;
                }
                else
                {
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // �����ڸ�����õ����������
                    for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
                    {
                        pOut[j] = ZhongShuOne.fLow;
                    }

                }

                ZhongShuOne.Reset();
            }
        }
        else if (pIn[i] == -1)
        {
            // �����߶ε͵㣬���������㷨
            if (ZhongShuOne.PushLow(i, pLow[i]))
            {
                bool bValid = true;
                float fLowValue;
                int nLowIndex;
                int nHighIndex;
                int nHighIndexTemp;
                int nLowCount = 0;
                if (ZhongShuOne.nDirection == -1 && ZhongShuOne.nTerminate == 1) // �������౻�����ս�
                {
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == -1)
                        {
                            if (nLowCount == 0)
                            {
                                nLowCount++;
                                fLowValue = pLow[x];
                                nLowIndex = x;
                            }
                            else
                            {
                                nLowCount++;
                                if (pLow[x] <= fLowValue)
                                {
                                    if (nLowCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fLowValue = pLow[x];
                                    nLowIndex = x;
                                    nHighIndex = nHighIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == 1)
                        {
                            nHighIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        ZhongShuOne.nEnd = nHighIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    i = nLowIndex - 1;
                }
                else
                {
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // �����ڸ�����õ����������
                    for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
                    {
                        pOut[j] = ZhongShuOne.fLow;
                    }

                }

                ZhongShuOne.Reset();
            }
        }
    }
    if (ZhongShuOne.bValid)
    {
        // �����ڸ�����õ����������
        for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
        {
            pOut[j] = ZhongShuOne.fLow;
        }
    }
}

//=============================================================================
// �������10�ţ�������㡢�յ��ź�
//=============================================================================
void Func10(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{

    //std::ofstream fout;
    //fout.open("D:\\CHANLUN.TXT", std::ofstream::out);

    ZhongShu ZhongShuOne;

    for (int i = 0; i < nCount; i++)
    {
        if (pIn[i] == 1)
        {
            // �����߶θߵ㣬���������㷨
            if (ZhongShuOne.PushHigh(i, pHigh[i]))
            {
                //fout<<"�����ս�"<<pHigh[i]<<endl;
                bool bValid = true;
                float fHighValue;
                int nHignIndex;
                int nLowIndex;
                int nLowIndexTemp;
                int nHighCount = 0;
                if (ZhongShuOne.nDirection == 1 && ZhongShuOne.nTerminate == -1) // �������౻�����ս�
                {
                    //fout<<"�������౻�����ս�<<endl;
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == 1)
                        {
                            if (nHighCount == 0)
                            {
                                nHighCount++;
                                fHighValue = pHigh[x];
                                nHignIndex = x;
                            }
                            else
                            {
                                nHighCount++;
                                if (pHigh[x] >= fHighValue)
                                {
                                    if (nHighCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fHighValue = pHigh[x];
                                    nHignIndex = x;
                                    nLowIndex = nLowIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == -1)
                        {
                            nLowIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        //fout<<"ͬ����ֽⱣ���������<<endl;
                        //fout<<"����������Ƶ�<<pLow[nLowIndex]<<endl;
                        ZhongShuOne.nEnd = nLowIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    else
                    {
                        //fout<<"ͬ����ֽ����������Ч<<endl;
                    }
                    i = nHignIndex - 1;
                }
                else
                {
                    //fout<<"�������౻�����ս�<<endl;
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // ���б��
                    pOut[ZhongShuOne.nStart + 1] = 1;
                    pOut[ZhongShuOne.nEnd - 1]   = 2;
                }
                ZhongShuOne.Reset();
            }
        }
        else if (pIn[i] == -1)
        {
            // �����߶ε͵㣬���������㷨
            if (ZhongShuOne.PushLow(i, pLow[i]))
            {
                //fout<<"�����ս�"<<pHigh[i]<<endl;
                bool bValid = true;
                float fLowValue;
                int nLowIndex;
                int nHighIndex;
                int nHighIndexTemp;
                int nLowCount = 0;
                if (ZhongShuOne.nDirection == -1 && ZhongShuOne.nTerminate == 1) // �������౻�����ս�
                {
                    //fout<<"�������౻�����ս�<<endl;
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == -1)
                        {
                            if (nLowCount == 0)
                            {
                                nLowCount++;
                                fLowValue = pLow[x];
                                nLowIndex = x;
                            }
                            else
                            {
                                nLowCount++;
                                if (pLow[x] <= fLowValue)
                                {
                                    if (nLowCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fLowValue = pLow[x];
                                    nLowIndex = x;
                                    nHighIndex = nHighIndexTemp;
                                }
                            }
                            //fout<<"�͵�����"<<nLowCount<<endl;
                        }
                        else if (pIn[x] == 1)
                        {
                            nHighIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        //fout<<"ͬ����ֽⱣ���������<<endl;
                        //fout<<"����������Ƶ�<<pHigh[nHighIndex]<<endl;
                        ZhongShuOne.nEnd = nHighIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    else
                    {
                        //fout<<"ͬ����ֽ����������Ч<<endl;
                    }
                    i = nLowIndex - 1;
                }
                else
                {
                    //fout<<"�������౻�����ս�<<endl;
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // ���б��
                    pOut[ZhongShuOne.nStart + 1] = 1;
                    pOut[ZhongShuOne.nEnd - 1]   = 2;

                }
                ZhongShuOne.Reset();
            }
        }
    }
    if (ZhongShuOne.bValid)
    {
        // ���б��
        pOut[ZhongShuOne.nStart + 1] = 1;
        pOut[ZhongShuOne.nEnd - 1]   = 2;
    }
    //fout.close();
}

//=============================================================================
// �������11�ţ����෽������
//=============================================================================
void Func11(int nCount, float *pOut, float *pIn, float *pHigh, float *pLow)
{

    ZhongShu ZhongShuOne;

    for (int i = 0; i < nCount; i++)
    {
        if (pIn[i] == 1)
        {
            // �����߶θߵ㣬���������㷨
            if (ZhongShuOne.PushHigh(i, pHigh[i]))
            {
                bool bValid = true;
                float fHighValue;
                int nHignIndex;
                int nLowIndex;
                int nLowIndexTemp;
                int nHighCount = 0;
                if (ZhongShuOne.nDirection == 1 && ZhongShuOne.nTerminate == -1) // �������౻�����ս�
                {
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == 1)
                        {
                            if (nHighCount == 0)
                            {
                                nHighCount++;
                                fHighValue = pHigh[x];
                                nHignIndex = x;
                            }
                            else
                            {
                                nHighCount++;
                                if (pHigh[x] >= fHighValue)
                                {
                                    if (nHighCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fHighValue = pHigh[x];
                                    nHignIndex = x;
                                    nLowIndex = nLowIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == -1)
                        {
                            nLowIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        ZhongShuOne.nEnd = nLowIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    i = nHignIndex - 1;
                }
                else
                {
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // �����ڸ�����õ����෽������
                    for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
                    {
                        pOut[j] = (float) ZhongShuOne.nDirection;
                    }

                }

                ZhongShuOne.Reset();
            }
        }
        else if (pIn[i] == -1)
        {
            // �����߶ε͵㣬���������㷨
            if (ZhongShuOne.PushLow(i, pLow[i]))
            {
                bool bValid = true;
                float fLowValue;
                int nLowIndex;
                int nHighIndex;
                int nHighIndexTemp;
                int nLowCount = 0;
                if (ZhongShuOne.nDirection == -1 && ZhongShuOne.nTerminate == 1) // �������౻�����ս�
                {
                    bValid = false;
                    for (int x = ZhongShuOne.nStart; x <= ZhongShuOne.nEnd; x++)
                    {
                        if (pIn[x] == -1)
                        {
                            if (nLowCount == 0)
                            {
                                nLowCount++;
                                fLowValue = pLow[x];
                                nLowIndex = x;
                            }
                            else
                            {
                                nLowCount++;
                                if (pLow[x] <= fLowValue)
                                {
                                    if (nLowCount > 2)
                                    {
                                        bValid = true;
                                    }
                                    fLowValue = pLow[x];
                                    nLowIndex = x;
                                    nHighIndex = nHighIndexTemp;
                                }
                            }
                        }
                        else if (pIn[x] == 1)
                        {
                            nHighIndexTemp = x;
                        }
                    }
                    if (bValid)
                    {
                        ZhongShuOne.nEnd = nHighIndex; // ����������Ƶ���ߵ��ǰһ���͵㡣
                    }
                    i = nLowIndex - 1;
                }
                else
                {
                    i = ZhongShuOne.nEnd - 1;
                }
                if (bValid)
                {
                    // �����ڸ�����õ����෽������
                    for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
                    {
                        pOut[j] = (float) ZhongShuOne.nDirection;
                    }

                }

                ZhongShuOne.Reset();
            }
        }
    }
    if (ZhongShuOne.bValid)
    {
        // �����ڸ�����õ����෽������
        for (int j = ZhongShuOne.nStart + 1; j <= ZhongShuOne.nEnd - 1; j++)
        {
            pOut[j] = (float) ZhongShuOne.nDirection;
        }
    }
}

static PluginTCalcFuncInfo Info[] =
{
    { 1, &Func1},
    { 2, &Func2},
    { 3, &Func3},
    { 4, &Func4},
    { 5, &Func5},
    { 6, &Func6},
    { 7, &Func7},
    { 8, &Func8},
    { 9, &Func9},
    {10, &Func10},
    {11, &Func11},
    { 0, NULL}
};

BOOL RegisterTdxFunc(PluginTCalcFuncInfo **pInfo)
{
    if (*pInfo == NULL)
    {
        *pInfo = Info;

        return TRUE;
    }

    return FALSE;
}

