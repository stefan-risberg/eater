cmake_minimum_required(VERSION 2.8.8)
project(eater)

set (CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set (CMAKE_CXX_COMPILER "clang++")

# Tell CMake to run moc when needed.
#set(CMAKE_AUTOMOC_ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#find_package(Qt5Widgets REQUIRED)
find_package(PkgConfig)

pkg_check_modules(SQLITE3 sqlite3)
#add_library(format STATIC IMPORTED)
#set_target_properties(format PROPERTY IMPORTED_LOCATION ./lib/cppformat/build/libformat.a)

add_executable (eater
    src/main.cpp
    src/fooditem.cpp
    src/recepie.cpp
    src/nutrients.cpp
    src/date.cpp
    src/time.cpp
    src/timestamp.cpp
    src/tags.cpp
    src/db.cpp
    src/table_handler.cpp
    src/tbl_fooditems.cpp
    src/tbl_tags.cpp
    src/sql.cpp
)

add_library(format STATIC IMPORTED)
set_target_properties(format PROPERTIES IMPORTED_LOCATION
    ${CMAKE_SOURCE_DIR}/lib/cppformat/libformat.a)

include_directories(eater
    inc
    ${SQLITE3_INCLUDE_DIRS}
    ./lib/cppformat
)

link_directories(eater
    ${SQLITE3_LIBRARY_DIRS}
)

target_link_libraries(eater
    ${SQLITE3_LIBRARIES}
)
target_link_libraries(eater
    format
)

set_target_properties(eater PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin
)

install(TARGETS eater DESTINATION bin)
