cmake_minimum_required(VERSION 3.14)

project(conteiners)

add_executable(Conteiners NodesList.hpp Main.cpp Vector.hpp)
target_compile_features(Conteiners PUBLIC cxx_std_17)
set_target_properties(Conteiners PROPERTIES CXX_STANDARD_REQUIRED ON)

