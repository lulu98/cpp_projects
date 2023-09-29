cmake_minimum_required(VERSION 3.16)
project(hangman)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_EXEC "Build an executable." OFF)
option(UNIT_TEST "Execute unit tests." OFF)

set( ASSETS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/assets/" )

if(BUILD_EXEC)
    set(
        SOURCE_FILES
            main.cpp
            FileReader.cpp
            Game.cpp
            State.cpp
            GameService.cpp
    )
    add_definitions(-DASSETS_DIR="${ASSETS_DIR}")
    add_executable(${PROJECT_NAME} ${SOURCE_FILES})
endif(BUILD_EXEC)

if(UNIT_TEST)
    # Locate GTest
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})

    # Link runTests with what we want to test and the GTest and pthread library
    add_definitions(-DASSETS_DIR="${ASSETS_DIR}")
    add_executable(runTests tests.cpp FileReader.cpp Game.cpp State.cpp GameService.cpp)
    target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
endif(UNIT_TEST)

unset(BUILD_EXEC CACHE)
unset(UNIT_TEST CACHE)
