cmake_minimum_required(VERSION 3.3)

if (DEFINED ENV{TRAVIS_BUILD_NUMBER})
    project(print_ip VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else ()
    project(print_ip VERSION 0.0.1)
endif ()

# set application target name and paths
set(APP_TARGET ${PROJECT_NAME})
set(APP_SOURCE_DIR "${CMAKE_SOURCE_DIR}/src")
set(APP_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include")

# set warning flags for popular compilers
function(set_warnings_flags target)
        if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
                target_compile_options(${APP_TARGET} PRIVATE "-Wall" "-Wextra" "-pedantic")
        elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
                target_compile_options(${APP_TARGET} PRIVATE "/Wall")
        endif()
endfunction()

# create application target
add_executable(${APP_TARGET} "${APP_SOURCE_DIR}/main.cpp")
set_warnings_flags(${APP_TARGET})
set_target_properties(
        ${PROJECT_NAME} PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        INCLUDE_DIRECTORIES "${APP_INCLUDE_DIR}"
)

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR "rfrolov")
set(CPACK_PACKAGE_CONTACT rfrolov@engineer.com)
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Otus homework 04")
set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})

include(CPack)

enable_testing()
add_subdirectory(test)
