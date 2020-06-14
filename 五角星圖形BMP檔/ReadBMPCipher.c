#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "BmpDataStructure.h"

void ReadBMPCipher(char *IPbmpfilename, BMPHeaderData *FH_ptr, 
	BMPHeaderData *IH_ptr, RGBQUAD *CM_ptr, int Imgwidth, int Imgheight, 
	unsigned char *bpixel)
{
	ReadBMPCipher_FH(IPbmpfilename, FH_ptr);
	ReadBMPCipher_IH(IPbmpfilename, IH_ptr, Imgwidth, Imgheight);
	ReadBMPCipher_CM(IPbmpfilename, CM_ptr);
	ReadBMPCipher_DB(IPbmpfilename, Imgwidth, Imgheight, bpixel);
}

void ReadBMPCipher_FH(char *IPbmpfilename, BMPHeaderData *FH_ptr)
{
	FILE *fin2;
	fin2 = fopen(IPbmpfilename, "rb+"); //rb為讀取二進制檔案
	while(fin2 == NULL)
	{
		printf("%s is no exist.\n", IPbmpfilename);
		printf("Input IP BMP file name:\n");
		scanf("%s\n", &IPbmpfilename);
		fin2 = fopen(IPbmpfilename, "rb+");
	}
	
	int i, j, x;
	char BYTE_FileHeader[14];	//儲存BMP暗碼的陣列 
	
	//----------File Header--------------//
	fread(BYTE_FileHeader, 1, 14, fin2); 
	//int fread(char *buffer, int size, int count, FILE *fp);
	//Buffer為讀入資料要存放的地方，
	//size是讀入的每一筆資料長度(byte)，count為讀入的筆數
	for(x=0;x<2;x++)
		FH_ptr->bfType[x] = BYTE_FileHeader[x];
	for(x=0;x<4;x++)
		FH_ptr->bfSize[x] = BYTE_FileHeader[x+2];
	for(x=0;x<2;x++)
		FH_ptr->bfReserved1[x] = BYTE_FileHeader[x+6];
	for(x=0;x<2;x++)
		FH_ptr->bfReserved2[x] = BYTE_FileHeader[x+8];
	for(x=0;x<4;x++)
		FH_ptr->bfOffBits[x] = BYTE_FileHeader[x+10];	
	fclose(fin2);
}

void ReadBMPCipher_IH(char *IPbmpfilename, BMPHeaderData *IH_ptr,
	 int Imgwidth, int Imgheight)
{
	FILE *fin3;
	fin3 = fopen(IPbmpfilename, "rb"); //rb為讀取二進制檔案 
	while(fin3 == NULL)
	{
		printf("%s is no exist.\n", IPbmpfilename);
		printf("Input IP BMP file name:\n");
		scanf("%s\n", &IPbmpfilename);
		fin3 = fopen(IPbmpfilename, "rb");
	}
	
	int i, j, x;
	char BYTE_InfoHeader[40];
	//----------Info Header--------------//
	fseek(fin3, 14, SEEK_SET);
	fread(BYTE_InfoHeader, 1, 40, fin3); 
	
	for(x=0;x<4;x++)
	{
		IH_ptr->biSize[x] = BYTE_InfoHeader[x];
		IH_ptr->biWidth[x] = BYTE_InfoHeader[x+4];
		IH_ptr->biHeight[x] = BYTE_InfoHeader[x+8];
		IH_ptr->biCompression[x] = BYTE_InfoHeader[x+16];
		IH_ptr->biSizeImage[x] = BYTE_InfoHeader[x+20];
		IH_ptr->biXPelsPerMeter[x] = BYTE_InfoHeader[x+24];
		IH_ptr->biYPelsPerMeter[x] = BYTE_InfoHeader[x+28];
		IH_ptr->biClrUsed[x] = BYTE_InfoHeader[x+32];
		IH_ptr->biClrImportant[x] = BYTE_InfoHeader[x+36];
	}
	for(x=0;x<2;x++)
	{
		IH_ptr->biPlanes[x] = BYTE_InfoHeader[x+12];
		IH_ptr->biBitCount[x] = BYTE_InfoHeader[x+14];
	}
	
	fclose(fin3);
}

void ReadBMPCipher_CM(char *IPbmpfilename, RGBQUAD *CM_ptr)
{
	FILE *fin4;
	fin4 = fopen(IPbmpfilename, "rb"); //rb為讀取二進制檔案 
	while(fin4 == NULL)
	{
		printf("%s is no exist.\n", IPbmpfilename);
		printf("Input IP BMP file name:\n");
		scanf("%s\n", &IPbmpfilename);
		fin4 = fopen(IPbmpfilename, "rb");
	}
	
	int i, j, x;
	unsigned char BYTE_ColorMap[1024];
	//----------Color Map--------------//
	fseek(fin4, 54, SEEK_SET);
	fread(BYTE_ColorMap, 1, 1024, fin4); 
	
	for(i=0 ; i<256 ; i++)
	{
		CM_ptr[i].rgbBlue = BYTE_ColorMap[i*4];
		CM_ptr[i].rgbGreen = BYTE_ColorMap[i*4+1];
		CM_ptr[i].rgbRed = BYTE_ColorMap[i*4+2];
		CM_ptr[i].reserved = BYTE_ColorMap[i*4+3];
	}
	
	fclose(fin4);
}

void ReadBMPCipher_DB(char *IPbmpfilename, int Imgwidth, 
	int Imgheight, unsigned char *bpixel)
{
	FILE *fin5;
	fin5 = fopen(IPbmpfilename, "rb"); //rb為讀取二進制檔案 
	while(fin5 == NULL)
	{
		printf("%s is no exist.\n", IPbmpfilename);
		printf("Input IP BMP file name:\n");
		scanf("%s\n", &IPbmpfilename);
		fin5 = fopen(IPbmpfilename, "rb");
	}
	//----------Bitmap Data Block--------------//
	int SizePixel = Imgwidth*Imgheight;
	int w, h;
	
	unsigned char BYTE_Pixel[SizePixel];
	fseek(fin5, 1078, SEEK_SET);  
	//1078 = 14 + 40 + 32*32 = 14 + 40 + 1024 
	fread(BYTE_Pixel, 1, SizePixel, fin5);
	for(h=0;h<Imgheight;h++)
	{
		for(w=0;w<Imgwidth;w++)
		{
			bpixel[w+h*Imgwidth] = BYTE_Pixel[w+h*Imgwidth];
		}
	}
	fclose(fin5);
}

