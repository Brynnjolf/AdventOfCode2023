cmake_minimum_required(VERSION 3.0.0)
project(advent-of-code)

file(GLOB DAYS_SRC "days/*.cpp")

foreach(src IN LISTS DAYS_SRC)
    get_filename_component(exe_name ${src} NAME_WE)
    message(STATUS "src=${src} name=${exe_name}")
    add_executable(${exe_name} ${src})
endforeach()
