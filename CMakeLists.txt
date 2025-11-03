cmake_minimum_required(VERSION 3.20)
project(homework-1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Fetch doctest for testing
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
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# Include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

# Optional main executable (for local demo)
add_executable(XorLinkedList
        src/main.cpp
)
# Add headers just for IDE recognition
target_sources(XorLinkedList PRIVATE
        include/XorLinkedList.h
        include/XorLinkedList.tpp
        include/Node.h
)

# Enable testing
enable_testing()

# Test executable (autograder will use this)
add_executable(tests
        test/tests.cpp
        include/XorLinkedList.h
        include/XorLinkedList.tpp
        include/Node.h
)

target_link_libraries(tests PRIVATE doctest::doctest)

# Register test
add_test(NAME XorLinkedListTests COMMAND tests)
