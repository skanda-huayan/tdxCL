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
通達信：
1 編譯好的dll，即tdxCL.dll，放在通達信安裝目錄下的T0002/dlls下。
2 綁定dll到5號（其實幾號都可以，公式裡要做相應的更改即可）。
3 Ctrl-F打開公式管理器，按下面的公式創建公式。
4 。。。開始使用公式～

大智慧：
1 編譯好的dll，即tdxCL.dll，直接放在大智慧的安裝目錄下。
2 打開公式管理，添加公式。
```

#通達信公式#
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
#大智慧公式#
```
bi:="suCLX@BI";
duan:="suCLX@DUANVAR"(bi);

drawline(bi=1,h,bi=-1,l,0),dotline,coloryellow,linethick1;
drawline(bi=-1,l,bi=1,h,0),dotline,coloryellow,linethick1;
drawline(duan=1,h,duan=-1,l,0),colorblue,linethick1;
drawline(duan=-1,l,duan=1,h,0),colorblue,linethick1;
{段高低点}
DRAWTEXT(duan=1, h,''+h), colorred, align1, valign2;
DRAWTEXT(duan=-1, l,''+l), colorgreen, align1;

zszg:="suCLX@ZSZGVAR"(bi);
zszd:="suCLX@ZSZDVAR"(bi);
zsse:="suCLX@ZSSEVAR"(bi);
zszz:=(zszg+zszd)/2;

dzszg:="suCLX@ZSZGVAR"(duan);
dzszd:="suCLX@ZSZDVAR"(duan);
dzsse:="suCLX@ZSSEVAR"(duan);

DRAWLINE(zsse=1, zszg, zsse=2, zszg, 0), colorred, linethick1;
DRAWLINE(zsse=1, zszd, zsse=2, zszd, 0), colorred, linethick1;
STICKLINE(zsse=1, zszg, zszd, 1, 0), colorred, linethick1;
STICKLINE(zsse=2, zszg, zszd, 1, 0), colorred, linethick1;
DRAWLINE(zsse=1, zszz, zsse=2, zszz, 0), coloryellow;

DRAWLINE(dzsse=1, dzszg, dzsse=2, dzszg, 0), colorblue, linethick1;
DRAWLINE(dzsse=1, dzszd, dzsse=2, dzszd, 0), colorblue, linethick1;
STICKLINE(dzsse=1, dzszg, dzszd, 1, -501), colorblue, linethick1;
STICKLINE(dzsse=2, dzszg, dzszd, 1, 501), colorblue, linethick1;
```
