set(SOURCE_SEMANTIC_ANALYSER
    SemanticAnalyzer.cpp
    AstStatementParser.cpp
)

set(HEADERS_SEMANTIC_ANALYSER
    SemanticAnalyzer.cpp
    AstStatementParser.cpp
)

add_library(SemanticAnalyzer SHARED ${SOURCE_SEMANTIC_ANALYSER})

target_include_directories(SemanticAnalyzer PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${CMAKE_SOURCE_DIR}/Common/AST/src
)

target_link_libraries(SemanticAnalyzer PUBLIC
    Logger
    AST
)

# Копирование библиотеки в bin
set_target_properties(SemanticAnalyzer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS SemanticAnalyzer DESTINATION lib)
install(FILES ${HEADERS_SEMANTIC_ANALYSER} DESTINATION include)
