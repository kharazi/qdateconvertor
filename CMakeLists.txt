cmake_minimum_required(VERSION 3.1)
project(QDateConvertor)
set(CMAKE_CXX_STANDARD 11)

# Qt Dependencies -------------------------------------------------------------
find_package(Qt5Core REQUIRED)

set(HEADER
        qdateconvertor.h)

set(SRC
        qdateconvertor.cpp)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(${PROJECT_NAME} SHARED ${HEADER} ${SRC})

target_link_libraries(${PROJECT_NAME} Qt5::Core )
