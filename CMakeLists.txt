cmake_minimum_required(VERSION 3.0...3.20 FATAL_ERROR)
project(trender_s)

set(CMAKE_CXX_STANDARD 23)
set(lib_dir "${CMAKE_SOURCE_DIR}/lib" )
set(project_cpps "${CMAKE_SOURCE_DIR}/src/world.cpp" "${CMAKE_SOURCE_DIR}/src/dbuffer.cpp" "${CMAKE_SOURCE_DIR}/src/Trispec.cpp" "${CMAKE_SOURCE_DIR}/src/main.cpp" "${CMAKE_SOURCE_DIR}/src/renderer.cpp" "${CMAKE_SOURCE_DIR}/src/model.cpp" "${CMAKE_SOURCE_DIR}/src/tgaimage.cpp" "${CMAKE_SOURCE_DIR}/src/lighting.cpp" "${CMAKE_SOURCE_DIR}/src/camera.cpp")

add_executable(${PROJECT_NAME} ${INCLUDE_DIRECTORIES} ${project_cpps}) 
target_include_directories(${PROJECT_NAME} PUBLIC ${lib_dir} PRIVATE ${CMAKE_SOURCE_DIR}/src)

