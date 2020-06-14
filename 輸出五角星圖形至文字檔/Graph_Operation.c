#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Headerfile.h"
#define PI 3.14159265
void Graph_Operation(Point *Point_ptr,Line *Line_ptr){
	Find_ADE(Point_ptr); 
	Def_Line(Point_ptr,Line_ptr);
} 
void Find_ADE(Point *Point_ptr){ //X.Y  0:A , 1:B , 2:C , 3:D , 4:E
	int tri_a;
	float transRad,tri_b;
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;
	
	transRad=PI/180;
	tri_a=X[2]-X[1]; //Cx-Bx
	tri_b=2*tri_a*cos(72*transRad);
	
	X[3]=X[1]+(int)(tri_b*cos(72*transRad));
	Y[3]=Y[1]-(int)(tri_b*sin(72*transRad));

	X[4]=X[2]-(int)(tri_b*cos(72*transRad));
	Y[4]=Y[3];
	
	X[0]=(int)((X[1]+X[2])/2);
	Y[0]=Y[3]+(int)tri_a*sin(72*transRad);
	
	printf("A(%d,%d)\n",X[0],Y[0]);	
	printf("D(%d,%d)\n",X[3],Y[3]);
	printf("E(%d,%d)\n",X[4],Y[4]);
}
void Def_Line(Point *Point_ptr,Line *Line_ptr){
	/* Line[0]:Line_AD		Line[1]:Line_DC
	   Line[2]:Line_CB		Line[3]:Line_BE
	   Line[4]:Line_EA */
	Line_ptr->Line_m=(float*)malloc(sizeof(float)*5);
	Line_ptr->Line_b=(float*)malloc(sizeof(float)*5);
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;
	float *Line_m=(float*)Line_ptr->Line_m;
	float *Line_b=(float*)Line_ptr->Line_b;
	// X.Y	0:A , 1:B , 2:C , 3:D , 4:E
	Line_m[0]=(float)(Y[0]-Y[3])/(X[0]-X[3]);
	Line_b[0]=Y[0]-Line_m[0]*X[0];
	
	Line_m[1]=(float)(Y[3]-Y[2])/(X[3]-X[2]);
	Line_b[1]=Y[3]-Line_m[1]*X[3];
	
	Line_m[2]=(float)(Y[2]-Y[1])/(X[2]-X[1]);
	Line_b[2]=Y[2]-Line_m[2]*X[2];
	
	Line_m[3]=(float)(Y[1]-Y[4])/(X[1]-X[4]);
	Line_b[3]=Y[1]-Line_m[3]*X[1];
	
	Line_m[4]=(float)(Y[4]-Y[0])/(X[4]-X[0]);
	Line_b[4]=Y[0]-Line_m[4]*X[0];
	
	printf("Line_AD: y=%.2fx+%.2f\n",Line_m[0],Line_b[0]);
	printf("Line_DC: y=%.2fx+%.2f\n",Line_m[1],Line_b[1]);
	printf("Line_CB: y=%.2fx+%.2f\n",Line_m[2],Line_b[2]);
	printf("Line_BE: y=%.2fx+%.2f\n",Line_m[3],Line_b[3]);
	printf("Line_EA: y=%.2fx+%.2f\n",Line_m[4],Line_b[4]);
}
