#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BmpDataStructure.h"

void ReCoverBmpPixel(char *OPbmpfilename, BMPHeaderData *fh_ptr,
	 BMPHeaderData *ih_ptr, RGBQUAD *cm_ptr, 
	 unsigned char *ReCoverS_pixel, int Imgwidth, int Imgheight)
{
	FILE *OP_text;
	OP_text = fopen(OPbmpfilename, "wb");
	while(OP_text == NULL)
	{
		printf("%s is no exist.\n", OPbmpfilename);
		printf("Input IP BMP file name:\n");
		scanf("%s\n", &OPbmpfilename);
		OP_text = fopen(OPbmpfilename, "wb");
	}
	
	int i;
	for(i=0 ; i<2 ; i++)
		fwrite(&fh_ptr->bfType[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&fh_ptr->bfSize[i], 1, 1, OP_text);
	for(i=0 ; i<2 ; i++)
		fwrite(&fh_ptr->bfReserved1[i], 1, 1, OP_text);
	for(i=0 ; i<2 ; i++)
		fwrite(&fh_ptr->bfReserved2[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&fh_ptr->bfOffBits[i], 1, 1, OP_text);
	//BMP_FILE HEADER
	
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biSize[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biWidth[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biHeight[i], 1, 1, OP_text);
	for(i=0 ; i<2 ; i++)
		fwrite(&ih_ptr->biPlanes[i], 1, 1, OP_text);
	for(i=0 ; i<2 ; i++)
		fwrite(&ih_ptr->biBitCount[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biCompression[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biSizeImage[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biXPelsPerMeter[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biYPelsPerMeter[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biClrUsed[i], 1, 1, OP_text);
	for(i=0 ; i<4 ; i++)
		fwrite(&ih_ptr->biClrImportant[i], 1, 1, OP_text);
	//BMP_Info HEADER
	
	unsigned char ColorM[1024];
	for(i=0 ; i<256 ; i++)
	{
		ColorM[i*4] = cm_ptr[i].rgbBlue;
		ColorM[i*4+1] = cm_ptr[i].rgbGreen;
		ColorM[i*4+2] = cm_ptr[i].rgbRed;
		ColorM[i*4+3] = cm_ptr[i].reserved;
	}
	for(i=0 ; i<1024 ; i++)
		fwrite(&ColorM[i], 1, 1, OP_text);
	//BMP_Colormap
		
	int size = Imgwidth*Imgheight;

	for(i=0 ; i<size ; i++)
	{
		fwrite(&ReCoverS_pixel[i], 1, 1, OP_text);
	}
	//BMP_Bitmap Data Block
	fclose(OP_text);
}


