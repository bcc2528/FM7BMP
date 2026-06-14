
#include <stdio.h>

#define BMP_NUM 4

/*------------------------------------------------------
  参照関数定義
-------------------------------------------------------*/
extern void  _HALT();
extern void  _SUBRST();
extern int _fgetc(FILE *fs);

void draw_20p_block(int x, int y, char *p)
{
	_HALT();
#asm
	ldx   #$FC82

	; 0x17 コマンド(point)
	ldb   #$17
	stb   0,x

	; 表示点数 20ピクセル
	ldb   #20
	stb   1,x

	; X 座標
	ldd   4,u
	std   2,x
	addd #1
	std   8,x
	addd #1
	std   14,x
	addd #1
	std   20,x
	addd #1
	std   26,x
	addd #1
	std   32,x
	addd #1
	std   38,x
	addd #1
	std   44,x
	addd #1
	std   50,x
	addd #1
	std   56,x
	addd #1
	std   62,x
	addd #1
	std   68,x
	addd #1
	std   74,x
	addd #1
	std   80,x
	addd #1
	std   86,x
	addd #1
	std   92,x
	addd #1
	std   98,x
	addd #1
	std   104,x
	addd #1
	std   110,x
	addd #1
	std   116,x

	; Y 座標
	ldd   6,u
	std   4,x
	std   10,x
	std   16,x
	std   22,x
	std   28,x
	std   34,x
	std   40,x
	std   46,x
	std   52,x
	std   58,x
	std   64,x
	std   70,x
	std   76,x
	std   82,x
	std   88,x
	std   94,x
	std   100,x
	std   106,x
	std   112,x
	std   118,x

	; カラー
	ldy   8,u
	ldb   0,y
	tfr   b,a
	andb  #7
	stb   6,x
	lsra
	lsra
	lsra
	anda  #7
	sta   12,x

	ldb   1,y
	tfr   b,a
	andb  #7
	stb   18,x
	lsra
	lsra
	lsra
	anda  #7
	sta   24,x

	ldb   2,y
	tfr   b,a
	andb  #7
	stb   30,x
	lsra
	lsra
	lsra
	anda  #7
	sta   36,x

	ldb   3,y
	tfr   b,a
	andb  #7
	stb   42,x
	lsra
	lsra
	lsra
	anda  #7
	sta   48,x

	ldb   4,y
	tfr   b,a
	andb  #7
	stb   54,x
	lsra
	lsra
	lsra
	anda  #7
	sta   60,x

	ldb   5,y
	tfr   b,a
	andb  #7
	stb   66,x
	lsra
	lsra
	lsra
	anda  #7
	sta   72,x

	ldb   6,y
	tfr   b,a
	andb  #7
	stb   78,x
	lsra
	lsra
	lsra
	anda  #7
	sta   84,x

	ldb   7,y
	tfr   b,a
	andb  #7
	stb   90,x
	lsra
	lsra
	lsra
	anda  #7
	sta   96,x

	ldb   8,y
	tfr   b,a
	andb  #7
	stb   102,x
	lsra
	lsra
	lsra
	anda  #7
	sta   108,x

	ldb   9,y
	tfr   b,a
	andb  #7
	stb   114,x
	lsra
	lsra
	lsra
	anda  #7
	sta   120,x

	; ファンクションコード _PSET固定
	ldb   #$0
	stb   7,x
	stb   13,x
	stb   19,x
	stb   25,x
	stb   31,x
	stb   37,x
	stb   43,x
	stb   49,x
	stb   55,x
	stb   61,x
	stb   67,x
	stb   73,x
	stb   79,x
	stb   85,x
	stb   91,x
	stb   97,x
	stb   103,x
	stb   109,x
	stb   115,x
	stb   121,x
#endasm
	_SUBRST();
}


void main()
{
	int i, x, y, p;
	FILE  *fp;
	char pixel[640];
	char fname[BMP_NUM][9] = {
		"DOOM",
		"SPACECAT",
		"UMA",
		"FH6"
	};

	width(40, 25);
	console_set(0);

	i = 0;
	while(1)
	{

		if ((fp = fopen(fname[i], "r")) == NULL)
		{
			exit(_DSKERR);
		}

		cls(_BLACK);

		y = 0;
		do
		{
			p = 0;
			do
			{
				pixel[p++] = _fgetc(fp);
			} while(p < 320);

			p = 0;
			x = 0;
			do
			{
				draw_20p_block(x, y, &pixel[p]);
				p+=10;
				x+=20;
			}while (x < 640);
			y++;
		}while (y < 200);

		inkey(1);

		fclose(fp);

		i++;
		if(i >= BMP_NUM)
		{
			i = 0;
		}
	}
}