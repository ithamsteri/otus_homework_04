# set target name for test
set(APP_TEST_TARGET ${APP_TARGET}_test)

add_subdirectory(googletest EXCLUDE_FROM_ALL)

add_executable(${APP_TEST_TARGET} test_main.cpp)
set_warning_flags(${APP_TEST_TARGET})
set_target_properties(
        ${APP_TEST_TARGET} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        INCLUDE_DIRECTORIES "${APP_INCLUDE_DIR}"
        LINK_LIBRARIES gtest
)

add_test(tests ${APP_TEST_TARGET})
