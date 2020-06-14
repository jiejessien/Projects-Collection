#include <stdio.h>
#include <stdlib.h>
#include "Headerfile.h"

void Draw_Graphtxt(char OPtxtfname[],char *Star)
{
	FILE *fwrite;
	fwrite=fopen(OPtxtfname,"w");
	while(fwrite==NULL){
		printf("FAULT\n");
		printf("Output File Name:\n");
		scanf("%s\n", &OPtxtfname);
		fwrite = fopen(OPtxtfname, "w");
	}
	int i,j;

	for(j=ROW-1;j>=0;j--){
		for(i=0;i<COL;i++){
			if(j!=ROW-1&&i==0)
			fprintf(fwrite,"\n");
			
			fprintf(fwrite,"%c ",Star[j*COL+i]);
		}
	}
	fclose(fwrite);
}
