cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
set(PROJECT_NAME Sandbox)

project(
    ${PROJECT_NAME}
    VERSION 0.0.1
    DESCRIPTION "Sandbox - project for testing InMemDataBase library"
)

# InMemDataBase library
include_directories(${InMemDataBase_SOURCE_DIR}/inc)
# Include Directories
include_directories(${Sandbox_SOURCE_DIR}/inc)
include_directories(${Sandbox_SOURCE_DIR}/src)

# Source
set(SOURCE 
    ${Sandbox_SOURCE_DIR}/src/main.c
)

# Project Library
add_executable(${PROJECT_NAME} ${SOURCE})
# Add InMemDataBase library
target_link_libraries(${PROJECT_NAME} InMemDataBase)