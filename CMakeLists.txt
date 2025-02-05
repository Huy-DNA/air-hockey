cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_GENERATOR Ninja)

project(TinyFootball VERSION 1.0)

find_package(SDL2 REQUIRED)

# TinyFootball library
file(GLOB_RECURSE LIB_SOURCES ${PROJECT_SOURCE_DIR}/src/lib/*.cpp)
if (NOT "${LIB_SOURCES}" STREQUAL "")
  add_library(TinyFootballLib STATIC ${LIB_SOURCES})
  set_target_properties(TinyFootballLib PROPERTIES PREFIX "")
  set_target_properties(TinyFootballLib PROPERTIES OUTPUT_NAME "lib")
  target_include_directories(TinyFootballLib PUBLIC
                             ${PROJECT_SOURCE_DIR}/src/include
                             ${SDL2_INCLUDE_DIRS}
  )
  target_link_libraries(TinyFootballLib PUBLIC
                        SDL2::SDL2
  )
endif()
# TinyFootball executable
add_executable(TinyFootball ${PROJECT_SOURCE_DIR}/src/bin/game.cpp)
set_target_properties(TinyFootball PROPERTIES OUTPUT_NAME "out.o")
target_include_directories(TinyFootball PRIVATE
                           ${PROJECT_SOURCE_DIR}/src/include
                           ${SDL2_INCLUDE_DIRS}
)
if (NOT "${LIB_SOURCES}" STREQUAL "")
  target_link_libraries(TinyFootball PRIVATE
                        TinyFootballLib
  )
endif()
target_link_libraries(TinyFootball PRIVATE
                      SDL2::SDL2
)
