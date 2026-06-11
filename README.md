# FM7BMP
Fujitsu FM-7 Bitmap Graphics Demo

富士通の名機FM-7でビットマップグラフィックを行うデモプログラムです。

解像度640*200ドット 8色表示による総原色ショックをお楽しみください。

## 実行の仕方
Releaseに用意してあるFM7BMP.D77 フロッピーディスクイメージをブートさせるだけです。

しばらく待っていると画像が表示され、すべて表示された後にキーボードの何かのキーを押すと次の画像が表示されます。

## サンプル画像
![FM7BMP - DOOM](Screenshots/DOOM.png?raw=true)
![FM7BMP - SPACECAT](Screenshots/NEKO.png?raw=true)
![FM7BMP - UMA](Screenshots/UMA.png?raw=true)
![FM7BMP - FH6](Screenshots/FH6.png?raw=true)

## その他
ブードディスクのIPL・ローダーには山川機長さんの「[Ducky is Back!](https://github.com/captainys/FM/tree/master/7/Demos/2019/src)」のコードを利用させていただきました。

C言語コンパイラにはmalikto999氏の「[6809 クロスCコンパイラ](https://www.vector.co.jp/soft/winnt/prog/se522600.html)」を利用し、標準ライブラリを独自に最適化しました。
