cmake_minimum_required (VERSION 3.0)
project (libjaro VERSION 0.1)

configure_file (
  "${PROJECT_SOURCE_DIR}/jaro.h.in"
  "${PROJECT_BINARY_DIR}/jaro.h"
)

include_directories("${PROJECT_BINARY_DIR}")
add_library(jaro SHARED jaro.c)

install(TARGETS jaro LIBRARY DESTINATION lib)
install(FILES "${PROJECT_BINARY_DIR}/jaro.h" DESTINATION include)

enable_testing()
add_subdirectory(test)