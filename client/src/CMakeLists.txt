
add_executable(peterquad-client main.cpp)

#find_package(PkgConfig REQUIRED)
#pkg_check_modules(GLIBMM REQUIRED glibmm-2.4)

#target_link_libraries(mrpdi-calibrator ${GLIBMM_LIBRARIES} ${GIOMM_LIBRARIES} ${GTKMM_LIBRARIES} X11 Xi)

#include_directories(${GLIBMM_INCLUDE_DIRS} ${GIOMM_INCLUDE_DIRS} ${GTKMM_INCLUDE_DIRS})

add_definitions(-std=c++11 -g -O2)

install(TARGETS peterquad-client RUNTIME DESTINATION bin)


