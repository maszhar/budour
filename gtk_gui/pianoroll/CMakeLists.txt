set(GTK_GUI_PIANOROLL_SOURCES
  "pianoroll/viewmodel/pianoroll_viewmodel.cc"
)

add_library(
    gtk_gui_pianoroll
    STATIC
        ${GTK_GUI_PIANOROLL_SOURCES}
)

target_link_libraries(
    gtk_gui_pianoroll
    PUBLIC
        libs
        gtk_gui_reactive
) 

target_include_directories(
    gtk_gui_pianoroll
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)