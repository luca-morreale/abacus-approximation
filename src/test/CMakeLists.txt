find_package(Boost COMPONENTS system filesystem unit_test_framework REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_definitions(-DBOOST_TEST_DYN_LINK)

add_executable(graph_test test_graph.cpp ${SRC} ${HEAD})
add_executable(execution_test test_execution.cpp ${SRC} ${HEAD})
add_executable(control_test test_control_structure.cpp ${SRC} ${HEAD})
add_executable(app_graph_test test_approximated_graph.cpp ${SRC} ${HEAD})
add_executable(approximation_test test_approximation.cpp ${SRC} ${HEAD})
add_executable(selection_test test_selection.cpp ${SRC} ${HEAD})

target_link_libraries (graph_test
                        Graph
                        Utility
                        Approximation
                        ${Boost_FILESYSTEM_LIBRARY}
                        ${Boost_SYSTEM_LIBRARY}
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries (execution_test
                        Graph
                        Utility
                        Approximation
                        ${Boost_FILESYSTEM_LIBRARY}
                        ${Boost_SYSTEM_LIBRARY}
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries (control_test
                        Graph
                        Utility
                        Approximation
                        ${Boost_FILESYSTEM_LIBRARY}
                        ${Boost_SYSTEM_LIBRARY}
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries (app_graph_test
                        Graph
                        Utility
                        Approximation
                        ${Boost_FILESYSTEM_LIBRARY}
                        ${Boost_SYSTEM_LIBRARY}
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries (approximation_test
                        Graph
                        Utility
                        Approximation
                        ${Boost_FILESYSTEM_LIBRARY}
                        ${Boost_SYSTEM_LIBRARY}
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

target_link_libraries (selection_test
                        Graph
                        Utility
                        Approximation
                        ${Boost_FILESYSTEM_LIBRARY}
                        ${Boost_SYSTEM_LIBRARY}
                        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

add_test(GraphTest graph_test)
add_test(ExecutionTest execution_test)
add_test(ControlStructureTest control_test)
add_test(ApproximatedGraphTest app_graph_test)
add_test(ApproximationTest approximation_test)
add_test(SelectionTest selection_test)
