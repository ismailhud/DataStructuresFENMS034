cmake_minimum_required(VERSION 3.20)
project(homework-1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Add FetchContent for downloading doctest
include(FetchContent)
FetchContent_Declare(
        doctest
        GIT_REPOSITORY https://github.com/doctest/doctest.git
        GIT_TAG v2.4.11
)
FetchContent_MakeAvailable(doctest)

# Compiler warnings
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()

# Source files
set(SOURCES
        src/main.cpp
)

# Header files (for IDE completion)
set(HEADERS
        include/XorLinkedList.h
        include/XorLinkedList.tpp
        include/Node.h
)

# Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Main executable
add_executable(XorLinkedList ${SOURCES} ${HEADERS})

# Enable testing
enable_testing()

# Test executable (must be named Test to match workflow)
add_executable(Test
        test/tests.cpp
        ${HEADERS}
)

target_link_libraries(Test PRIVATE doctest::doctest)

add_test(NAME XorLinkedListTests COMMAND Test)
