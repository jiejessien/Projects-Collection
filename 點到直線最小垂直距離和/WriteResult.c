#include <stdio.h>
#include <stdlib.h>
#include "Headerfile.h"
void WriteResult(char OPtxtfname[],Line1 *Line1_ptr,Line2 *Line2_ptr)
{
	FILE *fwrite;
	fwrite=fopen(OPtxtfname,"w");
	while(fwrite==NULL){
		printf("FAULT\n");
		printf("Output File Name:\n");
		scanf("%s\n", &OPtxtfname);
		fwrite = fopen(OPtxtfname, "w");
	}
	float Diff;
	fprintf(fwrite,"===================¿é¥Xµ²ªG===================\n");
	Diff=(Line2_ptr->SumDis2)-(Line1_ptr->SumDis1);
	fprintf(fwrite,"Line1: y = %.2fx\n",Line1_ptr->Line1_m);
	fprintf(fwrite,"SumDis1 = %.2f\n",Line1_ptr->SumDis1);
	fprintf(fwrite,"Line2: y = %.2fx + %.2f\n",
	Line2_ptr->Line2_m,Line2_ptr->Line2_b);
	fprintf(fwrite,"SumDis2 = %.2f\n",Line2_ptr->SumDis2);
	fprintf(fwrite,"Diff = SumDis2 - SumDis1\n     = %.2f - %.2f = %.2f",
	Line2_ptr->SumDis2,Line1_ptr->SumDis1,Diff);
	printf("Diff = SumDis2 - SumDis1\n     = %.2f - %.2f = %.2f",
	Line2_ptr->SumDis2,Line1_ptr->SumDis1,Diff);
	
	fclose(fwrite);
}
