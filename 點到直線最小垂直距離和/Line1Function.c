#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Headerfile.h"
void Line1Function(Point *Point_ptr,Line1 *Line1_ptr)
{
	float d,m;
	float Total_d;
	float i;
	int j;
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;
	Line1_ptr->SumDis1=0;

	for(i=1;i<=20;i++){
			Total_d=0;
			m=pow(2,i);
		for(j=0;j<50;j++){
			d=fabs(-m*(float)X[j]+(float)Y[j])/pow(pow(m,2.0)+1,0.5);
			Total_d+=d;
			}
		
		if((Line1_ptr->SumDis1)==0||Total_d<(Line1_ptr->SumDis1)){
			Line1_ptr->SumDis1=Total_d;
			Line1_ptr->Line1_m=m;
			}
	}
}
