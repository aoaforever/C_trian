cmake_minimum_required(VERSION 3.5.1)
project(Project_threadpool_server)

set( CMAKE_CXX_FLAGS "-std=c++11 -pthread" )
add_definitions(-Wall -g )
add_executable(class_server class_server.cpp)
add_executable(client client.cpp)
# target_link_libraries(Project_threadpool_server pthread)

# target_include_directories(Project_threadpool_server PUBLIC /home/aoa_vm/workplace/backend/Project_threadpool_server)
