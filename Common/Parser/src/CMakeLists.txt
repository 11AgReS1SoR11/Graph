# Uncomment if you change syntax for regenerate parser files
# find_package(FLEX REQUIRED)
# find_package(BISON REQUIRED)
# set(FLEX_REQUIRED_VERSION "2.6.0")
# set(BISON_REQUIRED_VERSION "3.0.0")

set(FLEX_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/_lexer_.cpp)
set(BISON_OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/_parser_.cpp)
set(BISON_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/_parser_.h)

# Uncomment if you change syntax for regenerate parser files
# FLEX_TARGET(Lexer lexer.lex ${FLEX_OUTPUT})
# BISON_TARGET(Parser parser.y ${BISON_OUTPUT}
#              DEFINES_FILE ${BISON_HEADER}
#              COMPILE_FLAGS "--defines=${BISON_HEADER}")

# ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

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

add_library(Parser SHARED ${SOURCE_PARSER})

target_include_directories(Parser PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${CMAKE_SOURCE_DIR}/Common/AST/src
    ${CMAKE_SOURCE_DIR}/Common/SemanticAnalyzer/src
)

target_link_libraries(Parser PUBLIC
    Logger
    AST
    SemanticAnalyzer
    # Uncomment if you change syntax for regenerate parser files
#    ${FLEX_LIBRARIES}
)

target_compile_options(Parser PRIVATE
    $<$<CONFIG:Debug>:
        -DDEBUG
    >
    $<$<CONFIG:Release>:
        -DNDEBUG
    >
)


set_target_properties(Parser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

install(TARGETS Parser DESTINATION lib)
install(FILES ${HEADERS_PARSER} DESTINATION include)
