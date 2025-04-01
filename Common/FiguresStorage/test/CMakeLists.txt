set(SOURCE_FIGURES_STORAGE_TEST test.cpp)	

add_executable(FiguresStorageTest ${SOURCE_FIGURES_STORAGE_TEST})

target_link_libraries(FiguresStorageTest PRIVATE FiguresStorage)

target_include_directories(FiguresStorageTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Включаем поддержку CTest (если еще не включена в корневом CMakeLists.txt)
include(CTest)

# Добавляем тест
add_test(NAME FiguresStorageTest COMMAND FiguresStorageTest)

#Указываем директории с заголовочными файлами (если есть)
#target_include_directories(Backend PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#)
