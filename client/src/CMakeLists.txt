
add_executable(peterquad-client main.cpp Client.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

target_link_libraries(peterquad-client ${GTKMM_LIBRARIES})

include_directories(${GTKMM_INCLUDE_DIRS})

add_definitions(-std=c++11 -g -O2)

install(TARGETS peterquad-client RUNTIME DESTINATION bin)


