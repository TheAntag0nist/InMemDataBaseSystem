cmake_minimum_required(VERSION 3.13 FATAL_ERROR)
# Project Name
set(PROJECT_NAME InMemDataBase)

# Project
project(${PROJECT_NAME})

# Include Directories
include_directories(${InMemDataBase_SOURCE_DIR}/inc)
include_directories(${InMemDataBase_SOURCE_DIR}/src)

# Source
set(SOURCE 
    ${InMemDataBase_SOURCE_DIR}/src/core_db.c
    ${InMemDataBase_SOURCE_DIR}/src/core.c
    ${InMemDataBase_SOURCE_DIR}/src/node.c
    ${InMemDataBase_SOURCE_DIR}/src/log.c
)

# Project Library
add_library(${PROJECT_NAME} STATIC ${SOURCE})