add_library(perfect SHARED src/perfect.cc)

add_executable(perfect_exe src/perfect.cc)

target_include_directories(perfect PUBLIC include/perfectf.hh)