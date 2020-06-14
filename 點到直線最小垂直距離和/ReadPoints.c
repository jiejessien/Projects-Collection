#include <stdio.h>
#include <stdlib.h>
#include "Headerfile.h"
void ReadPoints(char IPtxtfname[],char OPtxtfname[],Point *Point_ptr)
 {
	FILE *fpoint;
	fpoint=fopen(IPtxtfname,"r");
	while(fpoint==NULL){
		printf("FAULT\n");
		printf("Input File Name:\n");
		scanf("%s\n", &IPtxtfname);
		fpoint = fopen(IPtxtfname, "r");
	}
	char buffer[350];
	fgets(buffer,350,fpoint);
	fscanf(fpoint,"%s\n",OPtxtfname);
	fgets(buffer,350,fpoint);
	Point_ptr->point_x=(int*)malloc(sizeof(int)*50);
	Point_ptr->point_y=(int*)malloc(sizeof(int)*50);
	int *X=(int*)Point_ptr->point_x;
	int *Y=(int*)Point_ptr->point_y;

	int i;
	for(i=0;i<50;i++)
		fscanf(fpoint,"(%d,%d)\n",&X[i],&Y[i]);
	fclose(fpoint);
}
