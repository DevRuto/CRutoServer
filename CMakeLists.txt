cmake_minimum_required(VERSION 3.5)
project(CRutoServer)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -DWINVER=0x501")

set(SOURCE_FILES main.c nr_dictionary.c nr_socket.c nr_socket.h nr_thread.c nr_thread.h)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
add_executable(CRutoServer ${SOURCE_FILES})

if(WIN32)
    target_link_libraries(CRutoServer wsock32 ws2_32)
endif()