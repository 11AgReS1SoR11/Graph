set(SOURCE_FIGURES
    Diamond.cpp
    Circle.cpp
    DotCloud.cpp
    Graph.cpp
    Line.cpp
    Rectangle.cpp
    Style.cpp
    Shape.cpp
)

set(HEADERS_FIGURES
    Diamond.hpp
    Circle.hpp
    DotCloud.hpp
    Graph.hpp
    Line.hpp
    Rectangle.hpp
    Style.hpp
    Shape.hpp
)

add_library(Figures SHARED ${SOURCE_FIGURES})

target_include_directories(Figures PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Установка библиотеки (опционально)
install(TARGETS Figures DESTINATION lib)
install(FILES ${HEADERS_FIGURES} DESTINATION include)
