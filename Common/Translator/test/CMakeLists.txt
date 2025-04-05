set(SOURCE_TRANSLATOR_TEST test.cpp)

add_executable(TranslatorTest ${SOURCE_TRANSLATOR_TEST})

target_link_libraries(TranslatorTest PRIVATE
    Catch2::Catch2WithMain
    Translator
)

target_include_directories(TranslatorTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/Common/Translator/src
    ${Catch2_SOURCE_DIR}/single_include
)

add_test(NAME TranslatorTest COMMAND TranslatorTest)
