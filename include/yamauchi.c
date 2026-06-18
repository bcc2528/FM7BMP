/* FM-7 サブCPU メモリマップ
$0000～$3FFF: VRAM青
$4000～$7FFF: VRAM赤
$8000～$BFFF: VRAM緑
$C000～$CFFF: コンソールバッファRAM
$D000～$D37F: ワークRAM
$D380～$D3FF: 共有RAM(メインCPU側: $FC80～$FCFF)
$D400～$D7FF: I/O
$D800～$DFFF: キャラクタROM
$E000～$FFFF: モニタROM
*/

/* YAMAUCHIコマンド
$FC82(サブCPUではD382)に$3Fを書き込み、次の8バイトは'YAMAUCHI'(実際にはFM-8のみで、FM-7以降は何でも可)
を入れることでコマンド列に定義したコードを実行していく
コマンドは4つ
$90: コマンド列終了
$91: ブロック転送 サブCPU転送元アドレス(2バイト) サブCPU転送先アドレス(2バイト) 転送バイト数2バイトを続けて書込む
$92: サブCPUジャンプ サブCPUジャンプ先アドレスを続けて書き込む
$93: サブCPUサブルーチンコール サブCPUルーチン先アドレスを続けて書き込む
*/

/*------------------------------------------------------
  参照関数定義
-------------------------------------------------------*/
extern void  _HALT();
extern void  _SUBRST();

// YAMAUCHIコマンド MOVE（メモリブロック転送）$91
// srcで示されるアドレスから、dstで示されるアドレスに、numバイト分データを転送する
void yamauchi_move(unsigned int src, unsigned int dst, unsigned int num)
{
	_HALT();
#asm
	ldx   #$FC80

	clrb
	stb   0,x
	stb   1,x

	ldb   #$3F ; メンテナンスコマンド
	stb   2,x
	ldb   #$59 ; Y
	stb   3,x
	ldb   #$41 ; A
	stb   4,x
	ldb   #$4D ; M
	stb   5,x
	ldb   #$41 ; A
	stb   6,x
	ldb   #$55 ; U
	stb   7,x
	ldb   #$43 ; C
	stb   8,x
	ldb   #$48 ; H
	stb   9,x
	ldb   #$49 ; I
	stb   10,x
	ldb   #$91 ; ブロック転送
	stb   11,x
	ldd   4,u  ; srcアドレス
	std   12,x
	ldd   6,u  ; dstアドレス
	std   14,x
	ldd   8,u  ; numバイト
	std   16,x
	ldb   #$90 ; コマンド終了
	stb   18,x
#endasm
	_SUBRST();
}


// メインCPU→サブCPU メモリ転送(最大88バイト)
// srcで示されるメインCPUアドレスから、dstで示されるサブCPUアドレスに、numバイト分データを転送する
void yamauchi_write(void *src, unsigned int dst, unsigned int num)
{
	_HALT();
#asm
	ldx   #$FCA8
	ldy   4,u
	ldd   8,u  ; numバイト
	; if(num > 88) num = 88
	cmpd  #88
	ble   _yamauchi_write_loop
	ldd   #88
	std   8,u

_yamauchi_write_loop equ *
	lda   ,y+
	sta   ,x+
	decb
	bne   _yamauchi_write_loop

	ldx   #$FC80

	clrb
	stb   0,x
	stb   1,x

	ldb   #$3F ; メンテナンスコマンド
	stb   2,x
	ldb   #$59 ; Y
	stb   3,x
	ldb   #$41 ; A
	stb   4,x
	ldb   #$4D ; M
	stb   5,x
	ldb   #$41 ; A
	stb   6,x
	ldb   #$55 ; U
	stb   7,x
	ldb   #$43 ; C
	stb   8,x
	ldb   #$48 ; H
	stb   9,x
	ldb   #$49 ; I
	stb   10,x
	ldb   #$93 ; サブルーチンコール。VRAM Access FlagをOn($D409のRead)
	stb   11,x
	ldd   #$D399 ; 
	std   12,x
	ldb   #$91 ; ブロック転送
	stb   14,x
	ldd   #$D3A8  ; srcアドレス
	std   15,x
	ldd   6,u  ; dstアドレス
	std   17,x
	ldd   8,u  ; numバイト
	std   19,x
	ldb   #$93 ; サブルーチンコール。VRAM Access FlagをOff($D409のWrite)
	stb   21,x
	ldd   #$D39D ;
	std   22,x
	ldb   #$90 ; コマンド終了
	stb   24,x
	ldd   #$B6D4 ; VRAM Access FlagをOn($D409のRead) LDA命令 = $B6, $D409, RTS命令 = $39
	std   25,x
	ldd   #$0939 ;
	std   27,x
	ldd   #$B7D4 ; VRAM Access FlagをOn($D409のRead) STA命令 = $B7, $D409, RTS命令 = $39
	std   29,x
	ldd   #$0939 ;
	std   31,x
#endasm
	_SUBRST();
}


// YAMAUCHIコマンド JMP（ジャンプ）$92
// addrアドレスに命令実行をジャンプする
void yamauchi_jmp(unsigned int addr)
{
	_HALT();
#asm
	ldx   #$FC80

	clrb
	stb   0,x
	stb   1,x

	ldb   #$3F ; メンテナンスコマンド
	stb   2,x
	ldb   #$59 ; Y
	stb   3,x
	ldb   #$41 ; A
	stb   4,x
	ldb   #$4D ; M
	stb   5,x
	ldb   #$41 ; A
	stb   6,x
	ldb   #$55 ; U
	stb   7,x
	ldb   #$43 ; C
	stb   8,x
	ldb   #$48 ; H
	stb   9,x
	ldb   #$49 ; I
	stb   10,x
	ldb   #$92 ; ジャンプ
	stb   11,x
	ldd   4,u  ; addrアドレス
	std   12,x
	ldb   #$90 ; コマンド終了
	stb   14,x
#endasm
	_SUBRST();
}


// YAMAUCHIコマンド JSR（サブルーチンコール）$93
// addrアドレスのサブルーチンを呼び出す
void yamauchi_jsr(unsigned int addr)
{
	_HALT();
#asm
	ldx   #$FC80

	clrb
	stb   0,x
	stb   1,x

	ldb   #$3F ; メンテナンスコマンド
	stb   2,x
	ldb   #$59 ; Y
	stb   3,x
	ldb   #$41 ; A
	stb   4,x
	ldb   #$4D ; M
	stb   5,x
	ldb   #$41 ; A
	stb   6,x
	ldb   #$55 ; U
	stb   7,x
	ldb   #$43 ; C
	stb   8,x
	ldb   #$48 ; H
	stb   9,x
	ldb   #$49 ; I
	stb   10,x
	ldb   #$93 ; サブルーチンコール
	stb   11,x
	ldd   4,u  ; addrアドレス
	std   12,x
	ldb   #$90 ; コマンド終了
	stb   14,x
#endasm
	_SUBRST();
}


// PSG音源レジスタに書込み
void psg_write(unsigned int reg, unsigned int data)
{
#asm
	ldx   #$FD0D
	ldb   5,u
	stb   1,x
	ldb   #3
	stb   0,x
	clr   0,x
	ldb   7,u
	stb   1,x
	ldb   #2
	stb   0,x
	clr   0,x
#endasm
}