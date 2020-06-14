#include <stdio.h>
#include <stdlib.h>
#include "Headerfile.h"

int main(int argc, char *argv[]) {
	char IPtxt_Filename[350]="InputPoint1.txt";
	char OPtxt_Filename[350];
	Datastruct *Datastruct_DS=(Datastruct*)malloc(sizeof(Datastruct));
	Datastruct_DS->Point_ptr=(Point*)malloc(sizeof(Point));
	Datastruct_DS->Line_ptr=(Line*)malloc(sizeof(Line));
	
	ReadPoints(IPtxt_Filename,OPtxt_Filename,Datastruct_DS->Point_ptr);
	printf("ReadPoints Success\n");
	printf("¿é¥XÀÉÀÉ¦W: %s\n",OPtxt_Filename);
	printf("B(%d,%d)\n",
		Datastruct_DS->Point_ptr->point_x[1],Datastruct_DS->Point_ptr->point_y[1]);
	printf("C(%d,%d)\n",
		Datastruct_DS->Point_ptr->point_x[2],Datastruct_DS->Point_ptr->point_y[2]);
		
	Graph_Operation(Datastruct_DS->Point_ptr,Datastruct_DS->Line_ptr);
	printf("Graph_Operation Success.\n");
	
	Datastruct_DS->Star=(char*)malloc(sizeof(char)*ROW*COL);
	Input_Graph(Datastruct_DS->Point_ptr,Datastruct_DS->Line_ptr,Datastruct_DS->Star);
	printf("Input_Graph Success.\n");
	
	Draw_Graphtxt(OPtxt_Filename,Datastruct_DS->Star);
	printf("Draw_Graphtxt Success.\n");
	
	free(Datastruct_DS->Point_ptr);
	free(Datastruct_DS->Line_ptr);
	free(Datastruct_DS);
	return 0;
}
