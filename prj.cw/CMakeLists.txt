cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)

find_package(doctest CONFIG REQUIRED)  

find_package(libigl CONFIG REQUIRED)  
find_package(tinysplinecxx CONFIG REQUIRED)

add_executable(libigl_sample libigl_sample.cpp)
target_link_libraries(libigl_sample 
    PRIVATE 
        tinysplinecxx::tinysplinecxx
        igl::igl_core 
        igl::igl_opengl
        igl::igl_glfw
        igl::igl_imgui
        igl_copyleft::igl_copyleft_core
)

find_package(opencv CONFIG)  
if (OpenCV_FOUND )
#    message(FATAL_ERROR "OpenCV packages found." )
    add_executable(libigl_levels_surface libigl_levels_surface.cpp)
    target_link_libraries(libigl_levels_surface 
        PRIVATE 
        opencv_core opencv_highgui opencv_imgproc
        igl::igl_core igl::igl_opengl igl::igl_glfw igl_copyleft::igl_copyleft_core
    )
endif()