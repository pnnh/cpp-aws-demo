cmake_minimum_required(VERSION 3.20)
project(cpp_aws_demo)

set(CMAKE_CXX_STANDARD 20)

find_package(AWSSDK REQUIRED COMPONENTS s3 sts)


add_executable(cpp_aws_demo main.cpp)

target_link_libraries(cpp_aws_demo ${AWSSDK_LINK_LIBRARIES}
        ${AWSSDK_PLATFORM_DEPS})

