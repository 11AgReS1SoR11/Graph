# Макрос для подключения Catch2
macro(include_catch2)
  include(FetchContent)
  FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG        v3.5.2
  )
  set(Catch2_POPULATE_BUILD_DIR OFF)
  FetchContent_MakeAvailable(Catch2)
endmacro()

cmake_minimum_required(VERSION 3.15)
project(GRAPH)

# Опция для включения/выключения сборки тестов
option(BUILD_TESTS "Enable building tests" ON)

if(BUILD_TESTS)
    include_catch2()
    include(CTest)
endif()

# Переменные для директорий
add_subdirectory(Backend)
add_subdirectory(Common)
add_subdirectory(App)

# Дополнительные настройки
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

message(STATUS "CMake configuration complete. Now run 'cmake --build .'")
