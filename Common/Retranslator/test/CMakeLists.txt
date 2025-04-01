set(SOURCE_RETRANSLATOR_TEST test.cpp)

add_executable(RetranslatorTest ${SOURCE_RETRANSLATOR_TEST})

target_link_libraries(RetranslatorTest PRIVATE
    Catch2::Catch2WithMain
    Retranslator
)

target_include_directories(RetranslatorTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/Retranslator/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME RetranslatorTest COMMAND RetranslatorTest)
