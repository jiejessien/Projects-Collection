#include <stdio.h>
#include <stdlib.h>
#include "BmpDataStructure.h"

void ReadIPFileText(char *IPCoetxtfilename, char IPbmpfilename[], 
	char OPbmpfilename[], BMPHeaderData *BMP8b_HDptr,Point *Point_ptr)
{
	FILE *fin;
	fin = fopen(IPCoetxtfilename, "r+");
	while(fin == NULL)
	{
		printf("%s is no exist.\n", IPCoetxtfilename);
		printf("Input IOPtxt file name:\n");
		scanf("%s\n", &IPCoetxtfilename);
		fin = fopen(IPCoetxtfilename, "r+");
	}
	char buffer[350];
	
	fgets(buffer, 350, fin);
	fscanf(fin, "%s\n", IPbmpfilename);
	//BMP Input filename
	
	fgets(buffer, 350, fin);
	fscanf(fin, "%s\n", OPbmpfilename);
	//BMP Output filename
	
	fgets(buffer, 350, fin);
	fscanf(fin, "%d\n", &BMP8b_HDptr->biWidth_integer);
	//BMP Image Width
	
	fgets(buffer, 350, fin);
	fscanf(fin, "%d\n", &BMP8b_HDptr->biHeight_integer);
	//BMP Image Height
	
	Point_ptr->point_x=(int*)malloc(sizeof(int)*5);
	Point_ptr->point_y=(int*)malloc(sizeof(int)*5);
	
	fgets(buffer,350,fin);
	fscanf(fin,"(%d,%d)\n",&Point_ptr->point_x[1],&Point_ptr->point_y[1]);
	fgets(buffer,350,fin);
	fscanf(fin,"(%d,%d)\n",&Point_ptr->point_x[2],&Point_ptr->point_y[2]);
	
	fclose(fin);
}

