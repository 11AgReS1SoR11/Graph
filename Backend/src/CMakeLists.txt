set(SOURCE_BACKEND Backend.cpp)	

add_library(Backend SHARED ${SOURCE_BACKEND})

target_include_directories(Backend PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Retranslator/src
    ${CMAKE_SOURCE_DIR}/Common/AST/src
    ${CMAKE_SOURCE_DIR}/Common/Figures
    ${CMAKE_SOURCE_DIR}/Common/FiguresStorage/src
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${CMAKE_SOURCE_DIR}/Common/SemanticAnalyzer/src
    ${CMAKE_SOURCE_DIR}/Common/FileManager/src
)

target_link_libraries(Backend PUBLIC
    Retranslator
    AST
    Figures
    FiguresStorage
    Logger
    SemanticAnalyzer
    FileManager
)

# Копирование библиотеки в bin
set_target_properties(Backend PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS Backend DESTINATION lib)
install(FILES Backend.hpp DESTINATION include)
