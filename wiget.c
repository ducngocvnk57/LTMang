#include "wiget.h"

int XYtoIndex(int a,int b) //Tu xy xac dinh diem
{
	int i,j;
	i = (a-25)/60; // xac dinh toa do x 
    j = (b-25)/60;	// xac dinh toa do y
   	i = j*9 + i; // xac dinh chi so trong mang 90 phan tu
   	return i;
}
point indexToXY(int i) //Tu xy xac dinh diem
{
	point a;
	int temp;
	int j;
	temp = i%9;
	j = (i-temp)/9;
	a.x = temp*60 + 25;
	a.y = j*60 + 25;
   	return a;
}
point chuanhoa(int a,int b){ //xac dinh vi tri click trong mang
	point index;
	int i = (int)(a-55)%60 ;
	int j = (int)(b-55)%60 ;
	if(i<30)
		a = a-i-30;
	else
		a = a-i+30; 
	
	if(j<30)
		b = b-j-30;
	else
		b = b-j+30;
	index.x = a;
	index.y = b;
	index.index = XYtoIndex(index.x,index.y);
	return index; 
}
void isMove(int a,int b,Chess *Broad,GtkWidget *fixed,int move)
{
	point clicked;
	clicked = chuanhoa(a,b);
	int i = clicked.index;
	a = clicked.x;b=clicked.y;
   	if(Broad[i].image !=NULL){
   		gtk_widget_destroy(Broad[i].image);
   	}
   		Broad[i].image = Broad[move].image;
   		Broad[move].image = NULL;
   		gtk_fixed_move(GTK_FIXED(fixed),Broad[i].image,a,b);
}

Chess *intBroad(GtkWidget *fixed){ //Khoi tao ban co
GtkWidget *image;
Chess *a = (Chess *)malloc(90*sizeof(Chess));
int i,x,y;
image = gtk_image_new_from_file ("images/bg.gif");
gtk_fixed_put(GTK_FIXED(fixed),image,0,0);
for(i=0;i<90;i++){
		switch(i){
			//quan den
			case 0://xe 
			case 8:
			 	a[i].image = gtk_image_new_from_file ("images/007.gif");
			 	break;
			case 1://ma
			case 7:
				a[i].image = gtk_image_new_from_file ("images/005.gif");
				break;
			case 2://tuong
			case 6:
				a[i].image = gtk_image_new_from_file ("images/004.gif");
				break;
			case 3://si
			case 5:
				a[i].image = gtk_image_new_from_file ("images/002.gif");
				break;
			case 4://phao
				a[i].image = gtk_image_new_from_file ("images/000.gif");break;
			case 19:
			case 25:
				a[i].image = gtk_image_new_from_file ("images/009.gif");break;
			case 27://tot
			case 29:
			case 31:
			case 33:
			case 35:
				a[i].image = gtk_image_new_from_file ("images/011.gif");break;
			//quan do
			case 54:
			case 56:
			case 58:
			case 60:
			case 62:
				a[i].image = gtk_image_new_from_file ("images/111.gif");break;
			case 64:
			case 70:
			 	a[i].image = gtk_image_new_from_file ("images/109.gif");break;
			case 81:
			case 89:
			 	a[i].image = gtk_image_new_from_file ("images/107.gif");break;
			case 82:
			case 88:
				a[i].image = gtk_image_new_from_file ("images/105.gif");break;
			case 83:
			case 87:
				a[i].image = gtk_image_new_from_file ("images/104.gif");break;
			case 84:
			case 86:
				a[i].image = gtk_image_new_from_file ("images/102.gif");break;
			case 85:
				a[i].image = gtk_image_new_from_file ("images/100.gif");break;
			default:
				a[i].image = NULL;
				break;
		}
		if(a[i].image!=NULL)
		{
			x = i%9;
			y = (i-x)/9;
			gtk_fixed_put(GTK_FIXED(fixed),a[i].image,25+60*x,25+60*y);	
		}
	}
	return a;	
}
