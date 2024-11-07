cmake_minimum_required(VERSION 3.5.1)

project(blossom_quest CXX C)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCES src/main.cpp src/engine/stb_image.h src/engine/app.cpp src/engine/animation.cpp src/engine/graphics.cpp src/engine/sound.cpp src/engine/resourcemanager.cpp src/engine/camera.cpp src/engine/input.cpp src/engine/sprite.cpp src/levelloader.cpp src/fader.cpp src/levels2.cpp src/choicebox.cpp src/levels1.cpp src/levels3.cpp src/particles.cpp)

set(POSITION_INDEPENDENT_CODE OFF)
set(COMPILE_FLAGS "")

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME})

wut_create_rpx(${PROJECT_NAME})

install(FILES ${CMAKE_BINARY_DIR}/${PROJECT_NAME}.rpx DESTINATION ${CMAKE_BINARY_DIR}/code)