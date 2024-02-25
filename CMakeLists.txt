cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)
project(trender_s)

set(CMAKE_CXX_STANDARD 23)
set(lib_dir "${CMAKE_SOURCE_DIR}/lib" )
set(project_cpps "${CMAKE_SOURCE_DIR}/src/main.cpp" "${CMAKE_SOURCE_DIR}/src/render.cpp" "${CMAKE_SOURCE_DIR}/src/model.cpp" "${CMAKE_SOURCE_DIR}/src/tgaimage.cpp")

add_executable(${PROJECT_NAME} ${INCLUDE_DIRECTORIES} ${project_cpps}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${lib_dir} PRIVATE ${CMAKE_SOURCE_DIR}/src)

