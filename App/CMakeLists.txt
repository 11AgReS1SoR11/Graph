add_executable(Graph main.cpp)

target_include_directories(Graph PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Backend/src
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
)

# Связываем с библиотеками
target_link_libraries(Graph PUBLIC
    Retranslator
    AST
    Figures
    FiguresStorage
    Logger
    SemanticAnalyzer
    FileManager
    Backend
)

set_target_properties(Graph PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# install application
install(TARGETS Graph DESTINATION bin)
