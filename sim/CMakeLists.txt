cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

project(Simulation)

find_package(Geant4 REQUIRED ui_all vis_all)
include(${Geant4_USE_FILE})

# Finds RIO version of ROOT to be available to Geant
find_package(ROOT REQUIRED COMPONENTS RIO)

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
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/include)
include_sub_directories_recursively(${PROJECT_SOURCE_DIR}/src)

# Function that recursively globs all files with a particular extension
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

# Uses above function to glob files with '.cc' and '.hh'
glob_files_recursively(${PROJECT_SOURCE_DIR} .cc sources)
glob_files_recursively(${PROJECT_SOURCE_DIR}/include .hh headers)

# Adds all macro files to binaries
file(GLOB MACRO_FILES "*.mac")
file(COPY ${MACRO_FILES} DESTINATION ${PROJECT_BINARY_DIR})


# if(CMAKE_COMPILER_IS_GNUCC)
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g")
# endif()

add_executable(sim sim.cc ${sources} ${headers})
target_link_libraries(sim ${Geant4_LIBRARIES})

add_custom_target(Simulation DEPENDS sim)