cmake_minimum_required(VERSION 3.23)
project(ols)

set(CMAKE_CXX_STANDARD 11)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../../bin)

add_executable(
        ${PROJECT_NAME}
        main.cpp
        encoder.cpp encoder.h decoder.cpp decoder.h stdafx.h)
