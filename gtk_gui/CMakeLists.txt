find_package(PkgConfig REQUIRED)

pkg_check_modules(GTK2 REQUIRED
    gtk+-2.0
    glib-2.0
)

add_subdirectory(reactive)
add_subdirectory(pianoroll)

add_library(gtk_gui INTERFACE)

target_link_libraries(
    gtk_gui
    INTERFACE
        gtk_gui_pianoroll
)