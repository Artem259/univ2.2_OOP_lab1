project(tests)

add_subdirectory(google-test)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_executable(tests main_test.cpp Geometry_test.cpp Graph_test.cpp)

target_link_libraries(tests gtest gtest_main)