#include <stdio.h>
#include <stdlib.h>
#include "BmpDataStructure.h"
void Input_Graph(Point *Point_ptr,Line *Line_ptr,
		unsigned char *pixel_ptr,int imgW, int imgH)
{
	int i,j;
	for(i=0;i<imgW;i++){
		for(j=0;j<imgH;j++){
		if(i%imgW==0)
			pixel_ptr[j*imgW+i]=0;
		if(j%imgH==0)
			pixel_ptr[j*imgW+i]=0;	}
	}
	int Fx;
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;
	float *Line_m=(float*)Line_ptr->Line_m;
	float *Line_b=(float*)Line_ptr->Line_b;
	
	for(i=0;i<5;i++)
	pixel_ptr[Y[i]*imgW+X[i]]=0;
	
	for(i=X[3]+1;i<X[0];i++){
		Fx=(int)(Line_m[0]*i+Line_b[0]);
		pixel_ptr[Fx*imgW+i]=0;		
	}
	for(i=X[3]+1;i<X[2];i++){
		Fx=(int)(Line_m[1]*i+Line_b[1]);
		pixel_ptr[Fx*imgW+i]=0;		
	}
	for(i=X[1]+1;i<X[2];i++){
		Fx=(int)(Line_m[2]*i+Line_b[2]);
		pixel_ptr[Fx*imgW+i]=0;		
	}
	for(i=X[1]+1;i<X[4];i++){
		Fx=(int)(Line_m[3]*i+Line_b[3]);
		pixel_ptr[Fx*imgW+i]=0;		
	}
	for(i=X[0]+1;i<X[4];i++){
		Fx=(int)(Line_m[4]*i+Line_b[4]);
		pixel_ptr[Fx*imgW+i]=0;		
	}
}

