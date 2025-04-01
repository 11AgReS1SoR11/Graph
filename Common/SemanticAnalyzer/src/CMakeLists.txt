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

# Установка библиотеки (опционально)
install(TARGETS SemanticAnalyzer DESTINATION lib)
install(FILES ${HEADERS_SEMANTIC_ANALYSER} DESTINATION include)
