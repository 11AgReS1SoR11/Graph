# FiguresStorage lib
set(SOURCE_FIGURES_STORAGE FiguresStorage.cpp)	

add_library(FiguresStorage SHARED ${SOURCE_FIGURES_STORAGE})

target_include_directories(FiguresStorage PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Figures
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
)

target_link_libraries(FiguresStorage PUBLIC
    Figures
    Logger
)

# Копирование библиотеки в bin
set_target_properties(FiguresStorage PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS FiguresStorage DESTINATION lib)
install(FILES FiguresStorage.hpp DESTINATION include)
