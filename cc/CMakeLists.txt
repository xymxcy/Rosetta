cmake_minimum_required(VERSION 2.8)
project(rosetta)

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

# setup directory where we should look for cmake modules files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(GlobalSettings)


# deps (third_party: relic, emp-toolkit)
execute_process(COMMAND bash ${CMAKE_SOURCE_DIR}/install_basic_deps_by_cmake.sh ${PROJECT_BINARY_DIR} ${CMAKE_BUILD_TYPE} ${THIRD_PARTY_DIR} 
                WORKING_DIRECTORY ${PROJECT_BINARY_DIR})
                

# config mpc with 128-bits
option(ROSETTA_MPC_128 "" OFF)
if (ROSETTA_MPC_128)
    message(STATUS "ROSETTA_MPC_128: ${ROSETTA_MPC_128}, use 128-bits MPC")
    # add_compile_definitions(ROSETTA_MPC_128=1)
    add_definitions(-DROSETTA_MPC_128=1)
else()
    message(STATUS "ROSETTA_MPC_128: ${ROSETTA_MPC_128}, use 64-bits MPC")
endif()

option(ROSETTA_COMPILE_TESTS "" OFF)

# modules
add_subdirectory(modules)
add_subdirectory(tf)
