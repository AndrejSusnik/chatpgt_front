#include <gtk/gtk.h>
#include <webkit2/webkit2.h>

// Function to set up persistent cookie storage
static void setup_cookie_storage(WebKitWebContext *web_context) {
    // Create a persistent storage directory
    const char *storage_dir = g_get_user_data_dir();
    char *cookies_path = g_build_filename(storage_dir, "iframe-app-cookies", NULL);

    // Set up the cookie manager
    WebKitCookieManager *cookie_manager = webkit_web_context_get_cookie_manager(web_context);
    webkit_cookie_manager_set_persistent_storage(
        cookie_manager,
        cookies_path,
        WEBKIT_COOKIE_PERSISTENT_STORAGE_SQLITE // Use SQLite for persistent storage
    );

    g_free(cookies_path);
}

// Function to activate the GTK app
static void activate(GtkApplication *app, gpointer user_data) {
    // Create a new application window
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "ChatGPT front");
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 600);

    // Create a WebKitWebView
    WebKitWebContext *web_context = webkit_web_context_get_default();
    setup_cookie_storage(web_context); // Set up persistent cookie storage

    WebKitWebView *web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
    gtk_container_add(GTK_CONTAINER(window), GTK_WIDGET(web_view));

    // Load the desired website
    webkit_web_view_load_uri(web_view, "https://chatgpt.com"); // Replace with your website URL

    // Show the window and its contents
    gtk_widget_show_all(window);
}

int main(int argc, char **argv) {
    // Create a new GTK application
    GtkApplication *app = gtk_application_new("com.example.iframeapp", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    // Run the application
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}

