#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
//giao dien
#include <gtk/gtk.h>
#include <stdlib.h>
#include "wiget.c"
#define BLACK 0
#define RED 1
#define EMTY 2
int sockfd;
struct sockaddr serverAddr;
char buff[1024];
struct sockaddr_in inAddr;
Chess *Broad;
GtkWidget *event_box;
GtkWidget *fixed;

int move = 91;
int di = BLACK;
int session = 0;

GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;

static void login_funtion(GtkButton *button, gpointer data){
  const char *accl = gtk_entry_get_text(GTK_ENTRY(entry1));
  const char *pass = gtk_entry_get_text(GTK_ENTRY(entry2));
  g_print("tk : %s\n",accl);
  g_print("mk : %s\n",pass);
  //validate va gui len server thong diep dang nhap
  buff[0]=0;
  buff[1]='\0';
  send(sockfd,buff,1024,0);
  recv(sockfd,buff,1024,0);
  printf("%s\n",buff);
}
static void singup_function(GtkButton *button, gpointer data){
  const char *accl = gtk_entry_get_text(GTK_ENTRY(entry1));
  const char *pass = gtk_entry_get_text(GTK_ENTRY(entry2));
  const char *repass = gtk_entry_get_text(GTK_ENTRY(entry3));
  g_print("tk : %s\n",accl);
  g_print("mk : %s\n",pass);
  g_print("repass : %s\n",repass);
  //validate va gui len server thong diep dang ky
  buff[0]=1;
  buff[1]='\0';
  send(sockfd,buff,1024,0);
  recv(sockfd,buff,1024,0);
  printf("%s\n",buff);
}
void login_popup(){
    GtkWidget *window_login;
    GtkWidget *table_login;
    GtkWidget *button_login;
    GtkWidget *label_name;
    GtkWidget *label_pass;
    //GtkWidget *label_result;
    window_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_login), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window_login), "Log In");
    gtk_window_set_modal(GTK_WINDOW(window_login),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window_login),10);
    table_login = gtk_table_new(4,2, FALSE);
    label_name = gtk_label_new("Tai khoan : ");
    gtk_table_attach(GTK_TABLE(table_login), label_name, 0,1,0,1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table_login), entry1, 1,2,0,1,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_pass = gtk_label_new("Mat Khau :");
    gtk_table_attach(GTK_TABLE(table_login), label_pass, 0,1,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility((GtkEntry *)entry2,FALSE);

    gtk_table_attach(GTK_TABLE(table_login),entry2, 1,2,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    button_login = gtk_button_new_with_label("LOG IN");
    gtk_table_attach(GTK_TABLE(table_login),button_login,1,2,2,3, 
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    g_signal_connect(GTK_BUTTON(button_login),"clicked",G_CALLBACK(login_funtion),NULL);
    gtk_container_add(GTK_CONTAINER(window_login),table_login);
    gtk_widget_show_all(window_login);
}
void singup_popup(){
    GtkWidget *window_singup;
    GtkWidget *table_register;
    GtkWidget *button_register;
    GtkWidget *label_name;
    GtkWidget *label_pass;
    GtkWidget *label_re;
    //GtkWidget *label_result;
    window_singup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_singup), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window_singup), "singup");
    gtk_window_set_modal(GTK_WINDOW(window_singup),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window_singup),10);
    table_register = gtk_table_new(4,2, FALSE);
    label_name = gtk_label_new("Tai khoan : ");
    gtk_table_attach(GTK_TABLE(table_register), label_name, 0,1,0,1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table_register), entry1, 1,2,0,1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_pass = gtk_label_new("Mat Khau :");
    gtk_table_attach(GTK_TABLE(table_register), label_pass, 0,1,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility((GtkEntry *)entry2,FALSE);
    gtk_table_attach(GTK_TABLE(table_register),entry2, 1,2,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_re = gtk_label_new("Go lai MK :");
    gtk_table_attach(GTK_TABLE(table_register), label_re, 0,1,2,3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry3 = gtk_entry_new();
    gtk_entry_set_visibility((GtkEntry *)entry3,FALSE);
    gtk_table_attach(GTK_TABLE(table_register),entry3, 1,2,2,3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    button_register = gtk_button_new_with_label("singup");
    gtk_table_attach(GTK_TABLE(table_register),button_register,1,2,3,4, 
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    g_signal_connect(GTK_BUTTON(button_register),"clicked",G_CALLBACK(singup_function),NULL);
    gtk_container_add(GTK_CONTAINER(window_singup),table_register);
    gtk_widget_show_all(window_singup);
}


void createSocket(){
  sockfd=socket(AF_INET,SOCK_STREAM,0);
  if (sockfd == -1)
    {
        printf("khong tao duoc socket\n");
        exit(1);
    }
    printf("Tao socket thanh cong\n");
    inAddr.sin_family=AF_INET;
    inAddr.sin_port=htons(5500);
    inet_aton("127.0.0.1",&inAddr.sin_addr);
    if(connect(sockfd,(struct sockaddr *)&inAddr,sizeof(struct sockaddr))<0){
      printf("connect failed.\n");
      exit(1);
    }
}

static gboolean button_press_callback (GtkWidget *event_box,GdkEventButton *event,gpointer data)
{
  if(session == 0) return 0;
	int a = (int)event->x;
	int b = (int)event->y;
	int i;
  int count = 0;
  //int j=0;
  //int way;
	point clicked;
	GtkWidget *fixed = (GtkWidget *)data;
	clicked = chuanhoa(a,b);
	i = clicked.index;

	if(a < 565 && b < 625){
    	g_print ("Event box clicked at coordinates %d,%d\n",clicked.x,clicked.y);
   	if(Broad[i].image !=NULL&&move == 91){
   			move = i; 
   			g_print ("Event box clicked vao o %d\n",i);
   	}else
   		if(move!= 91&&move!=i){
          buff[count++] = move;
          buff[count++] = i;
          buff[count] = '\0';
          send(sockfd,buff,1024,0);
   				g_print ("Event box clicked vao o %d\n",i);
          recv(sockfd,buff,1024,0);
          if(buff[0]==1){ 
   				isMove(a,b,Broad,fixed,move);         
          //Kiem tra thang

          if(buff[2]==1) ;//show_info();

          recv(sockfd,buff,1024,0);
          //Kiem tra thua     
          if(buff[2]==1)
          {
            g_print("ban da thua");
            Broad = intBroad(fixed);gtk_widget_show_all(event_box);
            return TRUE;
          }
          move = buff[0];
          i = buff[1];
          printf("%d - %d\n",move,i);   
          clicked = indexToXY(i);
          a = clicked.x;b=clicked.y;
          isMove(a,b,Broad,fixed,move);
   				//move = 91;
        }
        move = 91;
   	  }
    }
    return TRUE;
}


void button_clicked(GtkWidget *widget, gpointer data) {
	if(session == 0){
	session = 1;
  login_popup();
	}	
}

void singup_show(GtkWidget *widget, gpointer data) {
  if(session == 0){
  singup_popup();
  } 
}

void play(GtkWidget *widget, gpointer data) {
	if(session == 1){
  buff[0] = 2;
  buff[1]='\0';
  send(sockfd,buff,1024,0);
	Broad = intBroad(fixed);gtk_widget_show_all(event_box);
	}	
}

int main(){
GtkWidget *window1;
GtkWidget *play_box1;
GtkWidget *play_box2;
GtkWidget *table;
GtkWidget *label1;
GtkWidget *label2;
gtk_init(0,0);
window1 = gtk_window_new(GTK_WINDOW_TOPLEVEL);
gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
table = gtk_table_new(100,100, FALSE);
gtk_container_add(GTK_CONTAINER(window1), table);
event_box = gtk_event_box_new ();
fixed = gtk_fixed_new();
gtk_container_add (GTK_CONTAINER (event_box), fixed);

GtkWidget *btn=gtk_button_new_with_label("Dang nhap");
GtkWidget *btn3=gtk_button_new_with_label("Dang ky");
GtkWidget *btn2=gtk_button_new_with_label("Vao choi");

play_box1 = gtk_vbox_new(TRUE, 1);
play_box2 = gtk_vbox_new(TRUE, 1);

gtk_widget_set_size_request(play_box2,200,200);
gtk_widget_set_size_request(play_box1,200,200);
label1 = gtk_label_new("Server");
label2 = gtk_label_new("Client");

g_signal_connect(G_OBJECT(btn), "clicked",G_CALLBACK(button_clicked), NULL);
g_signal_connect(G_OBJECT(btn2), "clicked",G_CALLBACK(play), NULL);
g_signal_connect(G_OBJECT(btn3), "clicked",G_CALLBACK(singup_show), NULL);

gtk_box_pack_start(GTK_BOX(play_box1), label1, TRUE, TRUE, 0);
gtk_box_pack_start(GTK_BOX(play_box2), label2, TRUE, TRUE, 0);

gtk_table_attach(GTK_TABLE(table), btn, 0,20,0,30, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
gtk_table_attach(GTK_TABLE(table), btn2, 20,40,0,30, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
gtk_table_attach(GTK_TABLE(table), btn3, 40,60,0,30, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

gtk_table_attach(GTK_TABLE(table), event_box, 0, 70, 30, 100, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
gtk_table_attach(GTK_TABLE(table), play_box1, 70, 100, 30,75, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
gtk_table_attach(GTK_TABLE(table), play_box2, 70,100, 75,100, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

g_signal_connect (G_OBJECT(event_box),"button_press_event", GTK_SIGNAL_FUNC (button_press_callback),fixed);
g_signal_connect(window1, "destroy",G_CALLBACK(gtk_main_quit), NULL);

gtk_widget_show_all(window1);
createSocket();
gtk_main();
return 1;
}