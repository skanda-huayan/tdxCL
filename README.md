# tdxCL
精簡版ChanlunX，筆、段、中樞。
for：通達信和大智慧

通達信版說明：
https://www.55188.com/thread-9524243-1-1.html

大智慧版說明：
https://www.55188.com/thread-9555831-1-1.html

#編譯#
```
VC6.0即可。
```

#安裝#
```
1 編譯好的dll，即tdxCL.dll，放在通達信安裝目錄下的T0002/dlls下。
2 綁定dll到5號（其實幾號都可以，公式裡要做相應的更改即可）。
3 Ctrl-F打開公式管理器，按下面的公式創建公式。
4 。。。開始使用公式～
```

#TDX公式#
```
#TDX Formula#
{画笔}
FRAC:=TDXDLL5(6,0,H,L);
DRAWLINE(FRAC=-1,L,FRAC=+1,H,0), DOTLINE,LINETHICK1,COLORRED;
DRAWLINE(FRAC=+1,H,FRAC=-1,L,0), DOTLINE,LINETHICK1,COLORGREEN;

DUAN:=TDXDLL5(7,FRAC,H,L);{计算段的端点}
{画段}
DRAWLINE(DUAN=-1,L,DUAN=+1,H,0), COLORFF8000;{上升段}
DRAWLINE(DUAN=+1,H,DUAN=-1,L,0), COLORFF8000;{下降}

{笔中枢}
BISE:=TDXDLL5(10,FRAC,H,L);{输出笔中枢开始和结束}
BIZG:=TDXDLL5(8,FRAC,H,L);{输出笔中枢高点}
BIZD:=TDXDLL5(9,FRAC,H,L);{输出笔中枢低点}
BIZZ:=(BIZG+BIZD)/2;

{段中枢}
DUANSE:=TDXDLL5(10,DUAN,H,L);{输出段中枢开始和结束}
DUANZG:=TDXDLL5(8,DUAN,H,L);{输出段中枢高点}
DUANZD:=TDXDLL5(9,DUAN,H,L);{输出笔中枢低点}

{标出段高低点}
DRAWNUMBER(DUAN=1,H,H),COLORFF8000,DRAWABOVE;
DRAWNUMBER(DUAN=-1,L*0.999,L),COLORFF8000;

{画笔中枢}
IF(BIZG,BIZG,DRAWNULL), COLORRED;{画笔中枢高点}
IF(BIZD,BIZD,DRAWNULL), COLORRED;{画笔中枢低点}
STICKLINE(BISE,BIZD,BIZG,0.1,0), COLORRED;{画笔中枢开始结束}
{中枢中轴}
DRAWLINE(BISE,BIZZ,BISE,BIZZ,0),COLORYELLOW;

{画段中枢}
IF(DUANZG,DUANZG,DRAWNULL),COLORFF8000;{画段中枢高点}
IF(DUANZD,DUANZD,DRAWNULL),COLORFF8000;{画段中枢低点}
STICKLINE(DUANSE,DUANZD,DUANZG,0,0),COLORFF8000;{画笔段中枢开始结束}
```
