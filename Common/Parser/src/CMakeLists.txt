find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

set(FLEX_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp)
set(BISON_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp)
set(BISON_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/parser.h)

FLEX_TARGET(Lexer lexer.lex ${FLEX_OUTPUT})

BISON_TARGET(Parser parser.y ${BISON_OUTPUT}
             DEFINES_FILE ${BISON_HEADER})

ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set(SOURCE_PARSER
    Parser.cpp
    lexer.lex
    parser.y
    ${FLEX_OUTPUT}
    ${BISON_OUTPUT}
)

set(HEADERS_PARSER
    Parser.h
    ${BISON_HEADER}
)

add_library(Parser SHARED ${SOURCE_PARSER} ${HEADERS_PARSER})

target_include_directories(Parser PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${CMAKE_SOURCE_DIR}/Common/AST/src
)

target_link_libraries(Parser PUBLIC
    Logger
    AST
    ${FLEX_LIBRARIES}
)


set_target_properties(Parser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS Parser DESTINATION lib)
install(FILES ${HEADERS_PARSER} DESTINATION include)
