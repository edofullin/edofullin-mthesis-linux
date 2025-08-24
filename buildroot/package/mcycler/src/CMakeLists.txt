cmake_minimum_required(VERSION 3.10)
project(mcycler C)

add_executable(mcycler main.c)
install(TARGETS mcycler DESTINATION /bin)