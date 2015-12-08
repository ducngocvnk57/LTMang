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
struct userinfo {
  int flag;/*trag thai tien tr*/
  char username[30];
  char pass[16];
  int success;//=0 fail;=1 ok;=2 default or none
  int errornumber;//=10 loi signup;=20 error login;=30 error Wrong Moves; =0 none;=100 Success
  };
void convertUserinfoToString(struct userinfo acc,char str[1024]){
  memset(str,0,1024);
  //flag
  char str_flag[3];
  //itoa(acc.flag,str_flag,10);
  snprintf(str_flag, 10, "%d", acc.flag);
  strcat(str,str_flag);
  strcat(str,"|");
  //username
  strcat(str,acc.username);
  strcat(str,"|");
  //pass
  strcat(str,acc.pass);
  strcat(str,"|");
  //success
  char str_succe[1];
  snprintf(str_succe, 10, "%d",acc.success);
  strcat(str,str_succe);
  strcat(str,"|");
  //error
  char str_err[3];
  snprintf(str_err, 10, "%d", acc.errornumber);
  strcat(str,str_err);
  strcat(str,"|");
}
int sockfd;
struct sockaddr serverAddr;
char buff[1024];
struct sockaddr_in inAddr;
Chess *Broad;
GtkWidget *event_box;
GtkWidget *fixed;
GtkWidget *window1;

int move = 91;
int session = 0;
int check_play = 0;
FILE *fpt;
GtkWidget *entry1;
GtkWidget *entry2;
GtkWidget *entry3;
struct userinfo acc;
static void login_funtion(GtkButton *button, gpointer data){
  GtkLabel *label_result = (GtkLabel *)data;
  const char *accl = gtk_entry_get_text(GTK_ENTRY(entry1));
  const char *pass = gtk_entry_get_text(GTK_ENTRY(entry2));
  if(strcmp(accl,"")==0){ gtk_label_set_text(label_result,"tai khoan khong duoc de trong");return;}
  if(strcmp(pass,"")==0){ gtk_label_set_text(label_result,"Mat khau khong duoc de trong");return;}
  //validate va gui len server thong diep dang nhap
  acc.flag=0;
  strcpy(acc.username,accl);
  strcpy(acc.pass,pass);
  convertUserinfoToString(acc,buff);
  send(sockfd,buff,1024,0);
  recv(sockfd,buff,1024,0);
 
  if(buff[0] == 5){
    gtk_label_set_text(label_result,"Dang nhap thanh cong");
    session = 1;
    return;
  }else if(buff[0]==4){
    switch(buff[1]){
      case -1 :
        gtk_label_set_text(label_result,"Khong ton tai tai khoan");
      break;
      case 0 :
        gtk_label_set_text(label_result,"Mat khau khong dung");
      break;
      default:
      break;
    }
  }
}
static void singup_function(GtkButton *button, gpointer data){
  const char *accl = gtk_entry_get_text(GTK_ENTRY(entry1));
  const char *pass = gtk_entry_get_text(GTK_ENTRY(entry2));
  const char *repass = gtk_entry_get_text(GTK_ENTRY(entry3));
  GtkLabel *label_result = (GtkLabel *)data;
  if(strcmp(accl,"")==0){ gtk_label_set_text(label_result,"tai khoan khong duoc de trong");return;}
  if(strlen(pass)<=6){ gtk_label_set_text(label_result,"Mat khau phai nhieu hon 6 ky tu");return;}
  if(strcmp(pass,repass)!=0){ gtk_label_set_text(label_result,"go lai mat khau sai");return;}
  else{
    acc.flag=1;//dang ky
    strcpy(acc.username,accl);
    strcpy(acc.pass,pass);
    convertUserinfoToString(acc,buff);
    send(sockfd,buff,1024,0);
    recv(sockfd,buff,1024,0);
    if(buff[0]==5){gtk_label_set_text(label_result,"dang ky thanh cong");return;}
    else if(buff[0]==4){
      gtk_label_set_text(label_result,"Da ton tai tai khoan");return;
    }
  }
}
void quick_message (gchar *message) {
   GtkWidget *dialog, *label, *content_area;
   /* Create the widgets */
   GtkWindow *man_window = (GtkWindow *)window1;
   dialog = gtk_dialog_new_with_buttons("Message",
                                         man_window,
                                         GTK_DIALOG_DESTROY_WITH_PARENT,
                                         GTK_STOCK_OK,
                                         GTK_RESPONSE_NONE,
                                         NULL);
   gtk_widget_set_size_request(dialog,150,100);
   content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
   label = gtk_label_new (message);
   /* Ensure that the dialog box is destroyed when the user responds. */
   g_signal_connect_swapped (dialog,
                             "response",
                             G_CALLBACK (gtk_widget_destroy),
                             dialog);
   /* Add the label, and show everything we've added to the dialog. */
   gtk_container_add (GTK_CONTAINER (content_area), label);
   gtk_widget_show_all (dialog);
}

void login_popup(){
    GtkWidget *window_login;
    GtkWidget *table_login;
    GtkWidget *button_login;
    GtkWidget *label_name;
    GtkWidget *label_pass;
    GtkWidget *label_result;
    window_login = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_login), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window_login), "Log In");
    gtk_window_set_modal(GTK_WINDOW(window_login),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window_login),10);
    table_login = gtk_table_new(4,2, FALSE);
    label_result = gtk_label_new(NULL);
    gtk_table_attach(GTK_TABLE(table_login), label_result, 0,2,0,1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

    label_name = gtk_label_new("Tai khoan : ");
    gtk_table_attach(GTK_TABLE(table_login), label_name, 0,1,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table_login), entry1, 1,2,1,2,
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_pass = gtk_label_new("Mat Khau :");
    gtk_table_attach(GTK_TABLE(table_login), label_pass, 0,1,2,3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility((GtkEntry *)entry2,FALSE);

    gtk_table_attach(GTK_TABLE(table_login),entry2, 1,2,2,3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    button_login = gtk_button_new_with_label("LOG IN");
    gtk_table_attach(GTK_TABLE(table_login),button_login,1,2,3,4, 
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    g_signal_connect(GTK_BUTTON(button_login),"clicked",G_CALLBACK(login_funtion),label_result);
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
    GtkWidget *label_result;
    window_singup = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window_singup), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(window_singup), "singup");
    gtk_window_set_modal(GTK_WINDOW(window_singup),TRUE);
    gtk_container_set_border_width(GTK_CONTAINER(window_singup),10);
    table_register = gtk_table_new(5,2, FALSE);
    label_result = gtk_label_new(NULL);
    gtk_table_attach(GTK_TABLE(table_register), label_result, 0,2,0,1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_name = gtk_label_new("Tai khoan : ");
    gtk_table_attach(GTK_TABLE(table_register), label_name, 0,1,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry1 = gtk_entry_new();
    gtk_table_attach(GTK_TABLE(table_register), entry1, 1,2,1,2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_pass = gtk_label_new("Mat Khau :");
    gtk_table_attach(GTK_TABLE(table_register), label_pass, 0,1,2,3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry2 = gtk_entry_new();
    gtk_entry_set_visibility((GtkEntry *)entry2,FALSE);
    gtk_table_attach(GTK_TABLE(table_register),entry2, 1,2,2,3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    label_re = gtk_label_new("Go lai MK :");
    gtk_table_attach(GTK_TABLE(table_register), label_re, 0,1,3,4, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    entry3 = gtk_entry_new();
    gtk_entry_set_visibility((GtkEntry *)entry3,FALSE);
    gtk_table_attach(GTK_TABLE(table_register),entry3, 1,2,3,4, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    button_register = gtk_button_new_with_label("singup");
    gtk_table_attach(GTK_TABLE(table_register),button_register,1,2,4,5, 
    GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
    g_signal_connect(GTK_BUTTON(button_register),"clicked",G_CALLBACK(singup_function),label_result);
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
void exit_play(GtkWidget *widget, gpointer data){
  close(sockfd);
  gtk_main_quit();
}
static gboolean button_press_callback (GtkWidget *event_box,GdkEventButton *event,gpointer data)
{
  if(session == 0) return 0;
	int a = (int)event->x;
	int b = (int)event->y;
	int i;
  int recvbyte;
  int count = 0;
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
          buff[count++] = 3;
          buff[count++] = move;
          buff[count++] = i;
          buff[count] = '\0';
          send(sockfd,buff,1024,0);
   				g_print ("Event box clicked vao o %d\n",i);
          recv(sockfd,buff,1024,0);
          if(buff[0]==3){
              if(buff[1]==1){ 
       				isMove(a,b,Broad,fixed,move);
              if(buff[3]==1){
                quick_message("ban da thang");
                fpt = fopen("logfile.txt","w");
                while(1){
                recvbyte = recv(sockfd,buff,1024,0);
                buff[recvbyte+1] = '\0';
                if(buff[0]=='Q') break;
                fprintf(fpt, "%s\n",buff);
                }
                fclose(fpt);
                check_play = 0;
                return TRUE;
              }         
              recv(sockfd,buff,1024,0);
              //Kiem tra thua     
              move = buff[1];
              i = buff[2];
              printf("%d - %d\n",move,i);   
              clicked = indexToXY(i);
              a = clicked.x;b=clicked.y;
              isMove(a,b,Broad,fixed,move);
              if(buff[3]==1){
                quick_message("ban da thua");
                fpt = fopen("logfile.txt","w");
                while(1){
                recvbyte = recv(sockfd,buff,1024,0);
                buff[recvbyte+1] = '\0';
                if(buff[0]=='Q') break;
                fprintf(fpt, "%s\n",buff);
                }
                fclose(fpt);
                check_play = 0; 
                return TRUE;
              }
          }
        }
        move = 91;
   	  }
    }
    return TRUE;
}


void button_clicked(GtkWidget *widget, gpointer data) {
	if(session == 0) login_popup();
}

void singup_show(GtkWidget *widget, gpointer data) {
  if(session == 0) singup_popup();
}

void play(GtkWidget *widget, gpointer data) {
	if(session == 1&&check_play==0){
  acc.flag = 2;
  convertUserinfoToString(acc,buff);
  send(sockfd,buff,1024,0);
	Broad = intBroad(fixed);gtk_widget_show_all(event_box);
  check_play = 1;
  move = 91;
	}else{
    if(session==0) quick_message("ban chua dang nhap");
  }
}

int main(){
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

//gtk_widget_set_size_request(play_box2,200,200);
//gtk_widget_set_size_request(play_box1,200,200);
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
g_signal_connect(window1, "destroy",G_CALLBACK(exit_play), NULL);

gtk_widget_show_all(window1);
createSocket();
gtk_main();
return 1;
}