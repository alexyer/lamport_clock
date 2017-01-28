project(test)

include(CTest)
enable_testing()

include(DownloadProject.cmake)
download_project(
        PROJ    googletest
        GIT_REPOSITORY  https://github.com/google/googletest.git
        GIT_TAG master
        UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

add_executable(runUnitTests gtest.cpp lamport_clock_tests/lamport_clock_tests.cpp)
target_link_libraries(runUnitTests gtest gmock)