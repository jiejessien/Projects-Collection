#include <stdio.h>
#include <stdlib.h>
#include "Headerfile.h"
int main() {
	char IPtxt_Filename[350]="InputPoint.txt";
	char OPtxt_Filename[350];
	Datastruct *Datastruct_DS=(Datastruct*)malloc(sizeof(Datastruct));
	Datastruct_DS->Point_ptr=(Point*)malloc(sizeof(Point));
	Datastruct_DS->Line1_ptr=(Line1*)malloc(sizeof(Line1));
	Datastruct_DS->Line2_ptr=(Line2*)malloc(sizeof(Line2));

	ReadPoints(IPtxt_Filename,OPtxt_Filename,Datastruct_DS->Point_ptr);
	printf("--輸入座標點文字檔: %s\n",IPtxt_Filename) ;
	printf("--輸出運算結果文字檔: %s\n",OPtxt_Filename);
	printf("--輸入50個座標點:\n");
	int i;
	for(i=0;i<50;i++){
		printf("(%3d ,%4d )	",Datastruct_DS->Point_ptr->point_x[i],
			Datastruct_DS->Point_ptr->point_y[i]);
		if(i%5==4&&i!=0)
			printf("\n");
	}
	Line1Function(Datastruct_DS->Point_ptr,Datastruct_DS->Line1_ptr);
	printf("Line1: y=%.1fx\n",Datastruct_DS->Line1_ptr->Line1_m);
	printf("SumDis1 = %.2f\n",Datastruct_DS->Line1_ptr->SumDis1);
	Line2Function(Datastruct_DS->Point_ptr,Datastruct_DS->Line2_ptr);
	printf("Line2: y=%.1fx+%.1f\n",Datastruct_DS->Line2_ptr->Line2_m,
		Datastruct_DS->Line2_ptr->Line2_b);
	printf("SumDis2 = %.2f\n",Datastruct_DS->Line2_ptr->SumDis2);
	
	WriteResult(OPtxt_Filename,Datastruct_DS->Line1_ptr,
		Datastruct_DS->Line2_ptr);
	
	free(Datastruct_DS->Point_ptr);
	free(Datastruct_DS->Line1_ptr);
	free(Datastruct_DS->Line2_ptr);
	free(Datastruct_DS);
	return 0;
}
