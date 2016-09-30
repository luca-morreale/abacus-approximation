cmake_minimum_required (VERSION 2.8)
project(function_approximation)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

include_directories("${PROJECT_SOURCE_DIR}/include")
include(CTest)


add_library(Graph ${PROJECT_SOURCE_DIR}/graph.cpp ${PROJECT_SOURCE_DIR}/node.cpp 
   ${PROJECT_SOURCE_DIR}/include/graph.h ${PROJECT_SOURCE_DIR}/include/node.h ${PROJECT_SOURCE_DIR}/include/edge.h)

set(SRC
   ${PROJECT_SOURCE_DIR}/parser.cpp
   ${PROJECT_SOURCE_DIR}/executer.cpp
)

set(HEAD
   ${PROJECT_SOURCE_DIR}/include/parser.h
   ${PROJECT_SOURCE_DIR}/include/executer.h
)


add_executable(aapp main.cpp ${SRC} ${HEAD})


target_link_libraries(aapp Graph)



enable_testing()
add_subdirectory(test)