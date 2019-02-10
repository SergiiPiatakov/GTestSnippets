# Framework for writing tests.
ExternalProject_Add (
    googletest
    GIT_REPOSITORY "https://github.com/google/googletest.git"
    GIT_TAG "release-1.8.1"
    CMAKE_ARGS "-DCMAKE_BUILD_TYPE=Release"
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/googletest"
    INSTALL_COMMAND ""
    TEST_COMMAND ""
)
set_target_properties (googletest PROPERTIES EXCLUDE_FROM_ALL TRUE)
ExternalProject_Get_Property (googletest source_dir binary_dir)
set (GTEST_INCLUDE_DIRS   "${source_dir}/googletest/include")
set (GTEST_LIBRARIES      "${binary_dir}/googlemock/gtest/libgtest.a")
set (GTEST_MAIN_LIBRARIES "${binary_dir}/googlemock/gtest/libgtest_main.a")
set (GTEST_BOTH_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES})

include_directories (
    ${PROJECT_SOURCE_DIR}/test
    ${GTEST_INCLUDE_DIRS}
)

# Test suites.
set (
    calculator_test_SOURCES
    ${calculator_SOURCES}
    ${PROJECT_SOURCE_DIR}/test/calculator_test.cpp
)

add_executable (calculator_test ${calculator_test_SOURCES})

target_link_libraries (
    calculator_test
    ${GTEST_BOTH_LIBRARIES}
    pthread
)
add_dependencies (calculator_test googletest)