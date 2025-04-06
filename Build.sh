#!/bin/bash

# Определяем операционную систему
OS=$(uname -s)

# Функция для вывода сообщений об ошибках и выхода
error()
{
  echo "Error: $1" >&2
  exit 1
}

CMAKE_GENERATOR="Unix Makefiles"

if ! which cmake > /dev/null; then
  echo "cmake не найден."
  exit 1
fi

# Определяем режим сборки (По умолчанию Debug)
BUILD_TYPE="Debug"
BUILD_DIR="build"
BUILD_TESTS_FLAG="-DBUILD_TESTS=ON"

# Обрабатываем аргументы командной строки
while [[ $# -gt 0 ]]; do
  case "$1" in
    --Release)
      BUILD_TYPE="Release"
      BUILD_DIR="build_release"
      shift
      ;;
    --noTest)
      BUILD_TESTS_FLAG="-DBUILD_TESTS=OFF"
      shift
      ;;
    *)
      echo "Неизвестный параметр: $1"
      exit 1
      ;;
  esac
done

# Создаем директорию сборки (если она не существует)
mkdir -p "$BUILD_DIR"

# Переходим в директорию сборки
cd "$BUILD_DIR"

# Конфигурируем проект с помощью CMake
cmake -G "$CMAKE_GENERATOR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" $BUILD_TESTS_FLAG .. || error "Ошибка при конфигурировании CMake"

cmake --build . --config "$BUILD_TYPE" -- -j36 || error "Ошибка при сборке проекта"

echo "Сборка в режиме $BUILD_TYPE успешно завершена!"
