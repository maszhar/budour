add_subdirectory(reactive)

add_library(libs INTERFACE)

target_link_libraries(
  libs
  INTERFACE
    reactive
)