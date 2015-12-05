   #include <gtk/gtk.h>

    GtkWidget*
    find_child(GtkWidget* parent, const gchar* name)
    {
            if (g_strcasecmp(gtk_widget_get_name((GtkWidget*)parent), (gchar*)name) == 0) { 
                    return parent;
            }

            if (GTK_IS_BIN(parent)) {
                    GtkWidget *child = gtk_bin_get_child(GTK_BIN(parent));
                    return find_child(child, name);
            }

            if (GTK_IS_CONTAINER(parent)) {
                    GList *children = gtk_container_get_children(GTK_CONTAINER(parent));
                    while ((children = g_list_next(children)) != NULL) {
                            GtkWidget* widget = find_child(children->data, name);
                            if (widget != NULL) {
                                    return widget;
                            }
                    }
            }

            return NULL;
    }

    int
    main(int argc, char *argv[])
    {
            gtk_init(&argc, &argv);

            GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
            GtkWidget *frame = gtk_frame_new(NULL);
            GtkWidget *vbox1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
            GtkWidget *textView = gtk_text_view_new();
            GtkWidget *hbox1 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);
            GtkWidget *button1 = gtk_button_new_with_label("button1");
            gtk_widget_set_name(button1, "btn1");
            GtkWidget *button2 = gtk_button_new_with_label("button2");
            gtk_widget_set_name(button2, "btn2");

            gtk_window_set_title(GTK_WINDOW(window), "Hello");
            gtk_container_set_border_width(GTK_CONTAINER(window), 10);
            gtk_window_set_default_size(GTK_WINDOW(window), 450, 400);

            gtk_container_add(GTK_CONTAINER(window), frame);
            gtk_container_add(GTK_CONTAINER(frame), vbox1);

            gtk_box_pack_start(GTK_BOX(vbox1), textView, 1, 1, 0);
            gtk_box_pack_start(GTK_BOX(vbox1), hbox1, 0, 1, 0);
            gtk_box_pack_start(GTK_BOX(hbox1), button1, 0, 1, 0);
            gtk_box_pack_start(GTK_BOX(hbox1), button2, 0, 1, 0);

            gtk_widget_show_all(window);

            g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

            GtkWidget* child = find_child(window, "btn2");
            if (child == button2) {
                    g_print("found it!\n");
            } else {
                    g_print("not found it!\n");
            }

            gtk_main();
            return 0;
    }