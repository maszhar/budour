set(GTK_GUI_REACTIVE_SOURCES
  "reactive/core/application/gtk_dispatcher.cc"
)

add_library(
    gtk_gui_reactive 
    STATIC
        ${GTK_GUI_REACTIVE_SOURCES}
)

target_include_directories(
    gtk_gui_reactive
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GTK2_INCLUDE_DIRS}
)

target_link_libraries(
    gtk_gui_reactive
    PUBLIC
        reactive
        ${GTK2_LIBRARIES}
)