add_library(queuelstt INTERFACE queuelstt.hpp)
set_property(TARGET queuelstt PROPERTY CXX_STANDARD 20)
target_include_directories(queuelstt INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)