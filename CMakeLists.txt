cmake_minimum_required(VERSION 3.2)
project("telephonia")

add_executable(telephonia main.cpp telephonia.cpp)
set_property(TARGET telephonia PROPERTY CXX_STANDARD 20)