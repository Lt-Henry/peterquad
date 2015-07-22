
add_executable(peterquad-server main.cpp Server.cpp System.cpp)

target_link_libraries(peterquad-server pthread)

#include_directories(${GLIBMM_INCLUDE_DIRS} ${GIOMM_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})

add_definitions(-std=c++11 -g -O2)

install(TARGETS peterquad-server RUNTIME DESTINATION bin)


