#include <gtk/gtk.h>
#include <stdlib.h>

#define BLACK 0
#define RED 1
#define EMTY 2
typedef struct
{
	GtkWidget *image;
}Chess;
typedef struct
{
	int index;
	int x;
	int y;
}point;
int XYtoIndex(int a,int b);
point indexToXY(int i);

point chuanhoa(int a,int b);
Chess *intBroad(GtkWidget *fixed);
void isMove(int a,int b,Chess *Broad,GtkWidget *fixed,int move);