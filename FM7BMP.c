
#include <stdio.h>

#define BMP_NUM 6

/*------------------------------------------------------
  éQè∆ä÷êîíËã`
-------------------------------------------------------*/
extern void  _HALT();
extern void  _SUBRST();
extern int _fgetc(FILE *fs);


void main()
{
	int i, y, p;
	FILE  *fp;
	char pixel[256];
	char fname[BMP_NUM][9] = {
		"DOOM",
		"SPACECAT",
		"UMA",
		"FH6",
		"SUIREN",
		"FMTOWNS"
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
				pixel[p] = _fgetc(fp);
			} while(++p < 240);

			//Blue plane
			yamauchi_write((char *)pixel, y, 80);

			//Red plane
			yamauchi_write((char *)pixel + 80, 0x4000 + y, 80);

			//Green Plane
			yamauchi_write((char *)pixel + 160, 0x8000 + y, 80);

			y+=80;
		}while (y < 16000);

		inkey(3);

		fclose(fp);

		i++;
		if(i >= BMP_NUM)
		{
			i = 0;
		}
	}
}