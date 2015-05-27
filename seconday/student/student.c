#include <gtk/gtk.h>
typedef struct {
    GtkWidget *window;
    GtkWidget *combo;
} CallbackData;
static void on_login_button_clicked(GtkWidget * button, gpointer data);
static GtkWidget *create_new_window(const gchar * text);
int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(window), 350, 350);
    gtk_window_set_title(GTK_WINDOW(window), "XX大学教务管理系统");
    gtk_container_set_border_width(GTK_CONTAINER(window), 120);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);
    GtkWidget *label =
        gtk_label_new("欢迎进入XX大学教务管理系统");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    label = gtk_label_new("请选择身份登录");
    gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 0);
    /* 下面创建下拉按钮GtkComboBoxText,
     * 如果下拉框中只有文字的话，这样做就行了,
     * 如果还有图片那就要用到GtkComboBox和GtkTreeModel,
     * 具体这里就不说了*/
    GtkWidget *combo = gtk_combo_box_text_new();
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),
                                   "学生登录");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),
                                   "教职工登录");
    gtk_combo_box_text_append_text(GTK_COMBO_BOX_TEXT(combo),
                                   "管理员登录");
    gtk_combo_box_set_active(GTK_COMBO_BOX(combo), 0);
    gtk_box_pack_start(GTK_BOX(box), combo, FALSE, FALSE, 10);
    /* 按钮 */
    GtkWidget *button = gtk_button_new_with_label("登录");
    gtk_box_pack_start(GTK_BOX(box), button, FALSE, FALSE, 40);
    static CallbackData cdata;
    cdata.window = window;
    cdata.combo = combo;
    g_signal_connect(G_OBJECT(button), "clicked",
                     G_CALLBACK(on_login_button_clicked), &cdata);
    gtk_widget_show_all(window);
    gtk_main();
    return 0;
}
static void on_login_button_clicked(GtkWidget * button, gpointer data)
{
    CallbackData *cdata = (CallbackData *) data;
    GtkWidget *combo = cdata->combo;
    GtkWidget *window = cdata->window;
    gchar *text =
        gtk_combo_box_text_get_active_text(GTK_COMBO_BOX_TEXT(combo));
    GtkWidget *new_window = create_new_window(text);
    /* 先屏蔽回调函数再删除原有窗口 */
    g_signal_handlers_block_by_func(G_OBJECT(window), gtk_main_quit, NULL);
    gtk_widget_destroy(window);
    /* 不删除原有窗口，只是隐藏 */
    /*gtk_widget_hide(window); */
    /* 显示新窗口 */
    gtk_widget_show_all(new_window);
    g_free(text);
}
static GtkWidget *create_new_window(const gchar * text)
{
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), text);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
    gtk_window_set_default_size(GTK_WINDOW(window), 360, 250);
    g_signal_connect(G_OBJECT(window), "destroy",
                     G_CALLBACK(gtk_main_quit), NULL);
    return window;
}
