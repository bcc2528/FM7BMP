#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main(int argc, char* argv[])
{
	FILE* fp;
	BITMAPFILEHEADER bmp_file_header;
	BITMAPINFOHEADER bmp_info_header;
	unsigned int pallet[16];
	unsigned char temp;
	unsigned char* original_image;
	unsigned char* new_image;
	char fname[256];

	if (argc < 2) {
		printf("How to use: %s <filename>\n", argv[0]);
		return 1;
	}

	snprintf(fname, sizeof(fname), "%s", argv[1]);

	fopen_s(&fp, fname, "rb"); // ファイルを開く。失敗するとNULLを返す。
	if (fp == NULL) {
		printf("%s file not open!\n", fname);
		return -1;
	}
	else {
		printf("%s file opened!\n", fname);
	}

	fread(&bmp_file_header, sizeof(BITMAPFILEHEADER), 1, fp); // ファイルヘッダを読み込む。
	if ((bmp_file_header.bfType != 0x4D42) || (bmp_file_header.bfSize != 0xFA76) || (bmp_file_header.bfOffBits != 0x76))
	{
		printf("%s file is not 16 Colors BMP format!\n", fname);
		fclose(fp); // ファイルを閉じる。
		return -1;
	}

	fread(&bmp_info_header, sizeof(BITMAPINFOHEADER), 1, fp); // 情報ヘッダを読み込む。
	if ((bmp_info_header.biSize != 40) || (bmp_info_header.biWidth != 640) || (bmp_info_header.biHeight != 200) ||
		(bmp_info_header.biPlanes != 1) || (bmp_info_header.biBitCount != 4) || (bmp_info_header.biCompression != 0))
	{
		printf("%s file is not 640 * 200 Resolution!\n", fname);
		fclose(fp); // ファイルを閉じる。
		return -1;
	}

	printf("%s file is 16 Colors BMP format!\n", fname);

	original_image = (unsigned char*)malloc(sizeof(unsigned char) * (640 * 200) / 2);
	new_image = (unsigned char*)malloc(sizeof(unsigned char) * 48000);

	fread(pallet, sizeof(unsigned int), 16, fp); // パレットを読み込む。

	fread(original_image, sizeof(unsigned char), (640 * 200) / 2, fp); // 画像データを読み込む。

	fclose(fp); // ファイルを閉じる。

	const unsigned char conversion_table_b[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x80, 0x80, 0x80 };
	const unsigned char conversion_table_r[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0, 0x80, 0, 0x80, 0, 0x80 };
	const unsigned char conversion_table_g[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x80, 0x80, 0, 0, 0x80, 0x80 };

	int x, y, i, j;
	unsigned char r, g, b;
	i = 63999;
	for (y = 0; y < 200; y++)
	{
		for (x = 79; x >= 0; x--)
		{
			r = 0;
			g = 0;
			b = 0;
			for (j = 0; j < 4; j++)
			{
				r >>= 1;
				g >>= 1;
				b >>= 1;
				temp = (original_image[i] & 0xf);
				r |= conversion_table_r[temp];
				g |= conversion_table_g[temp];
				b |= conversion_table_b[temp];
				r >>= 1;
				g >>= 1;
				b >>= 1;
				temp = ((original_image[i] >> 4) & 0xf);
				r |= conversion_table_r[temp];
				g |= conversion_table_g[temp];
				b |= conversion_table_b[temp];
				i--;
			}
			new_image[(y * 240) + x] = b;
			new_image[(y * 240) + 80 + x] = r;
			new_image[(y * 240) + 160 + x] = g;
		}
	}

	char* ext = strrchr(fname, '.');
	if (ext != NULL) {
		// 拡張子を ".dat" に変更
		strcpy_s(ext, 5, ".dat");
	}
	else {
		// 拡張子が無い場合は末尾に追加
		strcat_s(fname, 5, ".dat");
	}

	fopen_s(&fp, fname, "wb");
	fwrite((unsigned char*)new_image, 1, 48000, fp);
	fclose(fp);

	printf("Success!\n");

	return 0;
}