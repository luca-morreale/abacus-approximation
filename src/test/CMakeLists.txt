find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(graph_test test_graph.cpp ${SRC} ${HEAD})
add_executable(execution_test test_execution.cpp ${SRC} ${HEAD})

target_link_libraries (graph_test
						Graph
						${Boost_FILESYSTEM_LIBRARY}
                      	${Boost_SYSTEM_LIBRARY}
                      	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries (execution_test
						Graph
						${Boost_FILESYSTEM_LIBRARY}
                      	${Boost_SYSTEM_LIBRARY}
                      	${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(GraphTest graph_test)
add_test(ExecutionTest execution_test)