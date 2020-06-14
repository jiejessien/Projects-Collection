#include <stdio.h>
#include <stdlib.h>
#include "BmpDataStructure.h"

int main(int argc, char *argv[])
{
	char IPCoetxtfilename[350];
	char IPbmpfilename[350];
	char OPbmpfilename[350];
	int i, j;
	
	BMP_DataStructure *BMP_8bit 
			= (BMP_DataStructure*)malloc(sizeof(BMP_DataStructure));
	BMP_8bit->BMPHeaderDataPtr 
			= (BMPHeaderData*)malloc(sizeof(BMPHeaderData));
	BMP_8bit->ColorMap = (RGBQUAD*)malloc(sizeof(RGBQUAD)*256);
	BMP_8bit->Point_ptr = (Point*)malloc(sizeof(Point));
	BMP_8bit->Line_ptr = (Line*)malloc(sizeof(Line));
	
	ReadIPFileText("IPBmpFile3.txt", IPbmpfilename, OPbmpfilename, 
		BMP_8bit->BMPHeaderDataPtr,BMP_8bit->Point_ptr);
	
	printf("IPBmpFile txt Read Success...\n");
	printf("   Input BMP : %s\n",IPbmpfilename);
	printf("   Output BMP : %s\n",OPbmpfilename);
	printf("   BMP影像寬度=%d	BMP影像高度=%d\n"
		,BMP_8bit->BMPHeaderDataPtr->biWidth_integer,
		BMP_8bit->BMPHeaderDataPtr->biHeight_integer);
	printf("   B點座標 : B(%d,%d)\n"
			,BMP_8bit->Point_ptr->point_x[1],BMP_8bit->Point_ptr->point_y[1]);
	printf("   C點座標 : C(%d,%d)\n"
			,BMP_8bit->Point_ptr->point_x[2],BMP_8bit->Point_ptr->point_y[2]);
	 
	int Imgwidth, Imgheight; //讀取 IPCoefficient.txt 得到的BMP影像之寬高 
	Imgwidth = BMP_8bit->BMPHeaderDataPtr->biWidth_integer;
	Imgheight = BMP_8bit->BMPHeaderDataPtr->biHeight_integer;
	
	BMP_8bit->BMPHeaderDataPtr->bPixel = 
		(unsigned char*)malloc(sizeof(unsigned char)*Imgwidth*Imgheight);
	//配置對應大小的記憶體空間給 Bmp Image的所有pixel 
	
	ReadBMPCipher(IPbmpfilename, BMP_8bit->BMPHeaderDataPtr, 
			BMP_8bit->BMPHeaderDataPtr, BMP_8bit->ColorMap, 
			Imgwidth, Imgheight, BMP_8bit->BMPHeaderDataPtr->bPixel);
	printf("BMP Cipher Read Success...\n");
	
	Graph_Operation(BMP_8bit->Point_ptr,BMP_8bit->Line_ptr);
	printf("Graph Operation Success...\n");
	
	Input_Graph(BMP_8bit->Point_ptr,BMP_8bit->Line_ptr,
			BMP_8bit->BMPHeaderDataPtr->bPixel, Imgwidth, Imgheight);
	printf("Input_Graph Success...\n");

	ReCoverBmpPixel(OPbmpfilename, BMP_8bit->BMPHeaderDataPtr, 
			BMP_8bit->BMPHeaderDataPtr,BMP_8bit->ColorMap ,
			BMP_8bit->BMPHeaderDataPtr->bPixel, Imgwidth, Imgheight);
	printf("ReCover Bmp Pixel Success...\n");
	
	free(BMP_8bit->Point_ptr);
	free(BMP_8bit->Line_ptr);
	free(BMP_8bit->ColorMap);
	free(BMP_8bit->BMPHeaderDataPtr);
	free(BMP_8bit);
	return 0;
}


