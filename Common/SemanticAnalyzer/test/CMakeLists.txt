set(SOURCE_SEMANTIC_ANALYSER_TEST test.cpp)

add_executable(SemanticAnalyzerTest ${SOURCE_SEMANTIC_ANALYSER_TEST})

target_link_libraries(SemanticAnalyzerTest PRIVATE
    Catch2::Catch2WithMain
    SemanticAnalyzer
)

target_include_directories(SemanticAnalyzerTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/SemanticAnalyzer/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME SemanticAnalyzerTest COMMAND SemanticAnalyzerTest)
