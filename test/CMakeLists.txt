enable_testing ()

# Framework for writing tests.
ExternalProject_Add (
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "v1.10.x"
    CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)
ExternalProject_Get_Property (googletest source_dir binary_dir)
set (GTEST_ROOT "${CMAKE_CURRENT_BINARY_DIR}/googletest")
set (GTEST_FOUND TRUE)
set (GTEST_INCLUDE_DIRS   "${source_dir}/googletest/include")
set (GTEST_LIBRARIES      "${binary_dir}/lib/libgtest.a")
set (GTEST_MAIN_LIBRARIES "${binary_dir}/lib/libgtest_main.a")
set (GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories (
    ${PROJECT_SOURCE_DIR}/test
    ${GTEST_INCLUDE_DIRS}
)

# Special flags fo generating code coverage.
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set (CMAKE_SHARED_LINKER_FLAGS "-fprofile-arcs -ftest-coverage")


# Test suites.
set (
    calculator_test_SOURCES
    ${calculator_SOURCES}
    ${PROJECT_SOURCE_DIR}/test/calculator_test.cpp
)

add_executable (calculator_test EXCLUDE_FROM_ALL ${calculator_test_SOURCES})

target_link_libraries (
    calculator_test
    ${GTEST_BOTH_LIBRARIES}
    gcov
    pthread
)
add_dependencies (calculator_test googletest)
add_test (calculator_test calculator_test)


# Test coverage report.
set (Coverage_REPORT ${CMAKE_CURRENT_BINARY_DIR}/coverage.info)
set (Coverage_DIR    ${CMAKE_CURRENT_BINARY_DIR}/coverage)
add_custom_command (
    OUTPUT  ${Coverage_REPORT}
    COMMAND lcov -q -c -f -b . -d ${CMAKE_CURRENT_BINARY_DIR} -o ${Coverage_REPORT}
    COMMAND lcov -e ${Coverage_REPORT} '${PROJECT_SOURCE_DIR}/src/*' -o ${Coverage_REPORT}
    COMMAND genhtml ${Coverage_REPORT} --legend --demangle-cpp -f -q -o ${Coverage_DIR}
    DEPENDS calculator_test
)
add_custom_target (coverage DEPENDS ${Coverage_REPORT})
