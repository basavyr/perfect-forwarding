add_library(perfect SHARED src/perfect.cc)
add_library(uref SHARED src/refs_lrefs_urefs.cc)
add_executable(perfect_exe src/perfect.cc)
add_executable(uref_exe src/refs_lrefs_urefs.cc)

target_link_libraries(uref LINK_PUBLIC perfect)
target_include_directories(perfect PUBLIC include/perfectf.hh)

install(TARGETS uref_exe RUNTIME DESTINATION bin)
install(TARGETS perfect uref LIBRARY DESTINATION lib)