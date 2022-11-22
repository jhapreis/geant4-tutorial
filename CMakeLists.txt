set(EXECUTABLE_FILENAME "sim")
set(MAIN_FILENAME "sim.cc")
set(MACRO_FOLDER "./macros")
set(DATA_FOLDER "./data")
set(SOURCE_FOLDER "./src")
set(HEADER_FOLDER "./headers")

cmake_minimum_required(VERSION 2.8.10 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)

include(${Geant4_USE_FILE})

file(GLOB sources ${PROJECT_SOURCE_DIR}/${SOURCE_FOLDER}/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/${HEADER_FOLDER}/*.hh)

add_executable(${EXECUTABLE_FILENAME} ${MAIN_FILENAME} ${sources} ${headers})
target_include_directories(${EXECUTABLE_FILENAME} PRIVATE ${HEADER_FOLDER})
target_link_libraries(${EXECUTABLE_FILENAME} ${Geant4_LIBRARIES})

file(GLOB MACRO_FILES ${MACRO_FOLDER}/*.mac)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

file(GLOB DATA_FILES ${DATA_FOLDER}/*.dat)
file(COPY ${DATA_FILES} DESTINATION ${PROJECT_BINARY_DIR})

add_custom_target(Simulation DEPENDS sim)
