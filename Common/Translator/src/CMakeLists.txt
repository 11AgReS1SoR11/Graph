# Translator lib
set(SOURCE_FIGURES_STORAGE Translator.cpp)	

add_library(Translator SHARED ${SOURCE_FIGURES_STORAGE})

target_include_directories(Translator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Figures
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${CMAKE_SOURCE_DIR}/Common/SemanticAnalyzer/src
    ${CMAKE_SOURCE_DIR}/Common/FiguresStorage/src
)

target_link_libraries(Translator PUBLIC
    Figures
    Logger
    SemanticAnalyzer
    FiguresStorage
)

# Копирование библиотеки в bin
set_target_properties(Translator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS Translator DESTINATION lib)
install(FILES Translator.hpp DESTINATION include)