typedef struct
{
	unsigned long	bfType[2];
	unsigned long	bfSize[4];
	unsigned long	bfReserved1[2];
	unsigned long	bfReserved2[2];
	unsigned long	bfOffBits[4];
	//BMP_FILE HEADER
	unsigned long	biSize[4];
	long			biWidth[4];
	long			biHeight[4];
	unsigned long	biPlanes[2];
	unsigned long	biBitCount[2];
	unsigned long	biCompression[4];
	unsigned long	biSizeImage[4];
	unsigned long	biXPelsPerMeter[4];
	unsigned long	biYPelsPerMeter[4];
	unsigned long	biClrUsed[4];
	unsigned long	biClrImportant[4];
	//BMP_INFO HEADER (array)
	int				biWidth_integer;
	int				biHeight_integer;
	//BMP_INFO HEADER (int)
	unsigned char	*bPixel;
	//BMP_Bitmap Data
}BMPHeaderData;

typedef struct
{
	int rgbBlue;
	int rgbGreen;
	int rgbRed;
	int reserved;
	//BMP_Colormap
}RGBQUAD;

typedef struct{
	int* point_x;
	int* point_y;
}Point;

typedef struct{
	float *Line_m;
	float *Line_b;
}Line;

typedef struct
{
	BMPHeaderData	*BMPHeaderDataPtr;
	RGBQUAD			*ColorMap;
	char			BMPFileName[50];
	Point *Point_ptr;
	Line *Line_ptr;
}BMP_DataStructure;

void ReadIPFileText(char *IPCoetxtfilename, char IPbmpfilename[], 
	char OPbmpfilename[], BMPHeaderData *BMP8b_HDptr,Point *Point_ptr);	
void ReadBMPCipher(char *IPbmpfilename, BMPHeaderData *FH_ptr, 
	BMPHeaderData *IH_ptr, RGBQUAD *CM_ptr, int Imgwidth, int Imgheight, 
	unsigned char *bpixel);
void Graph_Operation(Point *Point_ptr,Line *Line_ptr);
void Input_Graph(Point *Point_ptr,Line *Line_ptr,unsigned char *pixel_ptr,
		int imgW, int imgH);
void ReCoverBmpPixel(char *OPbmpfilename, BMPHeaderData *fh_ptr,
	 BMPHeaderData *ih_ptr, RGBQUAD *cm_ptr, 
	 unsigned char *ReCoverS_pixel, int Imgwidth, int Imgheight);

