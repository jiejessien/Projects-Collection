#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int* point_x;
	int* point_y;
}Point;
typedef struct{
	float Line1_m;
	float SumDis1;
}Line1;

typedef struct{
	float Line2_m;
	float Line2_b;
	float SumDis2;	
}Line2;
typedef struct{
	Point *Point_ptr;
	Line1 *Line1_ptr;
	Line2 *Line2_ptr;
}Datastruct;
void ReadPoints(char IPtxtfname[],char OPtxtfname[],Point *Point_ptr);
void Line1Function(Point *Point_ptr,Line1 *Line1_ptr);
void Line2Function(Point *Point_ptr,Line2 *Line2_ptr);
void WriteResult(char OPtxtfname[],Line1 *Line1_ptr,Line2 *Line2_ptr);
