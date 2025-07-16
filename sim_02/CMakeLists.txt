# specifies which version of CMake to use
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Set the debugger
set(CMAKE_BUILD_TYPE Debug)

# Name of the project
project(Simulation)

# Packages to use, ui_all - User Interface, vis_all - Visualization
find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

find_package(ROOT REQUIRED COMPONENTS RIO)

# Function to recursively include subdirectories
function(include_sub_directories_recursively root_dir)
    if(IS_DIRECTORY ${root_dir})
        message("Including dir: ${root_dir}")
        include_directories(${root_dir})
    endif()

    file(GLOB all_children RELATIVE ${root_dir} ${root_dir}/*)
    foreach(child ${all_children})
        if(IS_DIRECTORY ${root_dir}/${child})
            include_sub_directories_recursively(${root_dir}/${child})
        endif()
    endforeach()
endfunction()

# Use the function for directories under 'include' and 'src'
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/include_02)
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/src_02)

# Function to recursively glob files with a particular extension
function(glob_files_recursively root_dir extension output_var)
    file(GLOB local_files ${root_dir}/*${extension})
    set(files ${local_files})

    file(GLOB all_children RELATIVE ${root_dir} ${root_dir}/*)
    foreach(child ${all_children})
        if(IS_DIRECTORY ${root_dir}/${child})
            glob_files_recursively(${root_dir}/${child} ${extension} child_files)
            list(APPEND files ${child_files})
        endif()
    endforeach()

    set(${output_var} ${files} PARENT_SCOPE)
endfunction()

# Use the function to get all .cc and .hh files
glob_files_recursively(${PROJECT_SOURCE_DIR} .cc sources)
glob_files_recursively(${PROJECT_SOURCE_DIR}/include_02 .hh headers)

# Copy all macro files to the binaries
file(GLOB_RECURSE MACRO_FILES ${PROJECT_SOURCE_DIR}/macros_02/*.mac)
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
endif()

# Name of executable, call all source and header files
add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS sim)