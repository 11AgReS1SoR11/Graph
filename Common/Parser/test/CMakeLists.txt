set(SOURCE_PARSER_TEST test.cpp)

add_executable(ParserTest ${SOURCE_PARSER_TEST})

target_link_libraries(ParserTest PRIVATE
    Catch2::Catch2WithMain
    Parser
)

target_include_directories(ParserTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/Parser/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME ParserTest COMMAND ParserTest)
