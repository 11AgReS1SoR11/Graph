set(SOURCE_LOGGER Logger.cpp)	

add_library(Logger SHARED ${SOURCE_LOGGER})

target_include_directories(Logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Установка библиотеки (опционально)
install(TARGETS Logger DESTINATION lib)
install(FILES Logger.hpp DESTINATION include)
