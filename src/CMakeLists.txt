add_executable (Eater
    main.cpp
    fooditem.cpp
    recepie.cpp
    nutrients.cpp
    date.cpp
    time.cpp
    timestamp.cpp
    )
#qt5_use_modules(Eater Widgets)

set_target_properties(Eater PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

