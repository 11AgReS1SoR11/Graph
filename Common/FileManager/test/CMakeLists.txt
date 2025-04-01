set(SOURCE_FILE_MANAGER_TEST test.cpp)	

add_executable(FileManagerTest ${SOURCE_FILE_MANAGER_TEST})

target_link_libraries(FileManagerTest PRIVATE FileManager)

target_include_directories(FileManagerTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/src
)

# Включаем поддержку CTest (если еще не включена в корневом CMakeLists.txt)
include(CTest)

# Добавляем тест
add_test(NAME FileManagerTest COMMAND FileManagerTest)

#Указываем директории с заголовочными файлами (если есть)
#target_include_directories(Backend PUBLIC
#    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
#    $<INSTALL_INTERFACE:include>
#)
