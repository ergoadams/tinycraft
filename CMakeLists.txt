cmake_minimum_required(VERSION 3.20)

project(tinycraft)

find_package(Threads REQUIRED)

file(GLOB SOURCES
     "src/*.cpp"
)

add_executable(tinycraft ${SOURCES})

target_link_libraries(tinycraft Threads::Threads)

target_include_directories(tinycraft
    PRIVATE 
        ${PROJECT_SOURCE_DIR}/include
)