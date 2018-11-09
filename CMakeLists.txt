# Minimum version can be no higher than 3.5 as Ubuntu package management uses this version.
cmake_minimum_required(VERSION 3.5)

project (EX07-HashMap)

set(SOURCE_PREFIX "hash_map")
set(EXEC_NAME "HashMap")
set(CMAKE_CXX_STANDARD 11)

if(EXISTS ${CMAKE_HOME_DIRECTORY}/csv15-lib/CMakeLists.txt)
include(csv15-lib/CMakeLists.txt)
else()
add_custom_target(submodule-init ALL git submodule init COMMAND git submodule update --recursive WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
endif()
