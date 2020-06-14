#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Headerfile.h"

void Input_Graph(Point *Point_ptr,Line *Line_ptr,char *Star){	
	int i,j;
	for(i=0;i<COL;i++){
		for(j=0;j<ROW;j++){
		if(i%COL==0)
			Star[j*COL+i]='|';
		else if(j%ROW==0)
			Star[j*COL+i]='_';	
		else
			Star[j*COL+i]=' ';
		}
	}
	int Fx;
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;
	float *Line_m=(float*)Line_ptr->Line_m;
	float *Line_b=(float*)Line_ptr->Line_b;
	
	for(i=0;i<5;i++)
	Star[Y[i]*COL+X[i]]='*';
	
	for(i=X[3]+1;i<X[0];i++){
		Fx=(int)(Line_m[0]*i+Line_b[0]);
		Star[Fx*COL+i]='*';		
	}
	for(i=X[3]+1;i<X[2];i++){
		Fx=(int)(Line_m[1]*i+Line_b[1]);
		Star[Fx*COL+i]='*';		
	}
	for(i=X[1]+1;i<X[2];i++){
		Fx=(int)(Line_m[2]*i+Line_b[2]);
		Star[Fx*COL+i]='*';		
	}
	for(i=X[1]+1;i<X[4];i++){
		Fx=(int)(Line_m[3]*i+Line_b[3]);
		Star[Fx*COL+i]='*';		
	}
	for(i=X[0]+1;i<X[4];i++){
		Fx=(int)(Line_m[4]*i+Line_b[4]);
		Star[Fx*COL+i]='*';		
	}
}
