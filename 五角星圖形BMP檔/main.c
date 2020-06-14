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
	printf("   BMP�v���e��=%d	BMP�v������=%d\n"
		,BMP_8bit->BMPHeaderDataPtr->biWidth_integer,
		BMP_8bit->BMPHeaderDataPtr->biHeight_integer);
	printf("   B�I�y�� : B(%d,%d)\n"
			,BMP_8bit->Point_ptr->point_x[1],BMP_8bit->Point_ptr->point_y[1]);
	printf("   C�I�y�� : C(%d,%d)\n"
			,BMP_8bit->Point_ptr->point_x[2],BMP_8bit->Point_ptr->point_y[2]);
	 
	int Imgwidth, Imgheight; //Ū�� IPCoefficient.txt �o�쪺BMP�v�����e�� 
	Imgwidth = BMP_8bit->BMPHeaderDataPtr->biWidth_integer;
	Imgheight = BMP_8bit->BMPHeaderDataPtr->biHeight_integer;
	
	BMP_8bit->BMPHeaderDataPtr->bPixel = 
		(unsigned char*)malloc(sizeof(unsigned char)*Imgwidth*Imgheight);
	//�t�m�����j�p���O����Ŷ��� Bmp Image���Ҧ�pixel 
	
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


