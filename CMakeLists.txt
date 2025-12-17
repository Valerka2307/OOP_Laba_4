cmake_minimum_required(VERSION 3.10)
project(MyFiguresProject)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")
endif()

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(${PROJECT_NAME}_lib
    ${CMAKE_SOURCE_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME}_lib
    PUBLIC ${CMAKE_SOURCE_DIR}/include
)

add_executable(${PROJECT_NAME}_exe
    main.cpp
)

target_link_libraries(${PROJECT_NAME}_exe
    PRIVATE ${PROJECT_NAME}_lib
)

enable_testing()

# Включаем цвета в Google Test
set(GTEST_COLOR ON)

add_executable(test_pentagon
    tests/test_pentagon.cpp
)

target_link_libraries(test_pentagon
    PRIVATE ${PROJECT_NAME}_lib
    PRIVATE gtest_main
)

add_test(NAME PentagonTests COMMAND test_pentagon --gtest_color=yes)

add_executable(test_hexagon
    tests/test_hexagon.cpp
)

target_link_libraries(test_hexagon
    PRIVATE ${PROJECT_NAME}_lib
    PRIVATE gtest_main
)

add_test(NAME HexagonTests COMMAND test_hexagon --gtest_color=yes)

add_executable(test_rhombus
    tests/test_rhombus.cpp
)

target_link_libraries(test_rhombus
    PRIVATE ${PROJECT_NAME}_lib
    PRIVATE gtest_main
)

add_test(NAME RhombusTests COMMAND test_rhombus --gtest_color=yes)
