find_package(PkgConfig)
pkg_check_modules(SQLITE3 sqlite3)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_COMPILER "clang++")

add_executable (Eater
    main.cpp
    fooditem.cpp
    recepie.cpp
    nutrients.cpp
    date.cpp
    time.cpp
    timestamp.cpp
    tags.cpp
    db.cpp
    db_fooditems.cpp
)

include_directories(
    ${SQLITE3_INCLUDE_DIRS}
    ../inc
)

set_target_properties(Eater PROPERTIES 
    RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin)

target_link_libraries(Eater
    ${SQLITE3_LIBRARIES}
)

link_directories(
    ${SQLITE3_LIBRARY_DIRS}
)

