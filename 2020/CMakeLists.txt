cmake_minimum_required(VERSION 3.10) 

project(2020)

# Find all sub folders containing CMakeLists.txt
MACRO(SUBDIRLIST result dir)
  FILE(GLOB children RELATIVE ${dir} ${dir}/*)
  SET(dirlist "")
  FOREACH(child ${children})
    IF(IS_DIRECTORY ${dir}/${child} AND EXISTS ${dir}/${child}/CMakeLists.txt)
      LIST(APPEND dirlist ${child})
    ENDIF()
  ENDFOREACH()
  SET(${result} ${dirlist})
ENDMACRO()

# Add all subdirectories with CMakeLists.txt
SUBDIRLIST(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
FOREACH(subdir ${SUBDIRS})
  
  add_subdirectory(${subdir})
ENDFOREACH()