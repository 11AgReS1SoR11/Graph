set(SOURCE_AST_TEST test.cpp)

add_executable(ASTTest ${SOURCE_AST_TEST})

target_link_libraries(ASTTest PRIVATE
    Catch2::Catch2WithMain
    AST
)

target_include_directories(ASTTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/AST/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME ASTTest COMMAND ASTTest)

