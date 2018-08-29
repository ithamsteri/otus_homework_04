set(APP_TEST_TARGET ${APP_TARGET}_test)

add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_executable(${APP_TEST_TARGET} test_main.cpp)
target_include_directories(${APP_TEST_TARGET} PRIVATE ${APP_INCLUDE_DIR})
target_link_libraries(${APP_TEST_TARGET} gtest)

set_target_properties(
        ${APP_TEST_TARGET} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

add_test(tests ${APP_TEST_TARGET})
