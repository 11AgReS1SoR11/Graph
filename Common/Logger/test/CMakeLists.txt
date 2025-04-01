set(SOURCE_LOGGER_TEST test.cpp)

add_executable(LoggerTest ${SOURCE_LOGGER_TEST})

target_link_libraries(LoggerTest PRIVATE
    Catch2::Catch2WithMain
    Logger
)

target_include_directories(LoggerTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME LoggerTest COMMAND LoggerTest)
