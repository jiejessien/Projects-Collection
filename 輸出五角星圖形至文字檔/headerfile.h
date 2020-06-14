#include <stdio.h>
#include <stdlib.h>
#define ROW 80
#define COL 70
typedef struct{
	int* point_x;
	int* point_y;
}Point;
typedef struct{
	float *Line_m;
	float *Line_b;
}Line;
typedef struct{
	Point *Point_ptr;
	Line *Line_ptr;
	char *Star;	 
}Datastruct;

void ReadPoints(char IPtxtfname[],char OPtxtfname[],Point *Point_ptr);
void Graph_Operation(Point *Point_ptr,Line *Line_ptr);
void Input_Graph(Point *Point_ptr,Line *Line_ptr,char *Star);
void Draw_Graphtxt(char OPtxtfname[],char *Star);


