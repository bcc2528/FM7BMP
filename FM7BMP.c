
#include <stdio.h>

#define BMP_NUM 4

void main()
{
	int i, x, y, p;
	FILE  *fp;
	char pixel[2561];
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
			fgets(pixel, 2561, fp);

			p = 0;
			x = 0;
			do
			{
				pset(x, y, pixel[p] & 7, _PSET);
				pset(x, y + 1, pixel[p + 320] & 7, _PSET);
				pset(x, y + 2, pixel[p + 640] & 7, _PSET);
				pset(x, y + 3, pixel[p + 960] & 7, _PSET);
				pset(x, y + 4, pixel[p + 1280] & 7, _PSET);
				pset(x, y + 5, pixel[p + 1600] & 7, _PSET);
				pset(x, y + 6, pixel[p + 1920] & 7, _PSET);
				pset(x, y + 7, pixel[p + 2240] & 7, _PSET);
				x++;
				pset(x, y, (pixel[p] >> 3) & 7, _PSET);
				pset(x, y + 1, (pixel[p + 320] >> 3) & 7, _PSET);
				pset(x, y + 2, (pixel[p + 640] >> 3) & 7, _PSET);
				pset(x, y + 3, (pixel[p + 960] >> 3) & 7, _PSET);
				pset(x, y + 4, (pixel[p + 1280] >> 3) & 7, _PSET);
				pset(x, y + 5, (pixel[p + 1600] >> 3) & 7, _PSET);
				pset(x, y + 6, (pixel[p + 1920] >> 3) & 7, _PSET);
				pset(x, y + 7, (pixel[p + 2240] >> 3) & 7, _PSET);
				p++;
				x++;
			}while (x < 640);
			y += 8;
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