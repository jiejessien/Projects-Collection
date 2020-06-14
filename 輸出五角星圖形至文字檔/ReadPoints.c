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
	
	Point_ptr->point_x=(int*)malloc(sizeof(int)*5);
	Point_ptr->point_y=(int*)malloc(sizeof(int)*5);
	
	fgets(buffer,350,fpoint);
	fscanf(fpoint,"(%d,%d)\n",&Point_ptr->point_x[1],&Point_ptr->point_y[1]);
	fgets(buffer,350,fpoint);
	fscanf(fpoint,"(%d,%d)\n",&Point_ptr->point_x[2],&Point_ptr->point_y[2]);
	
	fclose(fpoint);	
}
