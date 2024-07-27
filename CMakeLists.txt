cmake_minimum_required(VERSION 3.5.1)

project(blossom_quest CXX C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES src/main.cpp src/engine/app.cpp src/engine/graphics.cpp src/engine/sound.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/libvorbisfile.a ${CMAKE_CURRENT_SOURCE_DIR}/libvorbisenc.a ${CMAKE_CURRENT_SOURCE_DIR}/libvorbis.a ${CMAKE_CURRENT_SOURCE_DIR}/libogg.a)

wut_create_rpx(${PROJECT_NAME})