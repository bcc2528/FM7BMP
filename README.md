# FM7BMP
Fujitsu FM-7 Bitmap Graphics Demo

富士通の名機FM-7でビットマップグラフィックを行うデモプログラムです。

解像度640*200ドット 8色表示による総天然ショックならぬ総原ショックをお楽しみください。

## 実行の仕方
Releaseに用意してあるFM7BMP.D77 フロッピーディスクイメージをブートさせるだけです。

しばらく待っていると画像が表示され、すべて表示された後にキーボードの何かのキーを押すと次の画像が表示されます。

## サンプル画像
![FM7BMP - DOOM](Screenshots/DOOM.png?raw=true)
![FM7BMP - SPACECAT](Screenshots/NEKO.png?raw=true)
![FM7BMP - UMA](Screenshots/UMA.png?raw=true)
![FM7BMP - FH6](Screenshots/FH6.png?raw=true)

## 謝辞
ブードディスクのIPL・ローダーには山川機長さんの「[Ducky is Back!](https://github.com/captainys/FM/tree/master/7/Demos/2019/src)」のコードを利用させていただきました。

C言語コンパイラにはmalikto999氏の「[6809 クロスCコンパイラ](https://www.vector.co.jp/soft/winnt/prog/se522600.html)」を利用し、標準ライブラリを独自に最適化しました。

## おまけ
includeフォルダ内に「6809 クロスCコンパイラ」で使用可能なYAMAUCHIコマンドを読み出す関数、PSG音源レジスタに書き込みを行う関数を書いたライブラリを用意しました。

6809 クロスCコンパイラのincludeフォルダ内にyamauchi.h・yamauchi.cをコピーし、ファイル「MCC.exe.config」をテキストエディタで開き、add key="LibFiles"の項目のvalue=""に「;yamauchi.c」を追加してください。

使いたいCソースコードに「#include <yamauchi.h>」を記述することで関数を読み出せます。

使い方に関してはyamauchi.cを読んでみてください。
