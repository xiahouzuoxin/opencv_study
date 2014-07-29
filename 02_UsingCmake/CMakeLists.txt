project(read)
find_package(OpenCV REQUIRED)
add_executable(read read)
target_link_libraries(read ${OpenCV_LIBS})

