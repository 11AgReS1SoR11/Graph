#!/bin/bash

# Определяем операционную систему
OS=$(uname -s)

# Функция для вывода сообщений об ошибках и выхода
error()
{
  echo "Error: $1" >&2
  exit 1
}

# Определяем команду make
if [[ "$OS" == "MINGW"* || "$OS" == "Windows_NT"* ]]; then
  CMAKE_GENERATOR="MinGW Makefiles"
else
  CMAKE_GENERATOR="Unix Makefiles"
fi

if ! which cmake > /dev/null; then
  echo "cmake не найден."
  exit 1
fi

# Создаем директорию build (если она не существует)
mkdir -p build

# Переходим в директорию build
cd build

if [[ "$1" == "--noTest" ]]; then
  BUILD_TESTS_FLAG="-DBUILD_TESTS=OFF"
else
  BUILD_TESTS_FLAG="-DBUILD_TESTS=ON"
fi

# Конфигурируем проект с помощью CMake
cmake -G "$CMAKE_GENERATOR" $BUILD_TESTS_FLAG .. || error "Ошибка при конфигурировании CMake"

cmake --build . -- -j36

echo "Сборка успешно завершена!"
