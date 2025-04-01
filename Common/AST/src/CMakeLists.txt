set(SOURCE_AST AST.cpp)	

add_library(AST SHARED ${SOURCE_AST})

target_include_directories(AST PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# Копирование библиотеки в bin
set_target_properties(AST PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)

# Установка библиотеки
install(TARGETS AST DESTINATION lib)
install(FILES AST.hpp Node.hpp DESTINATION include)
