cmake_minimum_required(VERSION 3.10)

project(2022)

# Find all sub folders containing CMakeLists.txt
macro(SUBDIRLIST result dir)
  file(
    GLOB children
    RELATIVE ${dir}
    ${dir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${dir}/${child} AND EXISTS ${dir}/${child}/CMakeLists.txt)
      list(APPEND dirlist ${child})
    endif()
  endforeach()
  set(${result} ${dirlist})
endmacro()

# Add all subdirectories with CMakeLists.txt
subdirlist(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
foreach(subdir ${SUBDIRS})
  add_subdirectory(${subdir})
endforeach()
