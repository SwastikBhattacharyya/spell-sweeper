cmake_minimum_required(VERSION 3.30.2)
project(spell_sweeper)

file(GLOB_RECURSE sources src/main/*.cpp src/main/*.h)
file(GLOB_RECURSE sources_test src/test/*.cpp)
file(GLOB_RECURSE data resources/*)

add_executable(spell_sweeper ${sources} ${data})
target_compile_options(spell_sweeper PUBLIC -std=c++17 -Wall -Wfloat-conversion)
target_include_directories(spell_sweeper PUBLIC src/main)
file(COPY ${data} DESTINATION resources)

find_package(GTest)

if(GTEST_FOUND)
    add_executable(spell_sweeper_tests ${sources_test} ${sources})
    target_compile_definitions(spell_sweeper_tests PUBLIC UNIT_TESTS)
    set_target_properties(spell_sweeper PROPERTIES ENABLE_EXPORTS on)
    target_link_libraries(spell_sweeper_tests PUBLIC
        ${GTEST_BOTH_LIBRARIES}
        spell_sweeper
    )
    target_include_directories(spell_sweeper_tests PUBLIC
        ${GTEST_INCLUDE_DIRS}
    )
endif()
