set(SOURCE_RETRANSLATOR_TEST test.cpp)	

add_executable(RetranslatorTest ${SOURCE_RETRANSLATOR_TEST})

target_link_libraries(RetranslatorTest PRIVATE Retranslator)

target_include_directories(RetranslatorTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Включаем поддержку CTest (если еще не включена в корневом CMakeLists.txt)
include(CTest)

# Добавляем тест
add_test(NAME RetranslatorTest COMMAND RetranslatorTest)

#Указываем директории с заголовочными файлами (если есть)
#target_include_directories(Backend PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#)
