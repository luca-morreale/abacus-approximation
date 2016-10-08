cmake_minimum_required (VERSION 2.8)
project(function_approximation)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )

include_directories("${PROJECT_SOURCE_DIR}/include")
include(CTest)

find_package(OpenMP)
if (OPENMP_FOUND)
   set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()


add_library(Graph ${PROJECT_SOURCE_DIR}/graph.cpp ${PROJECT_SOURCE_DIR}/node.cpp 
   ${PROJECT_SOURCE_DIR}/include/graph.h ${PROJECT_SOURCE_DIR}/include/node.h ${PROJECT_SOURCE_DIR}/include/edge.h)

add_library(Utility ${PROJECT_SOURCE_DIR}/utility.cpp ${PROJECT_SOURCE_DIR}/include/utility.h)

set(SRC
   ${PROJECT_SOURCE_DIR}/parser.cpp
   ${PROJECT_SOURCE_DIR}/executer.cpp
   ${PROJECT_SOURCE_DIR}/syntax.cpp
   ${PROJECT_SOURCE_DIR}/approximated_graph.cpp
   ${PROJECT_SOURCE_DIR}/abacus.cpp
   ${PROJECT_SOURCE_DIR}/approximation.cpp
   ${PROJECT_SOURCE_DIR}/report.cpp
)

set(HEAD
   ${PROJECT_SOURCE_DIR}/include/parser.h
   ${PROJECT_SOURCE_DIR}/include/executer.h
   ${PROJECT_SOURCE_DIR}/include/syntax.h
   ${PROJECT_SOURCE_DIR}/include/approximated_graph.h
   ${PROJECT_SOURCE_DIR}/include/abacus.h
   ${PROJECT_SOURCE_DIR}/include/approximation.h
   ${PROJECT_SOURCE_DIR}/include/report.h
)


add_executable(aapp main.cpp ${SRC} ${HEAD})


target_link_libraries(aapp Graph)
target_link_libraries(aapp Utility)


enable_testing()
add_subdirectory(test)