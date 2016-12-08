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

SET(GCC_COVERAGE_COMPILE_FLAGS "-D ITERATIONS")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

add_library(Graph ${PROJECT_SOURCE_DIR}/graph.cpp ${PROJECT_SOURCE_DIR}/node.cpp 
   ${PROJECT_SOURCE_DIR}/include/graph.h ${PROJECT_SOURCE_DIR}/include/node.h ${PROJECT_SOURCE_DIR}/include/edge.h
)

add_library(Utility ${PROJECT_SOURCE_DIR}/utility.cpp ${PROJECT_SOURCE_DIR}/include/utility.h)

add_library(Approximation ${PROJECT_SOURCE_DIR}/approximated_graph.cpp ${PROJECT_SOURCE_DIR}/include/approximated_graph.h
   ${PROJECT_SOURCE_DIR}/executed_graph.cpp ${PROJECT_SOURCE_DIR}/include/executed_graph.h
      ${PROJECT_SOURCE_DIR}/approximation.cpp ${PROJECT_SOURCE_DIR}/include/approximation.h
      ${PROJECT_SOURCE_DIR}/report.cpp ${PROJECT_SOURCE_DIR}/include/report.h
)

set(SRC
   ${PROJECT_SOURCE_DIR}/parser.cpp
   ${PROJECT_SOURCE_DIR}/executer.cpp
   ${PROJECT_SOURCE_DIR}/syntax.cpp
   ${PROJECT_SOURCE_DIR}/abacus.cpp
)

set(HEAD
   ${PROJECT_SOURCE_DIR}/include/parser.h
   ${PROJECT_SOURCE_DIR}/include/executer.h
   ${PROJECT_SOURCE_DIR}/include/syntax.h
   ${PROJECT_SOURCE_DIR}/include/abacus.h
   ${PROJECT_SOURCE_DIR}/include/operations.h
)


add_executable(aapp_interpreted main.cpp ${SRC} ${HEAD})


target_link_libraries(aapp_interpreted Graph)
target_link_libraries(aapp_interpreted Utility)
target_link_libraries(aapp_interpreted Approximation)


# compiled version

set(SRC_COMPILED
   ${PROJECT_SOURCE_DIR}/parser.cpp
   ${PROJECT_SOURCE_DIR}/syntax.cpp
   ${PROJECT_SOURCE_DIR}/executer.cpp
   ${PROJECT_SOURCE_DIR}/executer_compilation.cpp
   ${PROJECT_SOURCE_DIR}/abacus.cpp
   ${PROJECT_SOURCE_DIR}/compiled_abacus.cpp
   ${PROJECT_SOURCE_DIR}/operation_generator.cpp
   ${PROJECT_SOURCE_DIR}/writer.cpp
)

set(HEAD_COMPILED
   ${PROJECT_SOURCE_DIR}/include/parser.h
   ${PROJECT_SOURCE_DIR}/include/syntax.h
   ${PROJECT_SOURCE_DIR}/include/executer.h
   ${PROJECT_SOURCE_DIR}/include/executer_compilation.h
   ${PROJECT_SOURCE_DIR}/include/abacus.h
   ${PROJECT_SOURCE_DIR}/include/compiled_abacus.h
   ${PROJECT_SOURCE_DIR}/include/operation_generator.h
   ${PROJECT_SOURCE_DIR}/include/writer.h
)

add_executable(aapp_compiled main_compiled.cpp ${SRC_COMPILED} ${HEAD_COMPILED})


target_link_libraries(aapp_compiled Graph)
target_link_libraries(aapp_compiled Utility)
target_link_libraries(aapp_compiled Approximation)

enable_testing()
add_subdirectory(test)