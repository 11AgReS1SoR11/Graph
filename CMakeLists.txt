cmake_minimum_required(VERSION 3.15)
project(GRAPH)

# Переменные для директорий
add_subdirectory(Backend)
add_subdirectory(Common)
add_subdirectory(App)

# Дополнительные настройки
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

# Установка (копирование) исполняемого файла в bin directory.
# install(TARGETS MyApp DESTINATION bin) # Установит MyApp в директорию "bin"
message(STATUS "CMake configuration complete. Now run 'cmake --build .'")
