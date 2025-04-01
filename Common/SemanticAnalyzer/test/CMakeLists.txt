set(SOURCE_SEMANTIC_ANALYSER_TEST test.cpp)	

add_executable(SemanticAnalyzerTest ${SOURCE_SEMANTIC_ANALYSER_TEST})

target_link_libraries(SemanticAnalyzerTest PRIVATE SemanticAnalyzer)

target_include_directories(SemanticAnalyzerTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Включаем поддержку CTest (если еще не включена в корневом CMakeLists.txt)
include(CTest)

# Добавляем тест
add_test(NAME SemanticAnalyzerTest COMMAND SemanticAnalyzerTest)

#Указываем директории с заголовочными файлами (если есть)
#target_include_directories(Backend PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#)
