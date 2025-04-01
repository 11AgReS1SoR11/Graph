set(SOURCE_LOGGER Logger.cpp)	

add_library(Logger SHARED ${SOURCE_LOGGER})

target_include_directories(Logger PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Копирование библиотеки в bin
set_target_properties(Logger PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS Logger DESTINATION lib)
install(FILES Logger.hpp DESTINATION include)
