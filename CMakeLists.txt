cmake_minimum_required(VERSION 3.1)
project(CTurtle)
option(BUILD_STATIC "Build a static CTurtle library." ON)
option(BUILD_DYNAMIC "Build a dynamic CTurtle library." OFF)
option(BUILD_EXAMPLES "Build Example Executables." OFF)
option(MSVC_GEN_ED "Build an education-oriented MSVC project with a hello-world \"main\" function." OFF)

set(CTURTLE_CPP_FILE "${PROJECT_SOURCE_DIR}/src/CTurtle.cpp")
set(CTURTLE_INCL_DIR "${PROJECT_SOURCE_DIR}/src")

include_directories("${CTURTLE_INCL_DIR}")

if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    # Link against X11 and libpthread on UNIX-esque systems.
    # This includes Cygwin, MinGW, G++, etcetera.
    # On Windows, for PThread, users can employ WinPThread.
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads REQUIRED)
endif()

if(BUILD_EXAMPLES)
    set(EXAMPLE_SOURCE_DIR "${PROJECT_SOURCE_DIR}/examples")
    message("Adding example executables from \"${EXAMPLE_SOURCE_DIR}\".")
    #TODO: set output dir

    file(GLOB files "${EXAMPLE_SOURCE_DIR}/*.cpp")
    
    foreach(file ${files})
        get_filename_component(ex_out_name "${file}" NAME_WE)
        message("Adding Example Executable ${ex_out_name}")
        add_executable("${ex_out_name}" "${file}" "${CTURTLE_CPP_FILE}")

        if(NOT "${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
            target_link_libraries("${ex_out_name}" ${X11_LIBRARIES})
            target_link_libraries("${ex_out_name}" Threads::Threads)
        endif()
    endforeach()
endif(BUILD_EXAMPLES)

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message("Found compiling under MSVC...")
    message("Setting attributes for project file...")

    #Disable precompiled headers
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Y-")

    #Set to C++14 Standard.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++14")

    #Disable overly-verbose compiler warnings.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w")

    # We don't need to do anything special for linking because
    # linking against GDI32 and kernel32 is handled automatically.
    if(BUILD_STATIC)
        add_library(CTurtle-Static STATIC ${CTURTLE_CPP_FILE})
    endif(BUILD_STATIC)

    if(BUILD_DYNAMIC)
        add_library(CTurtle-Static SHARED ${CTURTLE_CPP_FILE})
    endif(BUILD_DYNAMIC)

    if(MSVC_GEN_ED)
        add_executable(CTurtle-Sandbox "${PROJECT_SOURCE_DIR}/sandbox.cpp" "${CTURTLE_CPP_FILE}")
    endif(MSVC_GEN_ED)
else()
    message("Assuming Unix-Esque Environment, linking pthread and X11")
    if(MSVC_GEN_ED)
        message("Ignoring MSVC_GEN_ED option; Generating under Non-MSVC.")
    endif(MSVC_GEN_ED)

    if(BUILD_STATIC)
        message("Building Static Library")
        add_library(CTurtle-Static STATIC ${CTURTLE_CPP_FILE})
        target_link_libraries(CTurtle-Static ${X11_LIBRARIES})
        target_link_libraries(CTurtle-Static Threads::Threads)
    endif()

    if(BUILD_DYNAMIC)
        message("Building Dynamic Library")
        add_library(CTurtle-Dynamic SHARED ${CTURTLE_CPP_FILE})
        target_link_libraries(CTurtle-Dynamic ${X11_LIBRARIES})
        target_link_libraries(CTurtle-Dynamic Threads::Threads)
    endif()

endif()