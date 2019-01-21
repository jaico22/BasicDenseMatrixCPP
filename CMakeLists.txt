project(CPPDenseMatrix)
add_definitions(-std=c++11)

set(sources src/main.cpp src/dense.cpp src/dense.h)

include_directories(/user/local/include)
link_directories(/usr/local/lib)

add_executable(CPPDenseMatrix ${sources})
