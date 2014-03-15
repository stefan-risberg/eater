find_package(PkgConfig)
pkg_check_modules(SQLITE3 sqlite3)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(CMAKE_CXX_COMPILER "clang++")

add_executable (Eater
    src/main.cpp
    src/fooditem.cpp
    src/recepie.cpp
    src/nutrients.cpp
    src/date.cpp
    src/time.cpp
    src/timestamp.cpp
    src/tags.cpp
    src/db_food_items.cpp
)

include_directories(
    ${SQLITE3_INCLUDE_DIRS}
    inc
)

set_target_properties(Eater PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

target_link_libraries(Eater
    ${SQLITE3_LIBRARIES}
)

link_directories(
    ${SQLITE3_LIBRARY_DIRS}
)

