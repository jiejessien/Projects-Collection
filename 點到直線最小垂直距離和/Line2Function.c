#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Headerfile.h"
void Line2Function(Point *Point_ptr,Line2 *Line2_ptr)
{
	float Diff_Xi_Xavg,Diff_Yi_Yavg;
	float Sum_MultiDxDy=0,Sum_DxSqua=0;
	float Xavg,Yavg,Sum_X=0,Sum_Y=0;
	int i;
	float temp;
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;
	
	for(i=0;i<50;i++){
		Sum_X+=(float)X[i];
		Sum_Y+=(float)Y[i];
	}
	Xavg=Sum_X/50;
	Yavg=Sum_Y/50;

	for(i=0;i<50;i++){
		Diff_Xi_Xavg=(float)X[i]-Xavg;
		Diff_Yi_Yavg=(float)Y[i]-Yavg;
		temp=Diff_Xi_Xavg*Diff_Yi_Yavg;
		Sum_MultiDxDy+=temp;	
		temp=pow(Diff_Xi_Xavg,2);
		Sum_DxSqua+=temp;
	}
	Line2_ptr->Line2_m= Sum_MultiDxDy/Sum_DxSqua;
	Line2_ptr->Line2_b=Yavg-(Line2_ptr->Line2_m)*Xavg;
	
	float y_line;
	Line2_ptr->SumDis2=0;
	for(i=0;i<50;i++){
		y_line=(Line2_ptr->Line2_m)*(float)X[i]+(Line2_ptr->Line2_b);
		temp=fabs((float)Y[i]-y_line);
		Line2_ptr->SumDis2+=temp;
	}
}
