#include <gtk/gtk.h>
#define BLACK 0
#define RED 1
typedef struct
{
	int diem;
	int quan;
	GtkWidget *image;
}Chess;
typedef struct
{
	int index;
	int x;
	int y;
}point;
Chess Broad[91];
static GtkWidget *fixed;
int move = -1;
//lay toa do click chuot
int XYtoIndex(int a,int b)
{
	int i,j;
	i = (a-25)/60+1; // xac dinh toa do x 
    j = (b-25)/60;	// xac dinh toa do y
   	i = j*9 + i; // xac dinh chi so trong mang 90 phan tu
   	return i;
}
void debug(){
	int i;
	for (i = 0; i < 91; i++)
	{
		if(Broad[i].image!=NULL)
		printf("%d\n",i);
	}
}
//chuan hoa toa do
point chuanhoa(int a,int b){
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
static gboolean button_press_callback (GtkWidget *event_box,GdkEventButton *event,gpointer data)
{
	point clicked;
	int a = (int)event->x;
	int b = (int)event->y;
	int i;
	clicked = chuanhoa(a,b);
	a = clicked.x;
	b = clicked.y;
	i = clicked.index;
	if(a < 565 && b < 625){
    	g_print ("Event box clicked at coordinates %d,%d\n",a, b);
   		g_print ("Event box clicked vao o %d\n",i);
   	if(Broad[i].image !=NULL&&move == -1){
   			move = i; 
   	}else
   		if(move!= -1&&move!=i){
   				//kiem tra nuoc di tai day
   				//kiem tra an 
   				if(Broad[i].image !=NULL){
   					gtk_widget_destroy(Broad[i].image);
   				}
   				Broad[i].image = Broad[move].image;
   				Broad[i].diem = Broad[move].diem;
   				Broad[move].image = NULL;
   				Broad[move].diem = 0;
   				gtk_fixed_move(GTK_FIXED(fixed),Broad[i].image,a,b); 
   				move = -1;
   		}

    }
    //debug();
    return TRUE;
}
void intBroad(){
int i;
int x;
int y;
for(i=1;i<91;i++){
		switch(i){
			//quan den
			case 1:
			case 9:
			 	Broad[i].image = gtk_image_new_from_file ("images/007.gif");break;
			case 2:
			case 8:
				Broad[i].image = gtk_image_new_from_file ("images/005.gif");break;
			case 3:
			case 7:
				Broad[i].image = gtk_image_new_from_file ("images/004.gif");break;
			case 4:
			case 6:
				Broad[i].image = gtk_image_new_from_file ("images/002.gif");break;
			case 5:
				Broad[i].image = gtk_image_new_from_file ("images/000.gif");break;
			case 20:
			case 26:
				Broad[i].image = gtk_image_new_from_file ("images/009.gif");break;
			case 28:
			case 30:
			case 32:
			case 34:
			case 36:
				Broad[i].image = gtk_image_new_from_file ("images/011.gif");break;

			//quan do
			case 55:
			case 57:
			case 59:
			case 61:
			case 63:
				Broad[i].image = gtk_image_new_from_file ("images/111.gif");break;
			case 65:
			case 71:
			 	Broad[i].image = gtk_image_new_from_file ("images/109.gif");break;
			case 82:
			case 90:
			 	Broad[i].image = gtk_image_new_from_file ("images/107.gif");break;
			case 83:
			case 89:
				Broad[i].image = gtk_image_new_from_file ("images/105.gif");break;
			case 84:
			case 88:
				Broad[i].image = gtk_image_new_from_file ("images/104.gif");break;
			case 85:
			case 87:
				Broad[i].image = gtk_image_new_from_file ("images/102.gif");break;
			case 86:
				Broad[i].image = gtk_image_new_from_file ("images/100.gif");break;
			default:
				Broad[i].image = NULL;
				Broad[i].diem = 0;
				break;
		}
		if(Broad[i].image!=NULL)
		{
			//xac dinh x,y theo hang cot dua vao chi so mang
			if(i%9 == 0) x=9;
			else x = i%9;
			x = x-1;
			y = (i-x)/9;
			gtk_fixed_put(GTK_FIXED(fixed),Broad[i].image,25+60*x,25+60*y);	
		}
	}	
}
int main(){

GtkWidget *window;
GtkWidget *event_box;
GtkWidget *play_box1;
GtkWidget *play_box2;
GtkWidget *table;
GtkWidget *image;
GtkWidget *label1;
GtkWidget *label2;
int i;
gtk_init(0,0);

window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
table = gtk_table_new(2, 2, FALSE);
gtk_container_add(GTK_CONTAINER(window), table);
event_box = gtk_event_box_new ();
fixed = gtk_fixed_new();
image = gtk_image_new_from_file ("images/bg.gif");
gtk_fixed_put(GTK_FIXED(fixed),image,0,0);
intBroad();
gtk_container_add (GTK_CONTAINER (event_box), fixed);

play_box1 = gtk_vbox_new(TRUE, 1);
play_box2 = gtk_vbox_new(TRUE, 1);

gtk_widget_set_size_request(play_box2,200,200);
gtk_widget_set_size_request(play_box1,200,200);


label1 = gtk_label_new("Server");
label2 = gtk_label_new("Client");

gtk_box_pack_start(GTK_BOX(play_box1), label1, TRUE, TRUE, 0);

gtk_box_pack_start(GTK_BOX(play_box2), label2, TRUE, TRUE, 0);

gtk_table_attach(GTK_TABLE(table), event_box, 0, 1, 0, 2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

gtk_table_attach(GTK_TABLE(table), play_box1, 1, 2, 0, 1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

gtk_table_attach(GTK_TABLE(table), play_box2, 1, 2, 1, 2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

g_signal_connect (G_OBJECT(event_box),"button_press_event", GTK_SIGNAL_FUNC (button_press_callback),image);
g_signal_connect(window, "destroy",G_CALLBACK(gtk_main_quit), NULL);
gtk_widget_show_all(window);

gtk_main();

}