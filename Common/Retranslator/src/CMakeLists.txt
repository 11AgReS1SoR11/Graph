set(SOURCE_RETRANSLATOR Retranslator.cpp)	

add_library(Retranslator SHARED ${SOURCE_RETRANSLATOR})

target_include_directories(Retranslator PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${CMAKE_SOURCE_DIR}/Common/Figures
    ${CMAKE_SOURCE_DIR}/Common/Logger/src
    ${CMAKE_SOURCE_DIR}/Common/AST/src
)

target_link_libraries(Retranslator PUBLIC
    Logger
    AST
    Figures
)

# Копирование библиотеки в bin
set_target_properties(Retranslator PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS Retranslator DESTINATION lib)
install(FILES Retranslator.hpp DESTINATION include)
