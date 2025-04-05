set(SOURCE_PARSER_TEST test.cpp)

set(TEST_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test1
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test2
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/test3
)

add_executable(ParserTest ${SOURCE_PARSER_TEST})

target_link_libraries(ParserTest PRIVATE
    Catch2::Catch2WithMain
    Parser
)

target_compile_options(ParserTest PRIVATE
    $<$<CONFIG:Debug>:
        -DDEBUG
    >
    $<$<CONFIG:Release>:
        -DNDEBUG
    >
)

set(TEST_OUTPUT_DIR "${CMAKE_BINARY_DIR}/Common/Parser/test/tests")

target_include_directories(ParserTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/Parser/src
    ${Catch2_SOURCE_DIR}/single_include
)

file(COPY ${TEST_FILES}
     DESTINATION ${TEST_OUTPUT_DIR}
)

add_test(NAME ParserTest COMMAND ParserTest)
