#include <gtk/gtk.h>
static GtkWidget *name;
static GtkWidget *password;

static void get_value( GtkWidget *widget,
                       gpointer data )
{
  gchar *buf;
  GtkLabel *label;
  gchar *text;
  GtkWidget *table;

  GtkWidget *button = gtk_button_new_with_label("play");
  //text = gtk_entry_get_text(GTK_ENTRY(name));

  label = GTK_LABEL (g_object_get_data (G_OBJECT (widget), "user_data"));

  table = GTK_TABLE(g_object_get_data (G_OBJECT (widget), "table"));

  gtk_table_attach(GTK_TABLE(table),button, 1, 2, 3, 4, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  text = g_strdup_printf("%s","Ban dang nhap thanh cong");

  gtk_init(0, 0);
}


int main(int argc, char *argv[]) {

  GtkWidget *window;
  GtkWidget *table;
  GtkWidget *window1;
  GtkWidget *label1;
  GtkWidget *label2;
  GtkWidget *notifi;

  GtkWidget *submit;

  gtk_init(&argc, &argv);

  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(window), "login");
  gtk_container_set_border_width(GTK_CONTAINER(window), 10);

  table = gtk_table_new(4, 2, FALSE);
  gtk_container_add(GTK_CONTAINER(window), table);

  label1 = gtk_label_new("Name");
  label2 = gtk_label_new("password");
  notifi = gtk_label_new("");


  gtk_table_attach(GTK_TABLE(table), label1, 0, 1, 1, 2, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), label2, 0, 1, 2, 3, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  gtk_table_attach(GTK_TABLE(table), notifi, 0,2, 0, 1, 
      GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  name = gtk_entry_new();
  password = gtk_entry_new();

  gtk_entry_set_visibility(GTK_ENTRY(password),FALSE);

  submit = gtk_button_new_with_label("login");
  g_object_set_data (G_OBJECT (submit), "user_data", notifi);
  g_object_set_data (G_OBJECT (submit), "table", table);

  g_signal_connect (submit, "clicked",G_CALLBACK (get_value),NULL);
  
  gtk_widget_set_uposition(window1, 240, 40);

  gtk_table_attach(GTK_TABLE(table), name, 1, 2, 1, 2,GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);
  gtk_table_attach(GTK_TABLE(table), password, 1, 2, 2, 3, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  gtk_table_attach(GTK_TABLE(table), submit, 1, 2, 3, 4, GTK_FILL | GTK_SHRINK, GTK_FILL | GTK_SHRINK, 5, 5);

  gtk_widget_show_all(window);

  g_signal_connect(window, "destroy",
      G_CALLBACK(gtk_main_quit), NULL);

  gtk_main();

  return 0;
}