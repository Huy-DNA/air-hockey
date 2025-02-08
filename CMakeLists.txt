cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR Ninja)

project(AirHockey VERSION 1.0)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)

# AirHockey library
file(GLOB_RECURSE LIB_SOURCES ${PROJECT_SOURCE_DIR}/src/lib/*.cpp)
if(NOT "${LIB_SOURCES}" STREQUAL "")
  add_library(AirHockeyLib STATIC ${LIB_SOURCES})
  set_target_properties(AirHockeyLib PROPERTIES PREFIX "")
  set_target_properties(AirHockeyLib PROPERTIES OUTPUT_NAME "lib")
  target_include_directories(
    AirHockeyLib PUBLIC ${PROJECT_SOURCE_DIR}/src/include ${SDL2_INCLUDE_DIRS})
  target_link_libraries(
    AirHockeyLib PUBLIC SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf
                        SDL2_image::SDL2_image)
endif()
# AirHockey executable
file(GLOB_RECURSE BIN_SOURCES ${PROJECT_SOURCE_DIR}/src/bin/game/*.cpp)
add_executable(AirHockey ${BIN_SOURCES})
set_target_properties(AirHockey PROPERTIES OUTPUT_NAME "out.o")
target_include_directories(
  AirHockey PRIVATE ${PROJECT_SOURCE_DIR}/src/include ${SDL2_INCLUDE_DIRS}
                    ${PROJECT_SOURCE_DIR}/src/bin/game)
if(NOT "${LIB_SOURCES}" STREQUAL "")
  target_link_libraries(AirHockey PRIVATE AirHockeyLib)
endif()
target_link_libraries(
  AirHockey PRIVATE SDL2::SDL2 SDL2_mixer::SDL2_mixer SDL2_ttf::SDL2_ttf
                    SDL2_image::SDL2_image)
