set(SOURCE_AST_TEST test.cpp)	

add_executable(ASTTest ${SOURCE_AST_TEST})

target_link_libraries(ASTTest PRIVATE AST)

target_include_directories(ASTTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Включаем поддержку CTest (если еще не включена в корневом CMakeLists.txt)
include(CTest)

# Добавляем тест
add_test(NAME ASTTests COMMAND ASTTest)

#Указываем директории с заголовочными файлами (если есть)
#target_include_directories(Backend PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#)
